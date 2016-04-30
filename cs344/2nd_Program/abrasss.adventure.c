/*
 * vim: ts=2 
 *
 * Description: 
 * Submit a program named <username>.adventure.c.
 * It will be compiled using this line, with my username as the example: 
 * 
 * %gcc –o brewsteb.adventure brewsteb.adventure.c
 *
 * Do not use the -C99 standard or flag when compiling 
 */

#include <stdio.h>
#include <stdlib.h> // For random numbers
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

#define FILE_DEBUG 1
#define LOGIC_DEBUG 0
#define ROOM_DEBUG 0
#define GENERAL_DEBUG 0

struct Room 
{
	int	 connections;
	char Room_Name[32];
	char Room_Type[16];
	struct Room * Connection[6];
};

const char * My_Room_Names[] =
{
// Name length is limited to 31 characters plus NULL
// 1234567890123456789012345678901
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
	"Mechanicsberg coffee house",		// 12
	"South Pole",										// 13
	"MMORPG command center",				// 14
};
const char * Room_Types[] =
{
	"START_ROOM",
	"END_ROOM",
	"MID_ROOM",
};

int room_names = 15;
int room_types = 3;
int rooms_in_game = 7;
int min_connections = 3;
int max_connections = 6;


int  RandNum(int min, int max);
void PrintRoom (struct Room * , FILE *fp);
void GenerateRooms(struct Room * array[],  int);
void ConnectRooms(struct Room * array[]);
void WriteRoomsToFiles(struct Room * createRooms[], char * RoomDir);
void ReadRoomsFromFiles(struct Room * playRooms[], char * RoomDir);
int  AddConnection (struct Room * From, struct Room * To, int forward);
void RemoveFiles(char * RoomDir);
/* ******************************************************* */
main(int argc, char** argv) {
	int 		i;
	struct 	Room * createRooms[rooms_in_game];
	struct 	Room * playRooms[rooms_in_game];
	char		RoomDir[25];

	GenerateRooms(createRooms, rooms_in_game);
	ConnectRooms(createRooms);
	if (ROOM_DEBUG == 1 ) {
		for (i=0; i < rooms_in_game; i++)
			PrintRoom(createRooms[i], NULL);
	}
  sprintf(RoomDir, "abrasss.rooms.%d", getpid());
	FILE_DEBUG && printf ("RoomDir = %s\n", RoomDir);
	WriteRoomsToFiles(createRooms, RoomDir);

	ReadRoomsFromFiles(playRooms, RoomDir);

/*
 * File IO: 
 * 	bool WriteRoomsToFiles(createRooms);
 * 	Room * [] ReadRoomsFromFiles();
 * 	IsConnected(Room *, Room *)
 *
 * User interaction:
 * 	bool PlayGame(gameRooms);
 * 	void ListConnections(Room *, Room *)
 * 	Room * Get_room_by_name (string room_name)
 *  			 Get_room (Room * pointer)
 */


	exit(0);
}

void GenerateRooms(struct Room * gameRooms[], int num_rooms)
{
	/* *******************************************************
	 * Choose a list of ten different Room Names, hard coded into your program, 
	 * and have your program randomly assign a room name to each room generated. 
	 * For a given run of your program, 7 of the 10 room names will be used. 
	 * Note that a room name cannot be used to in more than one room
	 */
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
		// Or return success?  TBD
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

void WriteRoomsToFiles(struct Room * gameRooms[], char * RoomDir)
{
	int i;
	int result;
	FILE * File;
	char FileName[40];
	
	GENERAL_DEBUG && printf ("Starting WriteRoomsToFiles\n");

	result = mkdir (RoomDir, S_IRWXU);

	for (i=0; i < rooms_in_game; i++)
	{
  	sprintf(FileName, "%s/Roome_%d", RoomDir, i);
		FILE_DEBUG && printf ("    Would create file named %s\n", FileName);
		File = fopen (FileName, "w");
		// TODO: check result
		if (File == NULL)
			printf ("There has been a terrible failure of the space-time continuum...\n");
		PrintRoom(gameRooms[i], File);
		// TODO: check result
		close(File);
	}
}
void ReadRoomsFromFiles(struct Room * gameRooms[], char * RoomDir)
{
	/* *******************************************************
	 * Choose a list of ten different Room Names, hard coded into your program, 
	 * and have your program randomly assign a room name to each room generated. 
	 * For a given run of your program, 7 of the 10 room names will be used. 
	 * Note that a room name cannot be used to in more than one room
	 */
	int 	n=0;
	int 	room_number;
	int		matches;
	char  this_field[40];
	char  this_value[40];
	struct Room * this_room;
	DIR	* RoomDirectory;
	FILE * RoomFile;
	struct dirent * RoomListing;

	GENERAL_DEBUG && printf ("Starting ReadRoomsFromFiles\n");

	RoomDirectory = opendir (RoomDir);
	RoomListing = readdir (RoomDirectory);
	FILE_DEBUG && printf ("readdir succeeded\n");
	// TODO: check for failure
	while (RoomListing != NULL) { 
		RoomListing = readdir (RoomDirectory);
		matches = strncmp(RoomListing->d_name, "Roome_",6 );
		// Ignore files that don't match the pattern
		if (matches != 0) 
			continue;

		/* Open the file */
		FILE_DEBUG && printf ("opening file %s\n", RoomListing->d_name);
		RoomFile = fopen ( RoomListing->d_name, "r");
		//fscanf( RoomFile, "%[^:]:%s", this_field, this_value);
		/* Read the contents of the file into the struct */

		this_room = (struct Room *) malloc (sizeof (struct Room));
		//this_room->connections = 0;
		//strcpy (this_field, this_room->Room_Name);
		
		gameRooms[n++] = this_room;
	}
	GENERAL_DEBUG && printf ("Finishing ReadRoomsFromFiles\n");
}

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
	
int  RandNum(int min, int max)
{
	int maxPlus = max + 1;
	return (( rand() % (maxPlus - min) ) + min);
}

/* *******************************************************
	 * The first thing your program must do is generate 7 different room files
	 * , one room per file, in a directory called <username>.rooms.<process
	 * id>. You get to pick the names for those files, which should be 
	 * hard-coded into your program. For example, the directory, if I was writing
	 * the program, should be hard-coded (except for the process id number), as: 
	 * 
	 * abrasss.rooms.$PID
	 * 
	 * Each room has a Room Name, at least 3 outgoing connections (and at
	 * most 6 outgoing connections, where the number of outgoing connections
	 * is random) from this room to other rooms, and a room type. The connections
	 * from one room to the others should be randomly assigned – i.e. which
	 * rooms connect to each other one is random - but note that if room A
	 * connects to room B, then room B must have a connection back to room A. 
	 * Because of these specs, there will always be at least one path through. 
	 * Note that a room cannot connect to itself.
	 * 
	 * Each file that stores a room must have exactly this form, where the … is 
	 * additional room connections, as randomly generated:
	 * 
	 * ROOM NAME: <room name>
	 * CONNECTION 1: <room name>
	 * …
	 * ROOM TYPE: <room type>
	 * 
	 * The possible room type entries are: START_ROOM, END_ROOM, and MID_ROOM. 
	 * The assignment of which room gets which type should be random. Naturally, 
	 * only one room should be assigned as the start room, and only one
	 * room should be assigned as the end room.
*/



	/* GENERATE ROOMS **************************************************** /
	
	/* *******************************************************
	 * Upon being executed, after the rooms are generated, the game should
	 * present an interface to the player. Note that the room data must be
	 * read back into the program from the files, for use by the game. You
	 * can either do all of this reading immediately after writing them,
	 * or read each file in as needed in the course of the game.
	 *
	 */
	/* *******************************************************
	 * The interface should list where the player current is, and list the
	 * possible connections that can be followed. It should also then have
	 * a prompt. Here is the form that must be used:
	 *
	 * CURRENT LOCATION: XYZZY
	 * POSSIBLE CONNECTIONS: PLOVER, Dungeon, twisty.
	 * WHERE TO? >
	 *
	 * The cursor should be placed just after the > sign. Note the punctuation
	 * used: colons on the first two lines, commas on the second line, and
	 * the period on the second line. All are required.
	 */
	/* *******************************************************
	 *
	 * When the user types in the exact name of a connection to another room
	 * (Dungeon, for example), and then hits return, your program should
	 * write a new line, and then continue running as before. For example, 
	 * if I typed twisty above, here is what the output should look like:
	 *
	 * 	CURRENT LOCATION: XYZZY
	 * 	POSSIBLE CONNECTIONS: PLOVER, Dungeon, twisty.
	 * 	WHERE TO? >twisty
	 *
	 * If the user types anything but a valid room name from this location
	 * (case matters!), the program should return an error line that says
	 * “HUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.”, and repeat the current
	 * location and prompt, as follows:
	 *
	 * 	CURRENT LOCATION: XYZZY
	 * 	POSSIBLE CONNECTIONS: PLOVER, Dungeon, twisty.
	 * 	WHERE TO? >Twisty
	 *
	 * 	HUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.
	 *
	 */
	/* *******************************************************
	 * Trying to go to an incorrect location does not increment the path
	 * history or the step count. Once the user has reached the End Room, 
	 * the program should indicate that it has been reached. It should
	 * also print out the path the user has taken to get there, the number
	 * of steps, and a congratulatory message. Here is a complete game example, 
	 * showing the winning messages and formatting, and the return to the
	 * prompt:
	 *
	 *	YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!
	 *	YOU TOOK 2 STEPS. YOUR PATH TO VICTORY WAS:
	 *	twisty
	 *	Dungeon
	 *	%
	 *
	 * Note the punctuation used: I expect the same punctuation in your program.
	 *
	 */
