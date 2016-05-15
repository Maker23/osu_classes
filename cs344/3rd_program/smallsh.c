/* vim:ts=2
 *                      Shoshana Abrass
 *                  abrasss@oregonstate.edu
 *                    CS344_400 Program 3
 *                       May TODO, 2016
 *
 * Your shell will allow for the redirection of standard input and
 * standard output and it will support both foreground and background
 * processes.
 *
 *
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h> // For random numbers
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>

#define FILE_DEBUG 0
#define LOGIC_DEBUG 0
#define CHILD_DEBUG 0
#define PARSING_DEBUG 0
#define GENERAL_DEBUG 0

#define PROMPT "smallsh> "

#define MAX_CMD_LENGTH 2048
#define FALSE 0
#define TRUE  1

#define INPUT 5
#define OUTPUT 7


struct command 
{
	char commandline[MAX_CMD_LENGTH]; // A string
	char * args[512]; // An array of pointers
	char * input_filename;
	char * output_filename;
	int argcount;
	int	redirect_output;// boolean
	int	redirect_input;	// boolean
	int	background;			// boolean
	int	csignal;
};

// Function prototypes
void inner_loop();
void * printCommandStruct(struct command * Command);
void catchInterrupt_Parent(int sig);
void killProcessGroup();
void checkForBackgroundChildren();
struct command * parse_command_line ( char * inputLine);
int runCommand (struct command * Command, char * PATH);
int returnChildStatus ( struct command * Command, int status );

main(int argc, char ** argv)
{
	/* Initialize the shell by reading config files */
	// Trap SIGINT and kill foreground running process; if no fg process, ignore
	signal (SIGINT, catchInterrupt_Parent);

	/* Loop indefinitely */
	inner_loop();
}

void inner_loop()
{
	char input[MAX_CMD_LENGTH]; //hardcoded for now, TODO
	struct command * Command;
	int status = 0;
	int csignal = 0;

	char * PATH = getenv("PATH"); // in the real world this code would be elsewhere
	LOGIC_DEBUG && printf ("DBG: PATH is %s\n", PATH);

	while (1)
	{
		memset (input, 0, sizeof input);
		// Print the prompt and get the input
		fprintf(stdout, "%s", PROMPT);
		fgets(input, sizeof input, stdin);
		fflush(stdout);
		fflush(stdin);

		/* get user input */

		while (input[strlen(input)-1] == '\n')
			input[strlen(input)-1] = '\0';

		PARSING_DEBUG && printf ("DBG: received |%s|\n", input);

		/* Save a little time by checking before parsing.  If input == exit, exit */
		if ( strcmp (input, "" ) == 0 )
			continue;
		if ( strcmp (input, "exit" ) == 0 )
		{
			// Kill all children
			killProcessGroup();
			return;
		}
			
		/* Now parse */
		Command = parse_command_line(input);
		LOGIC_DEBUG && printf("DBG: *Command = %p\n", Command);
		if (Command == NULL ) {
			status=-1;
			continue;			// failed to parse
		}
		if ( strcmp(Command->args[0], "exit") == 0 )
			return;		// If input == exit, exit
		if ( strncmp (Command->args[0], "#", 1 ) == 0 )
		{
			status=0;	
	 		continue; // If the first character is a comment, ignore the rest of the line
		}
		if ( strcmp(Command->args[0], "status") == 0 )
		{
			// If input==status, print the status (or signal) of the previous command
			if ( csignal ) 
			{
				printf("terminated by signal %d\n", csignal);
			}
			else {
				printf("exit value %d\n", status);
			}
			status=0; 
			csignal=0; 
			continue;
		}

		/* execute user input */
		status = runCommand(Command, PATH);
		csignal = Command->csignal;

		LOGIC_DEBUG && printf("DBG: status = %d\n", status);

		checkForBackgroundChildren();
	
		// Free malloc'd memory and loop again
		free (Command);
	}
}

int runCommand(struct command * Command, char * PATH)
{
	int i;
	int status=0;
	pid_t pid, w_pid;
	char buf[PATH_MAX];
	char *cptr;

	LOGIC_DEBUG && printf ("DBG: Starting runCommand\n");
	(LOGIC_DEBUG || FILE_DEBUG) && printCommandStruct(Command);

	if ( strcmp(Command->args[0], "cd") == 0 )
	{
		// CD code here
		if (Command->argcount < 2 )
		{
			char * HOME = getenv("HOME");
			LOGIC_DEBUG && printf("DBG: cd'ing to HOME = %s\n", HOME);
			if (strcmp(HOME, "") == 0)
			{
				perror("Can't determine $HOME\n");
				status=-1;
			}
			else
			{
				status = chdir(HOME);
				if (status < 0 )
					perror(HOME);
			}
		}
		else
		{
			LOGIC_DEBUG && printf("DBG: cd'ing to dir = %s\n", Command->args[1]);
			status = chdir(Command->args[1]);
			if (status < 0 )
				perror(Command->args[1]);
		}
	}
	else if ( strcmp(Command->args[0], "pwd") == 0 )
	{
		cptr = getcwd(buf, sizeof(buf));
		if (cptr==NULL)
		{
			status=-1;
			perror("getcwd");
		}
		else
		{
			printf("%s\n", buf);
			status=0;
		}
	}
	else
	{
		// else fork
		pid = fork();
		if ( pid < 0 )
		{
			perror(Command->args[i]);
			status = pid;
		}
		else if ( pid == 0 )
		{
			// Child process
			status = runChild(Command);
			CHILD_DEBUG && printf ("Child exiting with status %d\n", status);
			exit(status);
		}
		else 
		{
			// TODO: implement backgrounding
			// Parent process; poll for status
			CHILD_DEBUG &&	printf ("DBG: Parent is waiting for process %d\n", pid );
			if ( ! Command->background ) 
			{
				do {
					w_pid = waitpid(pid, &status, WUNTRACED);
				}
				while (! WIFEXITED(status) && !WIFSIGNALED(status));
				status = returnChildStatus (Command, status);
			}
			else 
			{
				printf("[] %d\n", pid);
			}
		}
	}
	// if interrupted, return signal value
	return(status);
}

void checkForBackgroundChildren()
{
	pid_t w_pid;
	int status;
	/* Poll for status of any backgrounded processes that have finished */
	CHILD_DEBUG && printf ("polling for backgrounded processes now\n");
	while ( (w_pid = waitpid(WAIT_MYPGRP, &status, WNOHANG |WUNTRACED)) > 0)
	{
		CHILD_DEBUG && printf ("poll, w_pid = %d\n", w_pid);
		printf("pid(%d): ", w_pid);
		status = returnChildStatus(NULL, status);
	}
}

int returnChildStatus ( struct command * Command, int status )
{
	if (WIFEXITED(status)) 
	{
		(CHILD_DEBUG || (Command == NULL)) && printf("child exited, status=%d\n", WEXITSTATUS(status));
		status =  WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status)) 
	{
		printf("child killed (signal %d)\n", WTERMSIG(status));
		if (Command != NULL )
			Command->csignal =  WTERMSIG(status);
		status =  WIFSIGNALED(status);
	}
	fflush(stdout);
	return(status);
}

int runChild(struct command * Command)
{
	int i;
	int io;
	int status;
	int fdin, fdout;

	mode_t mode = ( S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH );

	if (CHILD_DEBUG)
	{
		printf ("DBG: In runChild forking: |");
		for (i=0; i< Command->argcount; i++) 
			printf (" %s", Command->args[i]);
		printf ("|\n");
		fflush(stdout);
		fflush(stdin);
	}
	//
  // reset stdin and stdout before exec
	//
 	if ( Command->redirect_input && (Command->input_filename != NULL))
	{
		if ( ( fdin = open(Command->input_filename, O_RDONLY, mode)) < 0 )
		{
			perror(Command->input_filename);
			return (-1);
		}
		dup2(fdin, STDIN_FILENO);
	}
 	if ( Command->redirect_output && (Command->output_filename != NULL))
	{
		if ( ( fdout = open (Command->output_filename, O_WRONLY|O_CREAT|O_TRUNC, mode)) < 0 )
		{
			perror(Command->output_filename);
			return (-1);
		}
		dup2(fdout, STDOUT_FILENO);
	}

	// exec the child process, capture the status
	status = execvp(Command->args[0], Command->args);
	if ( status < 0 )
	{
		perror(Command->args[0]);
	}
	return(status);
}

struct command * parse_command_line ( char * inputLine)
{
	struct command * thisCommand;
	char *inputWord[512];
	char *filename;
	int 	w, i, argcount;
	int background, redirect_input, redirect_output; // used as booleans
	int has_command, looking_for_filename; // used as booleans

	// Initialize variables
	w=0;
	argcount=0;
	has_command = FALSE;
	looking_for_filename = FALSE;
	filename=(char *)NULL;

	thisCommand = (struct command *) malloc (sizeof (struct command));// TODO or fail
	memset (thisCommand, 0, sizeof (struct command));
	strcpy(thisCommand->commandline,inputLine); // TODO or fail

	// TODO shoudl this be a do-while loop?
	inputWord[w] = strtok(thisCommand->commandline, " 	"); // space and tab as delimiters
	while ( inputWord[w] != NULL )
	{
		w++;
		inputWord[w] = strtok(NULL, " 	");
	}
	
	if ( PARSING_DEBUG > 1 ) {
		printf ("Tokenized stream:\n");
		for (i=0; i < w; i++) 
			printf ("token %d  :%s:\n", i, inputWord[i]);
	}
	
	for (i=0; i < w; i++) {
		// Is it a redirect <>  ?
		if (strcmp(inputWord[i], "<") == 0 || strcmp(inputWord[i], ">") == 0 )
		{
			if (! has_command)
			{
				printf("Syntax error: Redirect without a command\n");
				return(NULL);
				//	If we don't alread have a command, this is an error
			}
			else if ( looking_for_filename )
			{
				printf("Syntax error: Expecting filename after redirect\n");
				return(NULL);
			}
			else
			{

				if (strcmp(inputWord[i], "<") == 0)
				{
					(PARSING_DEBUG || FILE_DEBUG) && printf ("DBG: found redirect input\n");
					looking_for_filename = INPUT;
					thisCommand->redirect_input = TRUE;
				}
				else if (strcmp(inputWord[i], ">") == 0 )
				{
					(PARSING_DEBUG || FILE_DEBUG) && printf ("DBG: found redirect output\n");
					looking_for_filename = OUTPUT;
					thisCommand->redirect_output = TRUE;
				}
				else 
				{
					// This should never happen!!
				} 

			}
		}
		else if ( strcmp(inputWord[i], "&") == 0 )
		{
			// Is it an &  ?  
			if (looking_for_filename) 
			{
				printf("Syntax error: Expecting filename after redirect\n");
				return(NULL);
			}
			else if ( ! has_command )
			{
				// This is a no-op
				return;
			}
			else
			{
				// Stop parsing and throw the rest of the input away.
				thisCommand->background = TRUE;
				return;
			}
		}
		// It's a plain word - either a command or an argument
		else
		{
			if ( looking_for_filename)
			{
				(PARSING_DEBUG || FILE_DEBUG) && printf ("DBG: found filename %s, lff=%d\n", inputWord[i], looking_for_filename);
				if ( looking_for_filename == INPUT )
				{
					(PARSING_DEBUG || FILE_DEBUG) && printf ("DBG: setting input file\n");
					thisCommand->input_filename = inputWord[i];
				}
				else 
				{
					(PARSING_DEBUG || FILE_DEBUG) && printf ("DBG: setting output file\n");
					thisCommand->output_filename = inputWord[i];
				}
				looking_for_filename = FALSE;
			}
			else if ( has_command )
			{
				PARSING_DEBUG && printf ("DBG: found argument %s\n", inputWord[i]);
				thisCommand->args[argcount++] = inputWord[i];
			}
			else 
			{
				PARSING_DEBUG && printf ("DBG: found command %s\n", inputWord[i]);
				thisCommand->args[argcount++] = inputWord[i];
				has_command=TRUE;
			}

		// Examine the word.  Is it a built-in?
		// If not, it's a command 
			// Now everything that's not a special character is an argument.
		}
	}
	thisCommand->argcount = argcount;

	// Check for errors
	if ( has_command == FALSE )
	{
		printf("Syntax error: unparseable command line\n");
		return(NULL);
	}
	if ( looking_for_filename ) 
	{
		printf("Syntax error: Expecting filename after redirect\n");
		return(NULL);
	}
	
	return(thisCommand);

}

void catchInterrupt_Parent(int sig)
{
	LOGIC_DEBUG && printf("Parent caught signal %d\n", sig);
	signal (SIGINT, catchInterrupt_Parent);
	return;
}
/*
 * This is solely for debugging
 *
 */
void * printCommandStruct(struct command * Command)
{
	int i;

	printf ("argcount = %d\n", Command->argcount);
	for (i = 0; i < Command->argcount; i++)
	{
		printf ("args[%d] = %s\n", i, Command->args[i]);
	}
	if ( Command->input_filename != NULL)
		printf ("input  filename = %s\n", Command->input_filename);
	if ( Command->output_filename != NULL)
		printf ("output filename = %s\n", Command->output_filename);
	if ( Command->background != 0)
		printf ("background = TRUE\n");
}

void killProcessGroup()
{
	pid_t myPgid;
	int result;

	if ( (myPgid = getpgid(0)) < 0 )
		perror("getpgid");
	
  if (signal(SIGTERM, SIG_IGN) == SIG_ERR)
		perror("SIG_IGN");
		     
	if (killpg(getpgrp(), SIGUSR1) == -1)
		perror("killpg");

  if (signal(SIGTERM, SIG_DFL) == SIG_ERR)
		perror("SIG_DFL");

	//TODO: kill all children
	// getpgid
	// ignore signal
	// killpg
	// restore signal
	// exit
}

/*
 * The general syntax of a command line is:
 * 
 *	command [arg1 arg2 ...] [< input_file] [> output_file] [&]
 *
 * …where items in square brackets are optional.  You can assume that
 * a command is made up of words separated by spaces. 
 *
 * The special symbols * <, >, and & are recognized, but they must
 * be surrounded by spaces like other words. If the command is to be
 * executed in the background, the last word must be &. If standard
 * input or output is to be redirected , the > or < words followed
 * by a filename word must appear after all the arguments. Input redirection
 * can appear before or after output redirection.
 *
 * Your shell does not need to support any quoting; so arguments with
 * spaces inside them are not possible.
 *
 * Your shell must support command lines with a maximum length of 2048
 * characters, and a maximum of 512 arguments. You do not need to do
 * any error checking on the syntax of the command line.
 *
 * Finally, your shell should allow blank lines and comments.  Any
 * line that begins with the # character is a comment line and should
 * be ignored.  A blank line (one without any commands) should do nothing; 
 * your shell should just re-prompt for another command.
 */
