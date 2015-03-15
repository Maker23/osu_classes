#include <iostream>
#include <string>

#include "main.h"
#include "Room.h"
#include "Container.h"
#include "Thing.h"
#include "BuildTheEnvironment.h"

/*****************************************************************
 *
 *
 *****************************************************************/
Room * BuildTheHouse(Room **allRooms)
{

  if (DEBUG_FUNCTION) std::cout << "===== begin BuildTheHouse" << std::endl;
	std::string blank = ""; // useful for multi-line strings

	allRooms[FrontLawn]	= new Room("the front lawn", 
																 "The house is to the North.");
	allRooms[FrontHall]	= new Room("the Front Hall", 
																 "There are doorways on every side.");
	allRooms[Library] 	= new Room("the Library", 
																 blank 
																 + "The shelves are full of books and knicknacks.\n"
																 + "A large book lies on the oaken desk.\nYou see another room beyond");
	allRooms[SunRm] 		= new Room("the Sunroom", 
																 blank
																 + "The sun is shining through the windows.\n"
																 + "This looks like a lovely place to have tea!");
	allRooms[DiningRm]	= new Room("the formal Dining room", "");
	allRooms[Kitchen]		= new Room("the Kitchen", 
																 blank
																 + "There are doors on every side.\n"
																 + "There is a cupboard, a refrigerator, and an oven.");
	allRooms[Pantry]		= new Room("the Pantry", 
																 "There are shelves full of food!");
	allRooms[Garden]		= new Room("the Garden", 
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
	
  Room * Start = allRooms[FrontHall];

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

  if (DEBUG_FUNCTION) std::cout << "===== end BuildTheHouse" << std::endl;
	return Start;
}

void FillTheRooms(Room **allRooms)
{
  if (DEBUG_FUNCTION) std::cout << "===== begin FillTheRooms" << std::endl;
	std::string Instructions = WriteTheInstructions();


	/* Front Hall  *******************************************/
	Thing* Umbrella = new Thing("Umbrella","Don't open it inside!");
	Thing* SilverVase = new Thing("Silver Vase","This would look nice with some flowers in it.");
	Thing* GameInstructions = new Thing("Notebook", Instructions);

	Container* UmbrellaStand = new Container("Umbrella stand", "");
	UmbrellaStand->Contents.push_back(Umbrella);

	Container* FrontHallTable = new Container("Gilded rococo table by the front door", "");
	FrontHallTable->Contents.push_back(GameInstructions);

	allRooms[FrontHall]->ContainersHere.push_back(UmbrellaStand);
	allRooms[FrontHall]->ContainersHere.push_back(FrontHallTable);
	allRooms[FrontHall]->ThingsHere.push_back(SilverVase);


	/* Kitchen    ********************************************/
	Thing * Flour = new Thing("Flour","");
	Thing * Cream = new Thing("Cream","");
	Thing * Sugar = new Thing("Sugar","");
	Thing * Jam = new Thing("Jam","");
	Thing * Jar = new Thing("Glass Jar", "");
	Thing *	MixingBowl = new Thing("Mixing bowl","I wonder if we have the ingredients for scones?");

	MixingBowl->UseFunc = MixTheScones;

	Container* Fridge = new Container("Refrigerator","");
	Fridge->Contents.push_back(Cream);

	Container* Cupboard = new Container("Kitchen Cupboard","");
	Cupboard->Contents.push_back(Flour);
	Cupboard->Contents.push_back(Sugar);
	Cupboard->Contents.push_back(Jam);

	Container* DishCupboard = new Container("Dish Cupboard", "");
	DishCupboard->Contents.push_back(Jar);

	Container* Oven = new Container("Oven","It's nice and hot and ready to bake something.");
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


	/* Garden     ********************************************/
	Thing* SweetPeas = new Thing("Sweet peas","They're in bloom. The colors are gorgeous!");
	Thing* Honey = new Thing("Honey","Fresh from the comb.");

	Container* Hive = new Container("Bee hive","The bees look friendly");
	Hive->Contents.push_back(Honey);
	Hive->Open = false;
	Hive->OpenFunc = GatherHoney;

	allRooms[Garden]->ContainersHere.push_back(Hive);
	allRooms[Garden]->ThingsHere.push_back(SweetPeas);
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

bool GatherHoney(Container *PlayerBag)
{
	Thing *WeHaveTheJar;

  if (DEBUG_FUNCTION) std::cout << "===== begin GatherHoney" << std::endl;
	if (PlayerBag == NULL )
		return false;

	WeHaveTheJar = PlayerBag->FindByName("Glass Jar");

	if (WeHaveTheJar) 
	{
		if (DEBUG_FIND) std::cout << "Found the Jar by name" << std::endl;
  	if (DEBUG_FUNCTION) std::cout << "===== end GathrHoney" << std::endl;
		return true;
	}
	std::cout << "	You need something to put the honey into. Maybe an empty jar?" << std::endl;
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

bool BakeTheScones(Room *currentRoom, Container *PlayerBag)
{
	Thing *WeHaveTheScones;
	Thing *OvenPtr;
  if (DEBUG_FUNCTION) std::cout << "===== begin BakeTheScones" << std::endl;

	if (PlayerBag == NULL )
		return false;

	WeHaveTheScones = PlayerBag->FindByName("Uncooked Scones");

	if (WeHaveTheScones) 
	{
		if (DEBUG_FIND) std::cout << "Found the scones by name" << std::endl;
  	if (DEBUG_FUNCTION) std::cout << "===== end BakeTheScones" << std::endl;
		std::cout << "You put the scones in the oven. They will take 20 minutes to bake." << std::endl;
		std::cout << "You set a timer." << std::endl;
		PlayerBag->Contents.remove(WeHaveTheScones);
		OvenPtr = currentRoom->FindByName("Oven");
		((Container *) OvenPtr)->Contents.push_back(WeHaveTheScones);
		return true;
	}
	if (DEBUG_FIND) std::cout << "Did not find the scones by name" << std::endl;
  if (DEBUG_FUNCTION) std::cout << "===== end BakeTheScones" << std::endl;
	return false;
}

bool MixTheScones(Room * currentRoom, Container *PlayerBag)
{
  if (DEBUG_FUNCTION) std::cout << "===== begin MixTheScones" << std::endl;

	Thing * FlourPtr = PlayerBag->FindByName("Flour");
	Thing * CreamPtr = PlayerBag->FindByName("Cream");
	Thing * SugarPtr = PlayerBag->FindByName("Sugar");

	Thing * Scones = new Thing("Uncooked Scones","Scone dough on a cookie sheet. Ready to Bake!");

	if (FlourPtr && CreamPtr && SugarPtr)
	{
		std::cout << "You put the Flour, Cream and Sugar in the mixing bowl" << std::endl;
		std::cout << "You mix....." << std::endl;
		sleep(1);
		std::cout << "	mixing is done! You spoon the dough onto a baking sheet." << std::endl;

		PlayerBag->Contents.remove(FlourPtr);
		PlayerBag->Contents.remove(SugarPtr);
		PlayerBag->Contents.remove(CreamPtr);
		PlayerBag->Contents.push_back(Scones);
		return true;
	}
  if (DEBUG_FUNCTION) std::cout << "===== end MixTheScones" << std::endl;
	std::cout << "	You don't have all the ingredients to mix scones." 
		<< std::endl << "	If only we had a recipe..." << std::endl;
	return false;
}

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
	"   Bake scones\n" +
	"   Pick flowers\n" +
	"   Fill teapot\n" +
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
	"   Bake for 40 minutes.\n";

	return blank;
}
