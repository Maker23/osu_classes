/* vim:ts=2
 *                      Shoshana Abrass
 *                  abrasss@oregonstate.edu
 *                    CS344_400 Program 2
 *                       May 2, 2016
 *
 * A classic text-based maze adventure game in the genre of 
 * https://en.wikipedia.org/wiki/Colossal_Cave_Adventure
 *
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h> // For random numbers
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>

#define FILE_DEBUG 0
#define LOGIC_DEBUG 0
#define ROOM_DEBUG 0
#define CONNECT_DEBUG 0
#define GENERAL_DEBUG 0

// TODO exit or return on all perrors
// Global type for struct Room
struct Room 
{
	int	 connections;
	char Room_Name[32];	// The name of the room 
	char Room_Type[16]; // A string that defines the room type 
	struct Room * Connection[6];
};

// Defining room names at the top, although strictly speaking these
// don't need to be global
// Name length is limited to 31 characters plus NULL
const char * My_Room_Names[] =
{
	"entryway",			// 0
	"elevator",			// 1
	"hallway",			// 2
	"music room",		// 3
	"room of cats",	// 4 
	"library",			// 5
	"billiard room",// 6
	"microkitchen",	// 7 
	"nap room",			// 8
	"workshop",			// 9
	// Bonus rooms ;)
	"bridge of the Enterprise",			// 10
	"Galactic Senate on Coruscant",	// 11
	"Mechanicsburg coffee house",		// 12
	"South Pole",										// 13
	"MMORPG command center",				// 14
// 1234567890123456789012345678901// name length indicator
};

const char * Room_Types[] =
{
	"START_ROOM",
	"END_ROOM",
	"MID_ROOM",
};

/* Handy global variables that control gameplay */
int room_names = 15;
int room_types = 3;
int rooms_in_game = 7;
int min_connections = 3;
int max_connections = 6;
int	max_play_rounds = 1024; // After this you just lose...

/* Function prototypes */
int  RandNum(int min, int max);
int  AddConnection (struct Room * From, struct Room * To, int forward);
void PrintRoom (struct Room * , FILE *fp);
void GenerateRooms(struct Room * array[],  int);
void ConnectRooms(struct Room * array[]);
void PlayGame(struct Room * thisRoom);
void WriteRoomsToFiles(struct Room * createRooms[], char * RoomDir);
void ReadRoomsFromFiles(struct Room * playRooms[], char * RoomDir);
void RemoveDirectory (char * DirectoryName);
struct Room * getNextRoom(struct Room * thisRoom, char *RoomChoice);
struct Room * getRoomByName(struct Room * RoomArray[], int ArraySz, char * MatchName);


/* ******************************************************* */
main(int argc, char** argv) {
	int 		i;
	struct 	Room * createRooms[rooms_in_game];
	struct 	Room * playRooms[rooms_in_game];
	char		RoomDir[25];

	GenerateRooms(createRooms, rooms_in_game);
	ConnectRooms(createRooms);
  sprintf(RoomDir, "abrasss.rooms.%d", getpid());
	FILE_DEBUG && printf ("RoomDir = %s\n", RoomDir);
	WriteRoomsToFiles(createRooms, RoomDir);

	ReadRoomsFromFiles(playRooms, RoomDir);
	if ( ROOM_DEBUG > 0 ) {
		for (i=0; i < rooms_in_game; i++)
			PrintRoom(playRooms[i], NULL);
	}
  PlayGame(createRooms[0]);
	// RemoveDirectory(RoomDir); // Leave this for the TAs top look at

	exit(0);
}

/* ******************************************************* 
 * This function takes a pointer to a Room struct, and
 * uses a do...while loop to control game play. The loop
 * exits when the player reaches the room of type "END_ROOM"
 *
 * ***************************************************** */
void	PlayGame(struct Room * thisRoom)
{
	int i;
	int play_rounds = 0;
	char UserInput[2048];
	char *tmp;
	struct 	Room * roomHistory[max_play_rounds];
	struct 	Room * lastRoom = thisRoom;

	GENERAL_DEBUG && printf ("Starting PlayGame\n");

	memset (UserInput,0, sizeof UserInput);
	memset (roomHistory,0, sizeof roomHistory);

	// Main gameplay control loop
	do {
		if ( thisRoom != lastRoom ) {
			// We've moved, count a step
			roomHistory[play_rounds++] = thisRoom;
			lastRoom = thisRoom;
		}
	  if ( (strcmp (thisRoom->Room_Type, "END_ROOM")) == 0 )
		{
			printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
			printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", play_rounds);
			for (i=0; i < play_rounds; i++)
			{
				printf("%s\n", roomHistory[i]->Room_Name);
			}
			return;
		}
		printf ("CURRENT LOCATION: %s\n", thisRoom->Room_Name);
		printf ("POSSIBLE CONNECTIONS:");
		for (i = 0; i < thisRoom->connections; i++) {
			printf (" %s", thisRoom->Connection[i]->Room_Name);
			if ( i < thisRoom->connections -1 )
				printf (",");
			else
				printf (".\n");
		}
		printf ("WHERE TO? >");
		fgets(UserInput,2047,stdin);
		tmp = UserInput;
		// A small loop to remove trailing newline(s)
		while ( *tmp != '\0')
		{
			if ( *tmp == '\n' ) {
				*tmp = 0;
				break;
			}	
			*tmp++;
		}
		// getNextRoom from UserInput, then continue the loop
	}
	while ( (thisRoom = getNextRoom(thisRoom, UserInput)) != NULL );
}

/* ******************************************************* 
 *
 * Takes the current room and a RoomChoice string; if 
 * RoomChoice is a valid navigation step, return the pointer
 * to the Room struct with that name. Otherwise, print an error 
 * and return the room we're already in (ie, we don't move)
 *
 * ***************************************************** */
struct Room * getNextRoom(struct Room * thisRoom, char *RoomChoice)
{

	int i;

	for (i = 0; i < thisRoom->connections; i++) {
	  if ( (strcmp (thisRoom->Connection[i]->Room_Name, RoomChoice )) == 0 )
		{
			//match
			return ( thisRoom->Connection[i]);
		}
	}
	printf ("HUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
	return (thisRoom);

}

/* ******************************************************* 
 * Generate an array of 7 rooms.
 * Roomnames are chosen at random from the name array.
 * ***************************************************** */
void GenerateRooms(struct Room * gameRooms[], int num_rooms)
{
	struct Room * this_room;
	int room_number;
	char *this_name;
	char *this_type;
	int rooms_used[room_names];
	int	type = 0;
	int name;
	int i;
	int n = 0;

	GENERAL_DEBUG && printf ("Starting GenerateRooms\n");
	srand(time(NULL)); // seed the random number generator
	memset (rooms_used,0, sizeof rooms_used); // zero this array

	for (i=0; i<rooms_in_game; i++)
	{
		this_room = (struct Room *) malloc (sizeof (struct Room));
		this_room->connections = 0;
		/* Find a room we haven't used */
		do {
			room_number = RandNum(0, room_names -1);
		}
		while ( rooms_used[room_number] == 1 );

		rooms_used[room_number] = 1;
		strcpy (this_room->Room_Name, My_Room_Names[room_number]);
		if (type < room_types ){
			strcpy (this_room->Room_Type, Room_Types[type++]);
		}
		else {
			strcpy (this_room->Room_Type, Room_Types[room_types - 1]);
		}

		gameRooms[n++] = this_room;
	}

}


/* ******************************************************* 
 * Take an array of Room pointers, and create connections
 * between rooms for navigation.
 * A room will have between 3 and 6 connections.
 *
 * ***************************************************** */
void	ConnectRooms(struct Room * gameRooms[])
{
	int num_connections;
	int try_to_connect;
	int i; // outer loop
	int j; // inner loop
	int n; // loop for checking existing connections
	int result;
	struct Room * this_room;
	struct Room * connecting_room;

	GENERAL_DEBUG && printf ("Starting ConnectRooms\n");

	srand(time(NULL)); // seed the random number generator
	for (i=0; i < rooms_in_game; i++)
	{
		num_connections = RandNum(min_connections, max_connections);
		this_room = gameRooms[i];
		LOGIC_DEBUG && printf ("i = %d\n", i);
		LOGIC_DEBUG && printf ("Working on %s\n", this_room->Room_Name);
		LOGIC_DEBUG && printf ("num_connections = %d\n", num_connections);
		LOGIC_DEBUG && printf ("existing connections = %d\n", this_room->connections);

		if ( this_room->connections >= max_connections)
			continue;
		if ( this_room->connections >= num_connections)
			continue;
	
		// Generate num_connections 
		n = num_connections - this_room->connections;
		if ( n == 0 ) continue;
		for (j=0; j < n; j++) {

			LOGIC_DEBUG && printf ("j = %d\n", j);
			do 
			{
				try_to_connect = RandNum(0, rooms_in_game - 1);	
				LOGIC_DEBUG && printf ("try_to_connect = %d\n", try_to_connect);
				result = AddConnection(this_room, gameRooms[try_to_connect], 1);
			}
			while ( result == 1 );

			//AddConnection(gameRooms[try_to_connect], this_room);
		}
	}
}

/* ******************************************************* 
 * A helper function for ConnectRooms.
 * Attempts to create connections between two rooms; fails if one
 * of the rooms has max_connections, or if the connection already
 * exists.
 *
 * If it succeeds in making a forward connection 
 * from room A to room B, it immediately makes the reverse connection
 * from room B to room A.
 *
 * ***************************************************** */
int  AddConnection (struct Room * RoomFrom, struct Room * RoomTo, int forward)
{
	int i;
	int matches;

	GENERAL_DEBUG && printf ("Starting AddConnection, forward = %d\n", forward);
	if (forward == 1 ) {
		matches = ( strcmp(RoomFrom->Room_Name, RoomTo->Room_Name));
		if ( matches == 0 )
		{
			LOGIC_DEBUG && printf ("++ fail can't connect to self\n");
			return(1);
		}
		if ( RoomFrom->connections >= max_connections )
		{
			LOGIC_DEBUG && printf ("++ fail RoomFrom connections >= max_connections\n");
			return (1);
		}
		if ( RoomTo->connections >= max_connections ) 
		{
			LOGIC_DEBUG && printf ("++ fail RoomTo connections >= max_connections\n");
			LOGIC_DEBUG && printf ("RoomTo->RoomName = %s, RoomTo->connections = %d, max_connections=%d\n", RoomTo->Room_Name, RoomTo->connections, max_connections);
			return (1);
		}

		// If these rooms are already connected, return an error: can't add this.
		// Or return success? Not while we subtract existing connections from
		// connect count (line 283)
		for (i=0; i < RoomFrom->connections; i++)
		{
			matches = ( strcmp((RoomFrom->Connection[i])->Room_Name, RoomTo->Room_Name) );
			if ( matches == 0 )
			return(1);
		}
  }

	RoomFrom->Connection[RoomFrom->connections] = RoomTo;
	RoomFrom->connections++;
	if (forward == 1 )
		AddConnection ( RoomTo, RoomFrom, 0);

	return(0);
}

/* ******************************************************* 
 * Save the randomly generated rooms out to files
 * ***************************************************** */
void WriteRoomsToFiles(struct Room * gameRooms[], char * RoomDir)
{
	int i,r;
	int result;
	FILE * File;
	char FileName[40];
	struct stat *FileStat;
	
	GENERAL_DEBUG && printf ("Starting WriteRoomsToFiles\n");

	result = mkdir (RoomDir, S_IRWXU | S_IRWXG);

	for (i=0; i < rooms_in_game; i++)
	{
  	sprintf(FileName, "%s/Roome_%d", RoomDir, i);
		FILE_DEBUG && printf ("    Creating file named %s\n", FileName);
		File = fopen (FileName, "w");
		// TODO: check result
		if (File == NULL)
			printf ("There has been a terrible failure of the space-time continuum...\n");
		PrintRoom(gameRooms[i], File);
		// TODO: check result
		fclose(File);
	}

	if (FILE_DEBUG == 2 )
	{
		char * buffer;
		buffer = (char *) malloc (1024 * sizeof(char));
		FileStat = (struct stat *) malloc (sizeof (struct stat));
		for (i=0; i < rooms_in_game; i++)
		{
  		sprintf(FileName, "%s/Roome_%d", RoomDir, i);
			FILE_DEBUG && printf ("    Testing file named %s\n", FileName);
			if ( ( r  = stat (FileName, FileStat)) != 0 )
			{
				printf ("stat %s: errno %d\n", FileName, errno);
				perror(FileName);
			}
			else
			{
				FILE_DEBUG && printf ("    size = %d\n", FileStat->st_size);
			}
			File = fopen (FileName, "r");
			if (File == NULL)
				printf ("There has been a terrible failure of the space-time continuum...\n");
			fgets (buffer, 1023, (FILE *) File);
			printf ("     buf: %s\n", buffer);
			fclose(File);
		}
	}
}
/* ******************************************************* 
 *
 * Read the saved room files and use them to fill a Room array.
 * This is the array that will be used to play the game.
 *
 * ***************************************************** */
void ReadRoomsFromFiles(struct Room * playRooms[], char * RoomDir)
{
	int 	n=0,c=0;
	int 	room_number;
	int		matches;
	char  tmpstr[2048];
	char	pathname[2048];
	char	*buffer;
	char 	*tmpptr;
	size_t	sz;
	struct Room * this_room;
	struct Room * connect_room;
	DIR	* dirp;
	FILE * fp;
	struct dirent * RoomListing;

	GENERAL_DEBUG && printf ("Starting ReadRoomsFromFiles\n");

	buffer = (char *) malloc (2048 * (sizeof (char)));

	if ( ( dirp = opendir (RoomDir)) == NULL )
	{
		perror (RoomDir);
		// TODO: exit
	}
	RoomListing = readdir (dirp);
	while (( RoomListing = readdir ( dirp ) ) != NULL )
	{
		// TODO
		/* this code is reusable \/ */
		if ((strncmp ( RoomListing->d_name, "Roome_", 6)) != 0 )
		{
			ROOM_DEBUG && printf ("found unuseful filename |%s|\n", RoomListing->d_name);
			continue;
		}
		memset (pathname, 0, sizeof pathname);
		sprintf (pathname, "%s/%s", RoomDir, RoomListing->d_name);
		ROOM_DEBUG && printf ("opening file named |%s|\n", pathname);
		fp = fopen (pathname, "r");
		if ( fp == NULL)
		{
			perror(pathname);
		}

		/* Now read the file into the room struct */
		memset (buffer, 0, sizeof buffer);
		this_room = (struct Room *) malloc (sizeof (struct Room));
		this_room->connections = 0;
		c = 0;
		/* this code is reusable /\ */
		while (( fgets(buffer, 2047, (FILE *) fp)) != NULL )
		{
			tmpptr = buffer;
			while ( *tmpptr != '\0')
			{
				if ( *tmpptr == '\n' ) {
					*tmpptr = 0;
					break;
				}	
				*tmpptr++;
			}
			FILE_DEBUG && printf ("read buffer |%s|\n", buffer);
			if ((strncmp ( buffer, "ROOM NAME:", 10)) == 0 )
			{
				strcpy(this_room->Room_Name, (buffer + 11 * (sizeof(char))));
				ROOM_DEBUG && printf ("Found room name|%s|\n", this_room->Room_Name);
			}
			else if ((strncmp ( buffer, "CONNECTION", 10)) == 0 )
			{
				//strcpy(this_room->Connection[c], (buffer + 14 * (sizeof(char))));
				ROOM_DEBUG && printf ("Found connection |%s|\n",(buffer + 14 * (sizeof(char))));
				c++;
			}
			else if ((strncmp ( buffer, "ROOM TYPE:", 10)) == 0 )
			{
				strcpy(this_room->Room_Type, (buffer + 11 * (sizeof(char))));
				ROOM_DEBUG && printf ("Found room type|%s|\n", this_room->Room_Type);
			}
			else 
			{
				fprintf(stderr, "Found unparseable file line, ignoring\n");
				fprintf(stderr, "   (%s)\n", buffer);
			}
			memset (buffer, 0, sizeof buffer);
		}
		fclose(fp);
		playRooms[n++] = this_room;
	}

	/* Now read all the files again and add the room connections */
	rewinddir(dirp);
	RoomListing = readdir (dirp);
	while (( RoomListing = readdir ( dirp ) ) != NULL )
	{
		/* this code is reusable \/ */
		if ((strncmp ( RoomListing->d_name, "Roome_", 6)) != 0 )
		{
			CONNECT_DEBUG && printf ("found unuseful filename |%s|\n", RoomListing->d_name);
			continue;
		}
		memset (pathname, 0, sizeof pathname);
		sprintf (pathname, "%s/%s", RoomDir, RoomListing->d_name);
		CONNECT_DEBUG && printf ("Connecting pass: opening file named |%s|\n", pathname);
		fp = fopen (pathname, "r");
		if ( fp == NULL)
		{
			perror(pathname);
		}
		/* this code is reusable /\ */


		CONNECT_DEBUG && printf ("Connecting pass: trying now\n");
		this_room = NULL;
		while (( fgets(buffer, 2047, (FILE *) fp)) != NULL )
		{
			tmpptr = buffer;
			while ( *tmpptr != '\0')
			{
				if ( *tmpptr == '\n' ) {
					*tmpptr = 0;
					break;
				}	
				*tmpptr++;
			}
			CONNECT_DEBUG && printf ("Connecting pass: read buffer |%s|\n", buffer);
			if ((strncmp ( buffer, "ROOM NAME:", 10)) == 0 )
			{
				strcpy(tmpstr, (buffer + 11 * (sizeof(char))));
				this_room = getRoomByName(playRooms, rooms_in_game, tmpstr);
				CONNECT_DEBUG && printf ("Connecting pass: found room name|%s|\n", this_room->Room_Name);
			}
			else if ((strncmp ( buffer, "CONNECTION", 10)) == 0 )
			{
				strcpy(tmpstr, (buffer + 14 * (sizeof(char))));
				connect_room = getRoomByName(playRooms, rooms_in_game, tmpstr);
				// TODO: check for error
				this_room->Connection[this_room->connections++] = connect_room;
				CONNECT_DEBUG && printf ("Connecting pass: Found connection |%s|\n",(buffer + 14 * (sizeof(char))));
			}
		}
		fclose(fp);
	}
	GENERAL_DEBUG && printf ("Finishing ReadRoomsFromFiles\n");
}

/* ******************************************************* 
 *
 * A helper function that prints out a Room's information
 *
 * ***************************************************** */
void PrintRoom (struct Room * this_room, FILE * File)
{
	int  i=0;

  if (File == NULL ) 
		File = stdout;

	//fprintf(File, "================\n");
	//fprintf(File, "connections: %d\n", this_room->connections);
	// TODO: check result
	fprintf(File, "ROOM NAME: %s\n", this_room->Room_Name);
	while ( i < this_room->connections)
	{
		fprintf(File, "CONNECTION %d: %s\n", i, (this_room->Connection[i])->Room_Name);
		i++;
	}
	
	fprintf(File, "ROOM TYPE: %s\n", this_room->Room_Type);
}

/* ******************************************************* 
 *
 * Returns a Room pointer for the room that matches a given name.
 *
 * ***************************************************** */
struct Room * getRoomByName(struct Room * RoomArray[], int ArraySz, char * MatchName)
{
	int n;

	CONNECT_DEBUG && printf ("Starting getRoomByName matching %s\n", MatchName);
	for (n=0; n<ArraySz; n++)
	{
		CONNECT_DEBUG && printf ("Comparing %s\n", RoomArray[n]->Room_Name);
		if ((strcmp(RoomArray[n]->Room_Name, MatchName)) == 0 ){
			CONNECT_DEBUG && printf ("Ending getRoomByName with valid pointer\n");
			return (RoomArray[n]);
		}
	}
	CONNECT_DEBUG && printf ("Ending getRoomByName with NULL pointer\n");
	return (NULL);
}

/* ******************************************************* 
 *
 * Clean things up. Not used for this assignment.
 *
 * ***************************************************** */
void RemoveDirectory (char * DirectoryName)
{
	DIR	* dirp;
	struct dirent * DirListing;
	char pathname[2048];

	GENERAL_DEBUG && printf ("Starting RemoveDirectory\n");

	if ( ( dirp = opendir (DirectoryName)) == NULL )
	{
		perror (DirectoryName);
		// TODO: exit
	}
	DirListing = readdir (dirp);
	while (( DirListing = readdir ( dirp ) ) != NULL )
	{
		if (((strcmp ( DirListing->d_name, ".")) == 0) 
			|| ((strcmp ( DirListing->d_name, ".."))==0) )
		{
			ROOM_DEBUG && printf ("found unremovable file |%s|\n", DirListing->d_name);
			continue;
		}
		sprintf (pathname, "%s/%s", DirectoryName, DirListing->d_name);
		if ( (unlink ( pathname )) != 0 )
		{
			perror (pathname); 
			// TODO: exit? probably not; keep going
		}
	}
	if ( (rmdir (DirectoryName )) != 0 )
	{
			perror (DirectoryName); 
	}
}
	
/* ******************************************************* 
 * Return a random number between min and max, inclusive
 * ***************************************************** */
int  RandNum(int min, int max)
{
	int maxPlus = max + 1;
	return (( rand() % (maxPlus - min) ) + min);
}

