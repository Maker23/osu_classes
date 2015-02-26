#include <iostream>
#include <cstdlib>
#include <typeinfo>
// for the getInteger function
#include <cfloat>
#include <climits>
#include <sstream>
#include <set>
#include <list>

#include "Flags.h"
#include "Dice.h"
#include "Player.h"
#include "Character.h"

enum MenuChoice { Gob, Barb, Blu, Rept, Shad, unknown };
char MenuOptions[] = {'G','B','C','R','S'};

int Combat (Character & One, Character & Two);
int getIntFromUser(std::string Prompt, int DefaultAnswer, int MinRange, int MaxRange );
std::string getAGoodName(int & offset, CharType type);
void getRoster (Player & myPlayer, int numCharacters, int seed);
void Score (std::set<Character*> &allFighters);

void printUserMenu();
MenuChoice getUserMenuChoice(std::string PlayerName);


int main()
{
	std::string buffer;
	std::set <Character*> allFighters;
  srand(time(NULL));

	Player PlayerOne("PlayerOne");
	Player PlayerTwo("PlayerTwo");

	int numFighters = getIntFromUser("How many fighters should each player have? (1-100)", 5, 1, 100);
	getRoster(PlayerOne, numFighters, rand() % (size_t)&PlayerOne);
	getRoster(PlayerTwo, numFighters, rand() % (size_t)&PlayerTwo);

  PlayerOne.Print();
  PlayerTwo.Print();
	std::cout << std::endl << "Hit return to begin the tournament: ";
	getline(std::cin, buffer);

	Character* FighterOne = PlayerOne.NextFighter();
	Character* FighterTwo = PlayerTwo.NextFighter();
  while ( FighterOne && FighterTwo)
	{
		Combat( *FighterOne, *FighterTwo);
		(FighterOne->getHealth() <= 0) ? PlayerOne.RetireFighter(FighterOne) : FighterOne->scoreAgainst(FighterTwo);
		(FighterTwo->getHealth() <= 0) ? PlayerTwo.RetireFighter(FighterTwo) : FighterTwo->scoreAgainst(FighterOne);
		if ( ! (ASSIGN || TEST ) ) 
		{
			// For the assignment we just keep going
			PlayerOne.Print();
  		PlayerTwo.Print();
			std::cout << std::endl << "Hit return to continue the tournament: ";
			getline(std::cin, buffer);
		}
		allFighters.insert(FighterOne); allFighters.insert(FighterTwo);

		FighterOne = PlayerOne.NextFighter();
		FighterTwo = PlayerTwo.NextFighter();
	}

	if ( ! ASSIGN )
	{
 		PlayerOne.Print();
 		PlayerOne.PrintGraveyard();
 		PlayerTwo.Print();
 		PlayerTwo.PrintGraveyard();
	}
	Score(allFighters);
}

void Score (std::set<Character*> &allFighters)
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
					//Tie breakers: If two fighters have the same score, then
					// who has more health; if the same then,
					// ** all of these are no-ops if the fighters are the same type
					// who has lower strength; iff
					// who has lower armor; iff
					// who has lower attack; iff
					// who has lower defense
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
	for (iterL = rankedList.begin(); iterL != rankedList.end(); iterL++)
	{
		std::cout << (*iterL)->getName() << "	" << (*iterL)->getScore() << std::endl;
	}
	iterL = rankedList.begin();
	std::cout << "First place " << (*iterL)->getName() << "	" << (*iterL)->getScore() << std::endl;
	iterL++;
	std::cout << "Second place " << (*iterL)->getName() << "	" << (*iterL)->getScore() << std::endl;
	iterL++;
	std::cout << "Third place " << (*iterL)->getName() << "	" << (*iterL)->getScore() << std::endl;
}

void getRoster (Player & myPlayer, int numCharacters, int Seed)
{
	MenuChoice nextChoice;
	Character * myFighter; 
	std::string Name;
	std::string tmpString;

	int rSeed = Seed % 10;

	printUserMenu();
	for (int i = 0; i< numCharacters; i++)
	{
		nextChoice = unknown;
		do 
		{
			nextChoice = getUserMenuChoice( myPlayer.Name);
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
		myPlayer.LineUp.push_back(myFighter);
	}
}

/*****************************************************************
 * enum MenuChoice { Goblin, Barbarian, BlueChix, Reptile, Shadow, unknown };
 * char MenuOptions[] = {'G','B','C','R','S'};
 *
 *
 *************************************************************** */
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
	char menuOption;
	MenuChoice menuChoice;
	char inputBuffer[1024];

	std::cout << PlayerName << "  (G,B,C,R,S): ";
  menuOption = std::cin.get(); // get the first character
	std::cin.getline(inputBuffer,1024); // throw away anything else they typed

	for (int i=0; i<5; i++)
	{
		if (toupper(menuOption) == MenuOptions[i])
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
	if (pickAName > maxNames) return ""; //TODO Fix
	std::string Prompt;
	offset ++;

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

	Prompt = "Choose a name for your " + Classes[type];
	return( (getStringFromUser(Prompt, Names[type][pickAName]) + " the " + Classes[type]));
	//return Names[type][pickAName];
		
}

