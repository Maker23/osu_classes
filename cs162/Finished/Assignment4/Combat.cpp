#include <iostream>
#include <cstdlib>
#include <typeinfo>

#include "Flags.h"
#include "Dice.h"
#include "Character.h"

#ifndef TEST
#define TEST false
#endif

int Combat (Character & FighterOne, Character & FighterTwo);
void runStatisticsTests(Character &FighterOne, Character & FighterTwo);
void runTests();


/* *********************************************************************
 * Combat()
 *
 * The core function to decide combat between two characters.
 * Please see the PDF doc for information about design decisions here.
 *
 * ********************************************************************/

int Combat (Character & FighterOne, Character & FighterTwo)
{
	int flip = rand() % 2; // Toss the coin to see who attacks first
	int defend, attack, damage;
	int numRounds = 0;
	Character *Attacker, *Defender;
	Character *FirstAttacker = NULL;

  if (TEST) {
		// If we're testing reset all players to full strength
		FighterOne.Reset();
		FighterTwo.Reset();
	}
	else {
		// Otherwise recover some health if it's low
		FighterOne.Recover();
		FighterTwo.Recover();
	}

	if (!STATISTICS) std::cout << "Combat: " << FighterOne.getName() << " vs " << FighterTwo.getName() << std::endl;
	FighterOne.Bouts ++;
	FighterTwo.Bouts ++;
	do
	{
		/* Alternate who attacks vs. who defends. Other than that the
		 * code is the same for all combat rounds.  */

		numRounds ++;
  	if (flip == 0 ) 
		{
			Attacker = &FighterOne;
			Defender = &FighterTwo;
		}
		else
		{
			Attacker = &FighterTwo;
			Defender = &FighterOne;
		}
		if (FirstAttacker == NULL)
			FirstAttacker = Attacker; // Save this, we'll want it later

    /* Now carry out the attack....  */
		if (!TEST && VVERBOSE ) std::cout << Attacker->getName() << " attacks " << Defender->getName() << std::endl;
		if ( Defender -> AchillesFactor && Attacker->getType() != GOBLIN) {
			attack = Attacker->attack() * Defender->AchillesFactor;
			
			//if (TEST && (Defender->AchillesFactor != 1.0)) 
			//	std::cout << Attacker->getName() 
			//		<< " is hampered by the Achilles attack"<< std::endl;
		}
		else 
		{
			attack = Attacker->attack();
		}
		/* ... and the defense, and calculate the resulting damage */
		defend = Defender->defend();
		damage = attack - (defend + Defender->getArmor());

		if (DEBUG) std::cout << "Damage = " <<  attack << " - " 
			<< (defend + Defender->getArmor()) << std::endl;

		if (damage > 0 ) {
			Defender->setHealth(Defender->getHealth() - damage);
			if (! TEST && VVERBOSE) std::cout << "	" << Defender->getName() << " takes " 
				<< damage << " damage!" << std::endl;
			if (Defender->getHealth() <= 0 )
			{
				// Defender has died in this round
				if (!TEST && VVERBOSE) std::cout << Defender->getName() 
					<< " is hors de combat :( " << std::endl;
			}
		}
		else 
		{
			if (!TEST && VVERBOSE)std::cout << "No damage was done!" << std::endl;
		}
		flip = abs(flip - 1); // Flip alternates between 0 and 1
	}
	while ( FighterOne.getHealth() > 0 && FighterTwo.getHealth() > 0 );

	// Extra points for the winner if they didn't attack first
	// Extra points for the loser if the fight goes past N rounds
	Attacker->Wins++;
	Defender->Losses++;
	if (Attacker != FirstAttacker)
	{
		if (!TEST && VVERBOSE) std::cout <<  "	" <<"Awarding a bonus to winner " 
			<< Attacker->getName() << " for not attacking first" << std::endl;
		Attacker->setScore(Attacker->getScore() + 1); // Bonus
	}
	if (numRounds > 11 )
	{
		if (!TEST && VVERBOSE) std::cout << "	" << "Awarding a bonus to loser " 
			<< Defender->getName() << " for lasting longer than 11 rounds" << std::endl;
		Defender->setScore(Defender->getScore() + 1); // Bonus
	}


  // Return the results; this is mostly useful for accumulating results during testing
  if (FighterOne.getHealth() <= 0 )
	{ 
		return (2);// FighterTwo won
	}
	else if (FighterTwo.getHealth() <= 0 )
	{
		return (1); // FighterOne won
	}
	else
	{
		return (-1); // This should never happen
	}
}

/* *********************************************************************
 *
 *  runStatisticsTests
 *
 *  Take two Character references and run a number of Combat() rounds
 *  between them.  Print the finally win/loss tally
 *
 * ********************************************************************/
void runStatisticsTests (Character & FighterOne, Character & FighterTwo)
{
	int Iterations = 100000;
	int FighterOneCount = 0;
	int FighterTwoCount = 0;
	int ReturnFromCombat;
	std::string TypeNames[] = {"Goblin", "Barbarian", "Reptile", "BlueChix", "Shadow"};

	for (int i=0; i< Iterations; i++)
	{
		ReturnFromCombat = Combat(FighterOne, FighterTwo);
		if (ReturnFromCombat == 1) 
			FighterOneCount ++;
		else if (ReturnFromCombat ==2)
			FighterTwoCount ++;
	}
	std::cout << TypeNames[FighterOne.getType()] << " vs. " << TypeNames[FighterTwo.getType()] 
		<< " = " << FighterOneCount << " vs. " << FighterTwoCount << std::endl;

  std::cout.flush();
}

/* *********************************************************************
 * runTests()
 *
 * This is a test driver function. It creates two of each derived class,
 * and runs all the possible pairings through the runStatisticsTests()
 * function to see how often one character type defeats another.
 *
 * ********************************************************************/
void runTests() 
{
  // Each instance gets a name, but during testing we don't
	// see the names printed out.
	Character * TestGoblin;
	TestGoblin = new Goblin("WTF");
	Goblin GoblinOne ("Annoying Goblin");
	Goblin GoblinTwo ("Irritating Goblin Imp");
	Barbarian BarbOne ("Red Sonja");
	Barbarian BarbTwo ("Xeetha");
	ReptilePeople ReptileOne("Emerald Anole");
	ReptilePeople ReptileTwo("Golden Salamander");
	BlueChix BlueChixOne ("Rocking Blue Huntress");
	BlueChix BlueChixTwo ("Cerulean Stalker");
	Shadow ShadowOne ("The Shadow");
	Shadow ShadowTwo ("The Other Shadow");

	runStatisticsTests (GoblinOne, GoblinTwo);
	runStatisticsTests (GoblinOne, BarbTwo);
	runStatisticsTests (GoblinOne, ReptileOne);
	runStatisticsTests (GoblinTwo, BlueChixOne);
	runStatisticsTests (GoblinTwo, ShadowOne);
	
	runStatisticsTests (BarbOne, BarbTwo);
	runStatisticsTests (BarbOne, ReptileTwo);
	runStatisticsTests (BarbTwo, BlueChixOne);
	runStatisticsTests (BarbOne, ShadowOne);

	runStatisticsTests (ReptileOne, ReptileTwo);
	runStatisticsTests (ReptileOne, BlueChixTwo);
	runStatisticsTests (ReptileOne, ShadowTwo);
	
	runStatisticsTests (BlueChixOne, BlueChixTwo);
	runStatisticsTests (BlueChixOne, ShadowTwo);

	runStatisticsTests (ShadowOne, ShadowTwo);


	/*
	// Very basic test cases; initially used for early debugging, 
	// not really needed now.
	//
	Dice myDice(2,6);
	std::cout << "Rolling two dice: " << myDice.roll() << std::endl;

	std::cout << myBarb.getName() << " attack roll: " << myBarb.attack() << std::endl;
	std::cout << myBarb.getName() << " defend roll: " << myBarb.defend() << std::endl;

	std::cout << myShadow.getName() << " defend roll: " << myShadow.defend() << std::endl;
	std::cout << myShadow.getName() << " defend roll: " << myShadow.defend() << std::endl;
	std::cout << myShadow.getName() << " defend roll: " << myShadow.defend() << std::endl;
	*/


}
