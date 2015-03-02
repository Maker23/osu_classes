// vim: ts=2 
#include <iostream>
#include <cstdlib>
#include <set>			// STL set container
#include <list>			// STL list container
#include <cfloat>		// for the getIntFromUser function
#include <climits>	// for the getIntFromUser function
#include <sstream>	// for the getIntFromUser function

#include "Flags.h"
#include "Dice.h"
#include "Player.h"
#include "Character.h"

// Function prototypes
int Combat (Character & One, Character & Two);
int getIntFromUser(std::string Prompt, int DefaultAnswer, int MinRange, int MaxRange );
std::string getAGoodName(int & offset, CharType type);
void printUserMenu();
void getRoster (Player & myPlayer, int numCharacters, int seed);
void FighterScore (std::set<Character*> &allFighters);
void PlayerScore (Player * PlayerOne, Player* PlayerTwo, std::set<Character*> &allFighters);
void ReleaseMemory (std::set<Character*> &allFighters);

enum MenuChoice { Gob, Barb, Blu, Rept, Shad, unknown };
MenuChoice getUserMenuChoice(std::string PlayerName);

// Max 12 unless you add to the TestRoster below
#define TEST_ROSTER_SIZE 12


/* ********************************************************* */
int main()
{
	int numFighters;
	std::string buffer;
	std::set <Character*> allFighters;
  srand(time(NULL));

	Player PlayerOne("PlayerOne");
	Player PlayerTwo("PlayerTwo");

	// Create player rosters (lineups), interactively or from test data
  if (TEST)
	{
		numFighters = TEST_ROSTER_SIZE;
		getRoster(PlayerOne, numFighters, 0);
		getRoster(PlayerTwo, numFighters, 1);
	}
	else
	{
		numFighters = getIntFromUser(
			"How many fighters should each player have? (1-100)", 5, 1, 100);
		getRoster(PlayerOne, numFighters, rand() % (size_t)&PlayerOne);
		getRoster(PlayerTwo, numFighters, rand() % (size_t)&PlayerTwo);
	}

	// Get ready to rumble!
  PlayerOne.Print();
  PlayerTwo.Print();
	std::cout << std::endl << "Hit return to begin the tournament: ";
	getline(std::cin, buffer);

	Character* FighterOne = PlayerOne.NextFighter();
	Character* FighterTwo = PlayerTwo.NextFighter();

  // As long as both players have at least one fighter, keep going
  while ( FighterOne && FighterTwo)
	{
		Combat( *FighterOne, *FighterTwo);

		(FighterOne->getHealth() <= 0) ? 
			PlayerOne.RetireFighter(FighterOne) : FighterOne->scoreAgainst(FighterTwo);
		(FighterTwo->getHealth() <= 0) ? 
			PlayerTwo.RetireFighter(FighterTwo) : FighterTwo->scoreAgainst(FighterOne);

		if ( (! (ASSIGNMENT || TEST )) && VERBOSE ) 
		{
			// For the assignment we just keep going, but otherwise it's
			// nice to pause between bouts to look at the score
			PlayerOne.Print();
  		PlayerTwo.Print();
			std::cout << std::endl << "Hit return to continue the tournament: ";
			getline(std::cin, buffer);
		}
	
		// Add to the set for scoring the tournament later
		allFighters.insert(FighterOne); 
		allFighters.insert(FighterTwo);

		FighterOne = PlayerOne.NextFighter();
		FighterTwo = PlayerTwo.NextFighter();
	}

	if ( VERBOSE )
	{
		std::cout << std::endl << "*******" << "   Fighter statistics   " 
			<< "*******" << std::endl << std::endl;
 		PlayerOne.Print();
 		PlayerOne.PrintGraveyard();
 		PlayerTwo.Print();
 		PlayerTwo.PrintGraveyard();
	}
	// Print fighter and player scores
	FighterScore(allFighters);
	PlayerScore(&PlayerOne, &PlayerTwo, allFighters);
	ReleaseMemory(allFighters);
}

/* ********************************************************* */
void PlayerScore (
Player * PlayerOne, 
Player* PlayerTwo, 
std::set<Character*> &allFighters)
{
	Character* tmpCharacter;
	std::set<Character*>::iterator iterS;
	
	for (iterS = allFighters.begin(); iterS != allFighters.end(); iterS++)
	{
		if ((*iterS)->getPlayer() == PlayerOne ) 
			PlayerOne->setScore(PlayerOne->getScore() + (*iterS)->getScore());
		else if ((*iterS)->getPlayer() == PlayerTwo ) 
			PlayerTwo->setScore(PlayerTwo->getScore() + (*iterS)->getScore());
	}
  
	std::cout << std::endl << "*********" << "  Player rankings   " 
		<< "*********" << std::endl << std::endl;
	if (PlayerOne->getScore() > PlayerTwo->getScore())
		std::cout << PlayerOne->getName() << " wins the tournament!" << std::endl;
	else if (PlayerTwo->getScore() > PlayerOne->getScore())
		std::cout << PlayerTwo->getName() << " wins the tournament" << std::endl;
	else 
		std::cout << "The tournament is a tie!" << std::endl;

	std::cout << std::endl << "Overall scores: " << std::endl;
	std::cout << "	" << PlayerOne->getName() << ": " << PlayerOne->getScore() << std::endl;
	std::cout << "	" << PlayerTwo->getName() << ": " << PlayerTwo->getScore() << std::endl;
}

/* ********************************************************* */
void FighterScore (std::set<Character*> &allFighters)
{
	Character* tmpCharacter;
	std::list<Character*> rankedList;
	std::list<Character*>::iterator iterL;
	std::set<Character*>::iterator iterS;
	
	for (iterS = allFighters.begin(); iterS != allFighters.end(); iterS++)
	{
		if ( rankedList.size() == 0 )
		{
			rankedList.push_front(*iterS);
		}
		else
		{
			for (iterL = rankedList.begin(); iterL != rankedList.end(); iterL++)
			{
				if ( (*iterS)->getScore() >= (*iterL)->getScore() )
				{
					rankedList.insert(iterL, *iterS);
					break;
				}
			}
			if ( iterL == rankedList.end() )
			{
				rankedList.push_back(*iterS);
			}
		}
	}
	if (DEBUG)
	{
		for (iterL = rankedList.begin(); iterL != rankedList.end(); iterL++)
		{
			std::cout << (*iterL)->getName() << "	" << (*iterL)->getScore() << std::endl;
		}
	}

  if (rankedList.size() == 0 )
		return; // This shouldn't really happen

	std::cout << std::endl << "*********" << "  Fighter rankings  " 
		<< "*********" << std::endl << std::endl;
	iterL = rankedList.begin();
	std::cout << "First place goes to " << (*iterL)->getName() 
		<< " with	" << (*iterL)->getScore() << " points" 
		<< " (" << ((Player*)(*iterL)->getPlayer())->getName() << ")"
		<< std::endl;
	iterL++;
	std::cout << "Second place goes to " << (*iterL)->getName() 
		<< " with	" << (*iterL)->getScore() << " points" 
		<< " (" << ((Player*)(*iterL)->getPlayer())->getName() << ")"
		<< std::endl;

  if (rankedList.size() < 3)
		return;
	iterL++;
	std::cout << "Third place goes to " << (*iterL)->getName() 
		<< " with	" << (*iterL)->getScore() << " points" 
		<< " (" << ((Player*)(*iterL)->getPlayer())->getName() << ")"
		<< std::endl;
}

/* ********************************************************* */
void getRoster (Player & myPlayer, int numCharacters, int Seed)
{
	MenuChoice nextChoice;
	Character * myFighter; 
	int rSeed;
	std::string Name;
	std::string tmpString;

	// This is the pre-defined player lineup for automated testing
	MenuChoice TestRosters[2][12] = {
		{Gob,Barb,Blu,Rept,Shad,Gob ,Barb,Blu ,Rept,Shad,Blu ,Barb},
		{Gob,Barb,Blu,Rept,Shad,Barb,Blu ,Rept,Shad,Gob ,Shad,Shad},
	};

  if (TEST)
		rSeed = Seed + (Seed*numCharacters);
	else
		rSeed = Seed % 10;

	printUserMenu();
	for (int i = 0; i< numCharacters; i++)
	{
		nextChoice = unknown;
		do 
		{
			if (TEST)
				nextChoice = TestRosters[Seed][i];
			else
				nextChoice = getUserMenuChoice( myPlayer.getName());
			switch (nextChoice){
				case Gob:
					Name = getAGoodName( rSeed, (CharType)GOBLIN);
					myFighter = new Goblin(Name);
					break;
				case Barb:
					Name = getAGoodName( rSeed, (CharType)BARBARIAN);
					myFighter = new Barbarian(Name);
					break;
				case Blu:
					Name = getAGoodName( rSeed, (CharType)BLUECHIX);
					myFighter = new BlueChix(Name);
					break;
				case Rept:
					Name = getAGoodName( rSeed, (CharType)REPTILE);
					myFighter = new ReptilePeople(Name);
					break;
				case Shad:
					Name = getAGoodName( rSeed, (CharType)SHADOW);
					myFighter = new Shadow(Name);
					break;
				default:
					std::cout << "Unrecognized option, try again" << std::endl;
					break;
			}
		}
		while (nextChoice == unknown);
		myFighter->setPlayer(&myPlayer);
		myPlayer.AddFighter(myFighter);
		rSeed++;
	}
}

/* ********************************************************* 
 * enum MenuChoice { Goblin, Barbarian, BlueChix, Reptile, Shadow, unknown };
 * char MenuOptions[] = {'G','B','C','R','S'};
 ********************************************************* */
void printUserMenu()
{
	std::cout << std::endl <<
		"[G]oblin" << std::endl <<
		"[B]arbarian" << std::endl <<
		"blue[C]hix" << std::endl <<
		"[R]eptile" << std::endl <<
		"[S]hadow" << std::endl << std::endl <<
		"Which character do you want to add to your line up? "<< std::endl;
}
MenuChoice getUserMenuChoice( std::string PlayerName)
{
	MenuChoice menuChoice;
	char inputBuffer[1024];
	char MenuOptions[] = {'G','B','C','R','S'};
	char MenuOption;

	std::cout << PlayerName << "  (G,B,C,R,S): ";
  MenuOption = std::cin.get(); // get the first character
	std::cin.getline(inputBuffer,1024); // throw away anything else they typed

	for (int i=0; i<5; i++)
	{
		if (toupper(MenuOption) == MenuOptions[i])
		{
			menuChoice = (MenuChoice) i;
			return (menuChoice);
		}
	}
	return (unknown);
}
/*****************************************************************/
std::string getStringFromUser(std::string Prompt, std::string DefaultAnswer)
{
	std::string tmpString = "";
	do
	{
		std::cout << Prompt ;
		if (DefaultAnswer.compare("") != 0 )
		{
			std::cout << " [" << DefaultAnswer << "]";
		}
		std::cout << ": ";
		getline(std::cin,tmpString);
		if ( (tmpString.compare("") == 0) && (DefaultAnswer.compare("") != 0 ))
		{
			tmpString = DefaultAnswer;
		}
	}
	while ( tmpString.compare("") == 0 );
	return (tmpString);
}
/*****************************************************************/
int getIntFromUser(std::string Prompt, int DefaultAnswer, int MinRange, int MaxRange )
{
	//std::stringstream ss;
	std::string tmpString = "";
	float tmpFloat = FLT_MIN;
	int tmpInt = INT_MIN;
	bool Good = false;

	do {
		std::cout << Prompt ;
		std::cout << " [" << DefaultAnswer << "]";
		std::cout << ": ";
		getline(std::cin,tmpString);
		if (tmpString.compare("") == 0) 
		{
			tmpFloat = DefaultAnswer;
			tmpInt = (int)tmpFloat;
		}
		else 
		{
			std::stringstream ss(tmpString);
			ss << tmpString;
			ss >> tmpFloat;
			if ( ss.fail() )
			{
				std::cout << "Error: input \"" << tmpString 
					<< "\" was not a number; try again" << std::endl;
				continue;
			}
			else {
				tmpInt = (int)tmpFloat;
				if ( (float)tmpInt != tmpFloat )
				{
					std::cout << "Error: input \"" << tmpFloat 
						<< "\" was not an integer; try again" << std::endl;
					continue;
				}
			}
		}
		if (tmpInt >= MinRange && tmpInt <= MaxRange) 
			Good=true;
		else 
		{
			std::cout << "Error: Number is out of range (" 
				<< MinRange << "-" << MaxRange << ")" << std::endl;
		}

	}
	while ( ! Good );

	return (tmpInt);
}

// enum CharType {GOBLIN,BARBARIAN,REPTILE,BLUECHIX,SHADOW};
std::string getAGoodName(int & offset, CharType type)
{
	int maxNames = 10;
	int pickAName = abs(10 - offset);
	std::string Prompt;
	std::string defaultName;

  std::string Classes[5] = {"Goblin", "Barbarian", "Reptile", "Blue Chix", "Shadow"};

	std::string Names[5][10] = 
	{
  	{"Bolg", "Grumpy", "Gorthagnia", "Gerramonde", "Ginny", 
		 "Gorbagh", "Galadriel", "Gufnes", "Gibber", "Gunnar"}, 
		{"Conan", "Connie", "Belladonna", "Barbie", "Blodhwin",
		 "Eomer", "Genghis", "Gilgamesh", "Boudica", "Enkidu"},
		{"Slithy", "Sesquipedial", "Susurrus", "Slippy", "Slidy",
		 "Snarkblat", "Squandry", "Simpleton", "Snopes", "Srachan"},
		{"Aqua", "Cerulea", "Indigo", "Marina", "Laguna",
		 "Etherea", "Tealie", "Steel", "Violet", "Sapphire"},
 		{"Gray", "Shade", "Darkness", "Twilight", "Cloud",
		 "Tenebrae", "Smoke", "Fog", "Ember", "Pall"}
	};

	if (TEST) 
		defaultName = Classes[type] + "_" + std::to_string((long long)offset); 
	else if ((pickAName > maxNames) || TEST) 
		defaultName = Classes[type] + "_" + std::to_string((long long)pickAName); 
  else
		defaultName = Names[type][pickAName] + " the " + Classes[type];

	if (! TEST)
	{
		Prompt = "Choose a name for your " + Classes[type];
		return (getStringFromUser(Prompt, defaultName));
	}
	else
	{
		return(defaultName);
	}
	//return Names[type][pickAName];
		
}

/* ********************************************************* */
void ReleaseMemory (std::set<Character*> &allFighters)
{
	Character* tmpCharacter;
	std::set<Character*>::iterator iterS;
	
	for (iterS = allFighters.begin(); iterS != allFighters.end(); iterS++)
	{
		delete (*iterS);
	}
}
