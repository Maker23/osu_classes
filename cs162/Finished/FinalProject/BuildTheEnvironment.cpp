#include <iostream>
#include <string>

#include "utilities.h"
#include "Room.h"
#include "Container.h"
#include "Thing.h"
#include "BuildTheEnvironment.h"

/*****************************************************************
 *
 *
 *****************************************************************/
AbstractRoom * BuildTheHouse(AbstractRoom **allRooms)
{

  if (DEBUG_FUNCTION) std::cout << "===== begin BuildTheHouse" << std::endl;
	std::string blank = ""; // useful for multi-line strings

	allRooms[FrontLawn]	= new OutsideRoom("the front lawn", 
																 "The house is to the North.");
	allRooms[FrontHall]	= new TimerRoom("the Front Hall", 
																 "There are doorways on every side.");
	allRooms[Library] 	= new Room("the Library", 
																 blank 
																 + "The shelves are full of books and knicknacks.\n"
																 + "A large book lies on the oaken desk.\n"
																 + "You see another room beyond");
	allRooms[SunRm] 		= new Room("the Sunroom", 
																 blank
																 + "The sun is shining through the windows.\n"
																 + "This looks like a lovely place to have tea!");
	allRooms[DiningRm]	= new Room("the formal Dining room", "");
	allRooms[Kitchen]		= new TimerRoom("the Kitchen", 
																 blank
																 + "There are doors on every side.\n"
																 + "There is a cupboard, a refrigerator, and an oven.");
	allRooms[Pantry]		= new Room("the Pantry", 
																 "There are shelves full of food!");
	allRooms[Garden]		= new OutsideRoom("the Garden", 
																 blank 
																 + "Beautiful flowers surround you.\n"
																 + "You hear a constant gentle buzzing.");
	allRooms[StairUp]		= new Room("the Staircase", 
																 "It goes up to the upper storey.");
	allRooms[StairDown]	= new Room("the Staircase", 
																 "It goes down to the lower storey.");
	allRooms[Hallway]		= new Room("a hallway", "");
	allRooms[Bedrm]			= new Room("the bedroom", "");
	allRooms[DressingRm]= new Room("the Dressing Room", "");

	allRooms[FrontLawn]->East		= allRooms[Garden];
	allRooms[FrontLawn]->North	= allRooms[FrontHall];

	allRooms[FrontHall]->South	= allRooms[FrontLawn];
	allRooms[FrontHall]->East		= allRooms[SunRm];
	allRooms[FrontHall]->North	= allRooms[StairUp];
	allRooms[FrontHall]->West		= allRooms[Library];

	allRooms[Library]->East			= allRooms[FrontHall];
	allRooms[Library]->North		= allRooms[DiningRm];

	allRooms[SunRm]->North			= allRooms[Kitchen];
	allRooms[SunRm]->West				= allRooms[FrontHall];

	allRooms[DiningRm]->South		= allRooms[Library];

	allRooms[Kitchen]->South		= allRooms[SunRm];
	allRooms[Kitchen]->East			= allRooms[Garden];
	allRooms[Kitchen]->North		= allRooms[Pantry];
	allRooms[Kitchen]->West			= allRooms[StairUp];

	allRooms[Pantry]->South			= allRooms[Kitchen];

	allRooms[Garden]->South			= allRooms[FrontLawn];
	allRooms[Garden]->West			= allRooms[Kitchen];

	allRooms[StairUp]->South		= allRooms[FrontHall];
	allRooms[StairUp]->North		= allRooms[Hallway];

	allRooms[StairDown]->South	= allRooms[FrontHall];
	allRooms[StairDown]->North	= allRooms[Hallway];

	allRooms[Hallway]->South		= allRooms[StairDown];
	allRooms[Hallway]->East			= allRooms[DressingRm];
	allRooms[Hallway]->North		= allRooms[Bedrm];

	allRooms[Bedrm]->South			= allRooms[Hallway];
	allRooms[Bedrm]->East				= allRooms[DressingRm];

	allRooms[DressingRm]->South	= allRooms[Hallway];
	allRooms[DressingRm]->West	= allRooms[Bedrm];

  AbstractRoom * Start = allRooms[FrontHall];

  if (DEBUG_FUNCTION) std::cout << "===== end BuildTheHouse" << std::endl;
	return Start;
}

void FillTheRooms(AbstractRoom **allRooms)
{
  if (DEBUG_FUNCTION) std::cout << "===== begin FillTheRooms" << std::endl;
	std::string Instructions = WriteTheInstructions();


	/* Front Hall  *******************************************/
	Thing* Umbrella = new Thing("Umbrella","Don't open it inside!");
	Thing* GameInstructions = new Thing("Notebook", Instructions);

	Container* SilverVase = new Container("Silver Vase",
		"This would look nice with some flowers in it.");
	SilverVase->UseFunc = FillTheVase;
	SilverVase->Weight = 2;

	Container* UmbrellaStand = new Container("Umbrella stand", "");
	UmbrellaStand->Contents.push_back(Umbrella);

	Container* FrontHallTable = new Container("Gilded rococo table by the front door", "");
	FrontHallTable->Contents.push_back(GameInstructions);

	allRooms[FrontHall]->ContainersHere.push_back(UmbrellaStand);
	allRooms[FrontHall]->ContainersHere.push_back(FrontHallTable);
	allRooms[FrontHall]->ContainersHere.push_back(SilverVase);

	//allRooms[FrontHall]->setTimerLimit(GameLength-1); // TODO
	allRooms[FrontHall]->setTimerLimit(1); // TODO
	allRooms[FrontHall]->TimerFunc = RingTheDoorbell;

	/* Kitchen    ********************************************/
	Thing * Flour = new Thing("Flour","");
	Thing * Cream = new Thing("Cream","");
	Thing * Sugar = new Thing("Sugar","");
	Thing * Jam = new Thing("Jam","");
	Thing *	MixingBowl = new Thing("Mixing bowl",
		"I wonder if we have the ingredients for scones?");

	MixingBowl->UseFunc = MixTheScones;

	Container * Jar = new Container("Glass Jar", "");
	Jar->UseFunc = GatherHoney;
	Jar->Weight = 1;

	Container* Fridge = new Container("Refrigerator","");
	Fridge->Contents.push_back(Cream);

	Container* Cupboard = new Container("Kitchen Cupboard","");
	Cupboard->Contents.push_back(Flour);
	Cupboard->Contents.push_back(Sugar);
	Cupboard->Contents.push_back(Jam);

	Container* DishCupboard = new Container("Dish Cupboard", "");
	DishCupboard->Contents.push_back(Jar);

	Container* Oven = new Container("Oven",
		"It's nice and hot and ready to bake something.");
	Oven->UseFunc = BakeTheScones;

	allRooms[Kitchen]->ContainersHere.push_back(Cupboard);
	allRooms[Kitchen]->ContainersHere.push_back(DishCupboard);
	allRooms[Kitchen]->ContainersHere.push_back(Fridge);
	allRooms[Kitchen]->ContainersHere.push_back(Oven);
	allRooms[Kitchen]->ThingsHere.push_back(MixingBowl);


	/* Dining Room  ******************************************/
	Thing * Tea = new Thing("Tea canister", "Mmmm... smells like yunnan red!");
	Thing * TeaPot = new Thing("Silver teapot", "");
	TeaPot->Weight = 2; 
	TeaPot->UseFunc = BrewTheTea;

	Container * TeaChest = new Container("Tea chest","It has a silver escutcheon with a skeleton keyhole.");
	TeaChest->Open = false; // Locked!
	TeaChest->OpenFunc = UnlockTeaChest;
	TeaChest->Weight = 4;   // Light enough to carry
	Container * Sideboard = new Container("Sideboard","");
	Container * DiningTable = new Container("Dining Room table","");

	TeaChest->Contents.push_back(Tea);
	Sideboard->Contents.push_back(TeaChest);
	DiningTable->Contents.push_back(TeaPot);

	allRooms[DiningRm]->ContainersHere.push_back(Sideboard);
	allRooms[DiningRm]->ContainersHere.push_back(DiningTable);


	/* Library    ********************************************/
	std::string Recipe = GetTheRecipeForScones();
	Thing * CookBook = new Thing("A book titled 'Proper English tea'", Recipe );
	Thing * Watch = new Thing("Pocket Watch", "" );

	Container * LibTable = new Container("Library Desk","");
	LibTable->Contents.push_back(CookBook);
	LibTable->Contents.push_back(Watch);

	allRooms[Library]->ContainersHere.push_back(LibTable);


	/* Sun Room   ********************************************/
	Thing *	SilverKey = new Thing("Silver key", "I wonder what this opens?");
	Container * SunRmTable = new Container ("Sun Room table", 
		"There are four place settings laid out. What lovely tea cups!");

 	SunRmTable->Contents.push_back(SilverKey);
	allRooms[SunRm]->ContainersHere.push_back(SunRmTable);


	/* Front Lawn ********************************************/
	Thing* Roses = new Thing("Roses","Deep velvety red roses growing by the armful.");
	allRooms[FrontLawn]->ThingsHere.push_back(Roses);
	allRooms[FrontLawn]->setWeather("warm and sunny, with a bit of a breeze");


	/* Garden     ********************************************/
	Thing* SweetPeas = new Thing("Sweet peas","They're in bloom. The colors are gorgeous!");
	Thing* Honey = new Thing("Honey","Fresh from the comb.");
	Honey->UseFunc = GatherHoney;

	Container* Hive = new Container("Bee hive","The bees look friendly");
	Hive->Contents.push_back(Honey);
	Hive->UseFunc = GatherHoney;

	allRooms[Garden]->ContainersHere.push_back(Hive);
	allRooms[Garden]->ThingsHere.push_back(SweetPeas);
	allRooms[Garden]->setWeather("warm and sunny");
  if (DEBUG_FUNCTION) std::cout << "===== end FillTheRooms" << std::endl;
}

bool UnlockTeaChest(Container *PlayerBag)
{
	Thing *WeHaveTheKey;
	int counter = 0;

  if (DEBUG_FUNCTION) std::cout << "===== begin UnlockTeaChest" << std::endl;
	if (PlayerBag == NULL )
		return false;

	WeHaveTheKey = PlayerBag->FindByName("Silver key");

	if (WeHaveTheKey) 
	{
		if (DEBUG_FIND) std::cout << "Found the Key by name" << std::endl;
  	if (DEBUG_FUNCTION) std::cout << "===== end UnlockTeaChest" << std::endl;
		return true;
	}
	std::cout << "	Hm, looks like you're missing the key to the Tea Chest" << std::endl;
  if (DEBUG_FUNCTION) std::cout << "===== end UnlockTeaChest" << std::endl;
	return false;
}

bool GatherHoney(AbstractRoom * currentRoom, Container *PlayerBag)
{
	Thing *JarPtr = NULL;
	Thing *HivePtr = NULL;
	Thing *HoneyPtr = NULL;

  if (DEBUG_FUNCTION) std::cout << "===== begin GatherHoney" << std::endl;
	if (PlayerBag == NULL )
		return false;

	JarPtr = PlayerBag->FindByName("Glass Jar");
	HivePtr = currentRoom->FindByName("Bee hive");

	if (HivePtr)
		HoneyPtr = ((Container*) HivePtr)->FindByName("Honey");

	if (JarPtr && HivePtr && HoneyPtr) 
	{
		if (DEBUG_FIND) std::cout << "Found the Jar by name" << std::endl;
		((Container*) HivePtr)->Contents.remove(HoneyPtr);
		((Container*) JarPtr)->Contents.push_back(HoneyPtr);
		((Holdall*)PlayerBag)->GameTask[HoneyIsGathered] = true;
  	if (DEBUG_FUNCTION) std::cout << "===== end GathrHoney" << std::endl;
		return true;
	}
	else if ( HoneyPtr && !JarPtr)
	{
		std::cout << "	You need something to put the honey into. Maybe an empty jar?" << std::endl;
		return true;
	}
 	if (DEBUG_FUNCTION) std::cout << "===== end GatherHoney" << std::endl;
	return false;
}

bool CheckTheTime(Container *PlayerBag)
{
	Thing *WeHaveTheWatch;

  if (DEBUG_FUNCTION) std::cout << "===== begin CheckTheTime" << std::endl;

	if (PlayerBag == NULL )
		return false;

	WeHaveTheWatch = PlayerBag->FindByName("Pocket Watch");

	if (WeHaveTheWatch) 
	{
		if (DEBUG_FIND) std::cout << "Found the watch by name" << std::endl;
  	if (DEBUG_FUNCTION) std::cout << "===== end CheckTheTime" << std::endl;
		return true;
	}
	if (DEBUG_FIND) std::cout << "Did not find the watch by name" << std::endl;
  if (DEBUG_FUNCTION) std::cout << "===== end CheckTheTime" << std::endl;
	return false;
}

bool BakeTheScones(AbstractRoom *currentRoom, Container *PlayerBag)
{
	int timerMax;
	int timerCurrent;
	Thing *PlayerHasTheScones;
	Thing *SconesInTheOven;
	Thing *OvenPtr;

  if (DEBUG_FUNCTION) std::cout << "===== begin BakeTheScones" << std::endl;

	if (PlayerBag == NULL )
		return false;

	timerMax = currentRoom->getTimerLimit();
	timerCurrent = currentRoom->getTimer();
	OvenPtr = currentRoom->FindByName("Oven");
	PlayerHasTheScones = PlayerBag->FindByName("Uncooked Scones");
	//std::cout << "DEBUGGING timer currenta= " << timerCurrent << std::endl;

	if (PlayerHasTheScones) 
	{
		if (DEBUG_FIND) std::cout << "Found the scones by name" << std::endl;
  	if (DEBUG_FUNCTION) std::cout << "===== end BakeTheScones" << std::endl;
		std::cout << "You put the scones in the oven. They will take 20 minutes to bake." << std::endl;
		currentRoom->setTimerLimit(4);
		timerMax = currentRoom->getTimerLimit();
		if (DEBUG_USE) std::cout << "Setting a timer, timerMax = " << timerMax << std::endl;
		if ( timerMax )
		{
			std::cout << "You set a timer." << std::endl;
		}
		PlayerBag->Contents.remove(PlayerHasTheScones);
		PlayerHasTheScones->Name = "Cooking Scones";
		PlayerHasTheScones->Story = "On a baking sheet";
		std::string blank = "";
		((Container *) OvenPtr)->Contents.push_back(PlayerHasTheScones);
		((Container *) OvenPtr)->Story = blank + "Scones are baking. ";
		return true;
	}

  // Look for scones in the oven 
	SconesInTheOven = ((Container*) OvenPtr)->FindByName("Cooking Scones");
	if (! SconesInTheOven) SconesInTheOven = ((Container * )OvenPtr)->FindByName("Scones");
	if (! SconesInTheOven) SconesInTheOven = ((Container * )OvenPtr)->FindByName("Burnt Scones");

	if (! SconesInTheOven )
	{
		// No scones in the oven? If the timer is on, turn it off
		if (currentRoom ->getTimer())
		{
			std::cout << "Turning off the Oven timer." << std::endl;
			currentRoom->setTimer(0);
			return true;
		}
		// Else do nothing.
		return false;
	}
	// Scones are in the oven - see below
	else if ( timerMax && (timerCurrent < timerMax)) 
	{
		std::cout << "The Scones aren't finished baking" << std::endl
			<< "You might want to leave them in the oven" << std::endl;
		return false;
	}
	else if ( timerMax && (timerCurrent > (timerMax +2))) 
	{
		std::string blank = "";
		((Container *) OvenPtr)->Story = blank + "Scones are burning. ";
		std::cout << "The Scones are burning!" << std::endl
			<< "Take them out of the oven!" << std::endl;
		((Holdall*)PlayerBag)->GameTask[SconesAreBaked] = false;
		SconesInTheOven->Name = "Burnt Scones";
  	if (DEBUG_FUNCTION) std::cout << "===== end BakeTheScones" << std::endl;
		return false;
	}
	else if ( timerMax )
	{
		((Container *) OvenPtr)->Story = "";
		SconesInTheOven->Name = "Scones";
		std::cout << "The Scones are done!" << std::endl
			<< "Take them out of the oven!" << std::endl;
  	if (DEBUG_FUNCTION) std::cout << "===== end BakeTheScones" << std::endl;
		((Holdall *)PlayerBag)->GameTask[SconesAreBaked] = true;
		return false;
	}
	if (DEBUG_FIND) std::cout << "Did not find the scones by name" << std::endl;
  if (DEBUG_FUNCTION) std::cout << "===== end BakeTheScones" << std::endl;
	return false;
}

bool BrewTheTea(AbstractRoom * currentRoom, Container *PlayerBag)
{
  if (DEBUG_FUNCTION) std::cout << "===== begin BrewTheTea" << std::endl;
	Thing * TeaPtr = PlayerBag->FindByName("Tea canister");
	Thing * TeaPotPtr = PlayerBag->FindByName("Silver teapot");

	if ( ! TeaPtr)
	{
		std::cout << "You need tea to use a teapot." << std::endl;
		return false;
	}
	else if ((currentRoom->getName()).compare("the Kitchen") != 0 )
	{
		std::cout << "Where were you planning to find boiling water?" << std::endl
			<< "You need to be in the Kitchen to brew tea." << std::endl;
		return false;
	}
	else 
	{
		std::cout << "You have made some delicious tea. Mmmm... caffeine...."<< std::endl;
		((Holdall*)PlayerBag)->GameTask[TeaIsBrewed] = true;

		PlayerBag->Contents.remove(TeaPtr);
		PlayerBag->Contents.remove(TeaPotPtr);
		currentRoom->ThingsHere.push_back(TeaPotPtr);
		currentRoom->ThingsHere.push_back(TeaPtr);

		return true;
	}
}
	
bool FillTheVase(AbstractRoom * currentRoom, Container *PlayerBag)
{
  if (DEBUG_FUNCTION) std::cout << "===== begin FillTheVase" << std::endl;

	if ( ((Holdall*)PlayerBag)->GameTask[FlowersArePicked] == true)
	{
	 	// You can only fill the vase once :)
		return false;
	}

	Thing * RosePtr = PlayerBag->FindByName("Roses");
	Thing * SweetPeaPtr = PlayerBag->FindByName("Sweet peas");
	Thing * VasePtr = currentRoom->FindByName("Silver Vase");

	if (RosePtr) 
	{
		std::cout << "You fill the vase with roses. This will look stunning" 
			<< std::endl << "on the tea table" << std::endl;
		((Holdall*)PlayerBag)->GameTask[FlowersArePicked] = true;
		PlayerBag->Contents.remove(RosePtr);
		((Container*)VasePtr)->Contents.push_back(RosePtr);
		return true;
	}
	else if (SweetPeaPtr)
	{
		std::cout << "You fill the vase with sweet peas. They will smell delicious" 
			<< std::endl << "on the tea table" << std::endl;
		((Holdall*)PlayerBag)->GameTask[FlowersArePicked] = true;
		PlayerBag->Contents.remove(SweetPeaPtr);
		((Container*)VasePtr)->Contents.push_back(SweetPeaPtr);
		return true;
	}
	else
	{
		std::cout << "The vase is empty. You could fill it with flowers." << std::endl;
		return false;
	}

  if (DEBUG_FUNCTION) std::cout << "===== end FillTheVase" << std::endl;
}
bool MixTheScones(AbstractRoom * currentRoom, Container *PlayerBag)
{
  if (DEBUG_FUNCTION) std::cout << "===== begin MixTheScones" << std::endl;

	Thing * FlourPtr = PlayerBag->FindByName("Flour");
	Thing * CreamPtr = PlayerBag->FindByName("Cream");
	Thing * SugarPtr = PlayerBag->FindByName("Sugar");


	if (FlourPtr && CreamPtr && SugarPtr)
	{
		std::cout << "You put the Flour, Cream and Sugar in the mixing bowl" << std::endl;
		std::cout << "You mix....." << std::endl;
		sleep(1);
		std::cout << "	mixing is done! You spoon the dough onto a baking sheet." << std::endl;
		Thing * Scones = new Thing("Uncooked Scones","Scone dough on a cookie sheet. Ready to Bake!");
		Scones->UseFunc = BakeTheScones;
		PlayerBag->Contents.push_back(Scones);

		// For simplicity we delete these from the game
		PlayerBag->Contents.remove(FlourPtr);
		PlayerBag->Contents.remove(SugarPtr);
		PlayerBag->Contents.remove(CreamPtr);
		delete (FlourPtr);
		delete (SugarPtr);
		delete (CreamPtr);

		return true;
	}
  if (DEBUG_FUNCTION) std::cout << "===== end MixTheScones" << std::endl;
	std::cout << "	You don't have all the ingredients to mix scones." 
		<< std::endl << "	If only we had a recipe..." << std::endl;
	return true;
}

void RingTheDoorbell(AbstractRoom * currentRoom, int currentTime)
{
	TimerRoom *DoorbellRoom = (TimerRoom *)currentRoom;
	int timerMax = currentRoom->getTimerLimit();

	if (currentTime < timerMax)
		return;

	std::cout << "The Front Doorbell rings. Your friends are here for tea!" << std::endl;
	// Just ring once
	currentRoom->setTimerLimit(0);
	
}

// I ended up not using this function
std::list<Thing*> EquipThePlayer()
{
	std::list<Thing*> myThings;

	Container * Bag = new Container("Linen bag","");
	myThings.push_back(Bag);


	return (myThings);
}

std::string WriteTheInstructions()
{

	std::string blank = ""; 

	blank = blank +
	"It says:\n" +
	"\n" +
	"Tea on Wednesday -- 4 PM sharp!\n" +
	"\n" +
	"To Do:\n" +
	"X  Send invitations\n" +
	"   Brew tea\n" +
	"   Bake scones\n" +
	"   Pick flowers, fill vase\n" +
	"   Choose a hat!\n";

	return blank;
}

std::string GetTheRecipeForScones()
{

	std::string blank = ""; 

	blank = blank +
	"It looks like a recipe. It says:\n" +
	"\n" +
	"Scones for afternoon tea" +
	"\n" +
	"   2 c. Flour\n" +
	"   1/2 c. Cream\n" +
	"   1/2 c. Sugar\n" +
	"\n" +
	"   Put all ingredients into mixing bowl; stir.\n" +
	"   Put Scones into pre-heated oven\n" +
	"   Bake for 20 minutes.\n";

	return blank;
}
