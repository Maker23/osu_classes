/* vim:ts=2
 *                      Shoshana Abrass
 *                  abrasss@oregonstate.edu
 *                    CS344_400 Program 3
 *                       May 23, 2016
 *
 * Compile on eos-class with "gcc -o smallsh smallsh.c"
 *
 * I am indebted to: 
 * 	= Stephen Brennan's tutorial "Write a Shell in C", 
 * 	  which clearly lays out the logical flow of a shell program
 *	= Various gnu.org docs on subjects like process completion (for waitpid),
 *	  duplicating descriptors, and signal handling
 *  = The Linux man pages
 *  = cplusplus.com: the best C/C++ documentation online or off
 *
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>

#define FILE_DEBUG 0
#define LOGIC_DEBUG 0
#define CHILD_DEBUG 0
#define PARSING_DEBUG 0
#define GENERAL_DEBUG 0
// #define PROMPT "smallsh> "
#define PROMPT ":"

#define MAX_CMD_LENGTH 2048
#define MAX_ARG_COUNT 512
#define FALSE 0
#define TRUE  1

#define INPUT 5
#define OUTPUT 7

struct command 
{
	char commandline[MAX_CMD_LENGTH]; // A string
	char * args[MAX_ARG_COUNT]; 	// An array of pointers
	char * input_filename;
	char * output_filename;
	int argcount;
	int	redirect_output;// used as a boolean
	int	redirect_input;	// used as a boolean
	int	background;			// used as a boolean
	int	csignal;	// preserve the exit signal, if any
};

// Function prototypes
void innerLoop();
void * printCommandStruct(struct command * Command);
void catchInterruptParent(int sig);
void killProcessGroup();
void checkForBackgroundChildren();
struct command * parseCommandLine ( char * inputLine);
int runCommand (struct command * Command);
int returnChildStatus ( struct command * Command, int status );

// Global signal handling struct
struct sigaction p_sigact;

/* **********************************************************
 *
 * The main() function simply sets up signal handling for the
 * parent and then enters a command-parsing loop
 *
 ********************************************************* */
main(int argc, char ** argv)
{
	/* Trap SIGINT for handling */
	p_sigact.sa_flags = 0;
	sigemptyset(&p_sigact.sa_mask);
	p_sigact.sa_handler = catchInterruptParent;
	sigaction(SIGINT, &p_sigact, NULL);

	/* Loop indefinitely */
	innerLoop();
}

/* **********************************************************
 *
 * innerLoop(): Loop indefinitely, printing the prompt and 
 * collecting user-input command lines. Return when the builtin
 * command "exit" is issued.
 *
 ********************************************************* */
void innerLoop()
{
	char input[MAX_CMD_LENGTH];
	struct command * Command;
	int status = 0;
	int csignal = 0;

	while (1)
	{
		// At the beginning of the loop, before printing the prompt,
		// check to see if any background children have terminated
		checkForBackgroundChildren();

		memset (input, 0, sizeof input); // wipe the keyboard input buffer

		// Print the prompt and get the user's input
		fprintf(stdout, "%s", PROMPT);
		fgets(input, sizeof input, stdin);
		fflush(stdout); fflush(stdin);

		// Make sure the last position is null in case input is max length
		input[sizeof(input)] = '\0';
		// Remove trailing newline(s) from input
		while (input[strlen(input)-1] == '\n')
			input[strlen(input)-1] = '\0';

		PARSING_DEBUG && printf ("DBG: received |%s|\n", input); fflush(stdout);

		// Save a little time by checking simple cases before parsing. 
		if ( strcmp (input, "" ) == 0 )
			continue;
		if ( strcmp (input, "exit" ) == 0 )
		{
			// Exit? Kill all children and return to main
			killProcessGroup();
			return;
		}
			
		// Parse the user input into our Command struct, and look for special cases 
		Command = parseCommandLine(input);

		LOGIC_DEBUG && printf("DBG: *Command = %p\n", Command); fflush(stdout);
		if (Command == NULL ) {
			status=-1;
			continue;		// failed to parse; return to loop beginning
		}
		if ( strcmp(Command->args[0], "exit") == 0 )
		{
			// exit builtin
			// Exit? Kill all children and return to main
			killProcessGroup();
			return;	
		}
		if ( strncmp (Command->args[0], "#", 1 ) == 0 )
		{
			// comment builtin
			// This is a comment, ignore the rest of the line
			status=0;	
	 		continue; 
		}
		if ( strcmp(Command->args[0], "status") == 0 )
		{
			// status builtin
			// Print the status (or signal) of the previous command
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

		// No special cases found - run the user's command 
		status = runCommand(Command);
		csignal = Command->csignal; // save any signal before freeing the struct

		LOGIC_DEBUG && printf("DBG: status = %d\n", status); 
	
		// Free malloc'd struct memory and loop again
		free (Command);
	}
}

/* **********************************************************
 *
 * runCommand(): Take a filled command struct and execute it.
 *
 * This function is composed of a set of nested if/else tests;
 * each case should match only one rightmost test, but there
 * is only one return() statement at the function end.
 *
 ********************************************************* */
int runCommand(struct command * Command)
{
	int i;
	int status=0;
	pid_t pid, w_pid;
	char cwdbuf[PATH_MAX];
	char *cptr;

	LOGIC_DEBUG && printf ("DBG: Starting runCommand\n");
	(LOGIC_DEBUG || FILE_DEBUG) && printCommandStruct(Command);

  /* 
	 * Look for our built-in commands first. Supported commands are:
	 *
	 * 	cd		Change directory
	 * 	pwd		Print Working Directory
	 */
	if ( strcmp(Command->args[0], "cd") == 0 )
	{
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
		cptr = getcwd(cwdbuf, sizeof(cwdbuf));
		if (cptr==NULL)
		{
			status=-1;
			perror("getcwd");
		}
		else
		{
			printf("%s\n", cwdbuf);
			status=0;
		}
	}
	else
	{
		/* 
		 * Command is not a built-in. Fork here. 
		 * Parent waits for the child unless it's backgrounded.
		 * Child calls runChild() to exec the command.
		 */
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
			exit(status); // This line is never reached, because exec
		}
		else 
		{
			// Parent process
			if ( ! Command->background ) 
			{
				CHILD_DEBUG &&	printf ("DBG: Parent is waiting for process %d\n", pid );
				// Run in the foreground; parent waits for child to exit
				do {
					w_pid = waitpid(pid, &status, WUNTRACED);
				}
				while (! WIFEXITED(status) && !WIFSIGNALED(status));
				status = returnChildStatus (Command, status);
			}
			else 
			{
				// Run in the background; print the child process ID and return
				printf("[pid %d]\n", pid);
			}
		}
	}

	return(status);
}

/* **********************************************************
 *
 * checkForBackgroundChildren()
 * Use waitpid() to check the process group for any children
 * that have terminated (normally or with a signal)
 * If found, print the child pid and exit condition
 *
 ********************************************************* */
void checkForBackgroundChildren()
{
	pid_t w_pid;
	int status;

	/* Poll for status of any backgrounded processes that have finished */
	CHILD_DEBUG && printf ("polling for backgrounded processes\n");
	while ( (w_pid = waitpid(WAIT_MYPGRP, &status, WNOHANG |WUNTRACED)) > 0)
	{
		CHILD_DEBUG && printf ("poll, w_pid = %d\n", w_pid);
		printf("pid(%d): ", w_pid);
		status = returnChildStatus(NULL, status);
	}
}

/* **********************************************************
 *
 * returnChildStatus()
 * Print the child's exit condition, slightly different depending
 * on whether it had a normal exit() or whether it was killed
 * by a signal
 *
 ********************************************************* */
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

/* **********************************************************
 *
 * runChild()
 * This is where the child exec's the new command.
 * First it redirects stdin/stdout as needed.
 *
 * The return status here is critical. It should be:
 *    -1, if the redirect or exec fail
 *	  or  the return value of the execvp() call
 *
 ********************************************************* */
int runChild(struct command * Command)
{
	int status;
	int fdin, fdout;
	
	// permission mode for files we create from stdout
	mode_t mode = ( S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH );

	// noisy debugging info
	if (CHILD_DEBUG)
	{
		int i;
		printf ("DBG: In runChild forking: |");
		for (i=0; i< Command->argcount; i++) 
			printf (" %s", Command->args[i]);
		printf ("|\n");
		fflush(stdout);
		fflush(stdin);
	}

	// Redirect stdin and stdout as necessary
 	if ( Command->background && !(Command->redirect_input))
	{
		// If background and no stdin, redirect stdin to /dev/null
		CHILD_DEBUG && printf("DBG: background with no input redirect");
		fflush(stdout);
		if ( ( fdin = open("/dev/null", O_RDONLY, mode)) < 0 )
		{
			perror("/dev/null");
			return (-1);
		}
		dup2(fdin, STDIN_FILENO);
	}

 	if ( Command->redirect_input && (Command->input_filename != NULL))
	{
		// Redirect stdin from a file
		if ( ( fdin = open(Command->input_filename, O_RDONLY, mode)) < 0 )
		{
			perror(Command->input_filename);
			return (-1);
		}
		dup2(fdin, STDIN_FILENO);
	}
 	if ( Command->redirect_output && (Command->output_filename != NULL))
	{
		// Redirect stdout to a file
		if ( ( fdout = open (Command->output_filename, O_WRONLY|O_CREAT|O_TRUNC, mode)) < 0 )
		{
			perror(Command->output_filename);
			return (-1);
		}
		dup2(fdout, STDOUT_FILENO);
	}

	// Exec the child process, capture the status
	// Note that execvp uses the PATH environment variable
	status = execvp(Command->args[0], Command->args);
	if ( status < 0 )
		perror(Command->args[0]);

	return(status);
}

/* **********************************************************
 *
 * parseCommandLine()
 * Take the user's command line input and return a pointer
 * to a filled command struct - or NULL if there's a parsing error
 * Note that malloc is used to create the struct, which will
 * be freed elsewhere
 *
 ********************************************************* */
struct command * parseCommandLine ( char * inputLine)
{
	struct command * thisCommand;
	char *inputWord[MAX_ARG_COUNT];
	int i;
	int wordcount, argcount;
	int has_command = FALSE;  // boolean
	int looking_for_filename = FALSE; // booleans

	wordcount=0;	// the number of tokens or 'words' in the user's input
	argcount=0;		// the number of command arguments we end up with

	// malloc a new command struct, and permanently copy the
	// user input into it
	thisCommand = (struct command *) malloc (sizeof (struct command));
	if (thisCommand == NULL) 
		return(NULL); // malloc failed
	memset (thisCommand, 0, sizeof (struct command));
	strcpy(thisCommand->commandline,inputLine);

	// Parse the line into tokens, using space and tab as delimiters
	inputWord[wordcount] = strtok(thisCommand->commandline, " 	");
	while ( inputWord[wordcount] != NULL )
	{
		wordcount++;
		inputWord[wordcount] = strtok(NULL, " 	");
	}
	
	// Helpful debugging
	if ( PARSING_DEBUG > 1 ) {
		printf ("Tokenized stream:\n");
		for (i=0; i < wordcount; i++) 
			printf ("token %d  :%s:\n", i, inputWord[i]);
	}

	// Now step through the tokens and build the Command struct
	// Special tokens, such as >,<,&, are treated differently
	//
	for (i=0; i < wordcount; i++) {
	
		// Is it a redirect symbol? <,> 
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
					// This should never happen!! why do we even have this button?
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
				return(NULL);
			}
			else
			{
				// Stop parsing and throw the rest of the input away.
				thisCommand->background = TRUE;
				return(thisCommand);
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

/* **********************************************************
 *
 * catchInterruptParent()
 * This does pretty much nothing, and is functionally equivalent 
 * to ignoring SIGINT
 *
 ********************************************************* */
void catchInterruptParent(int sig)
{
	LOGIC_DEBUG && printf("Parent caught signal %d\n", sig);
	// Parent process doesn't do anything with the interrupt
	// We print a newline here to keep the prompt clean
	printf("\n");
	fflush(stdout);
	return;
}

/* **********************************************************
 *
 * printCommandStruct() - solely for debugging
 *
 ********************************************************* */
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

/* **********************************************************
 *
 * killProcessGroup()
 * Kill all child processes before the parent exits. 
 * First tells the parent to ignore SIGTERM, then issues SIGTERM
 * to the entire process group
 *
 ********************************************************* */
void killProcessGroup()
{
	pid_t myPgid;
	struct sigaction save_sigact, tmp_sigact;
	int result;

	if ( (myPgid = getpgid(0)) < 0 )
		perror("getpgid");
	
	// preserve the parent's existing signal state
	if ( sigaction (SIGTERM, NULL, &save_sigact) < 0)
	{
		; // sigaction fail. What do we do about that :) Ignore I guess
	}
	else 
	{
		// Now ignore signal in parent - since the parent is also in the process group
		memcpy ( &tmp_sigact, &save_sigact, sizeof(save_sigact));
		tmp_sigact.sa_handler = SIG_IGN;
		sigaction(SIGTERM, &tmp_sigact, NULL);
	}
		     
	// signal the process group
	if (killpg(getpgrp(), SIGTERM) == -1)
		perror("killpg");

	// restore the parent's signal state
	sigaction(SIGTERM, &save_sigact, NULL);

}

