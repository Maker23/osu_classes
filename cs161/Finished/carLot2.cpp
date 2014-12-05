/* vim: ts=2
 *
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/11/24
 *  Last Modification date: 2014/11/30
 *  Filename: carLot2.cp
 *
 *  Overview:
 *	DATE:
 *	[x]	Date should be a class, 
 *	[x] Date should have constructor that takes parameters with which to
 *			initialize its data members (day, month, year).  
 *	[x]	The constructor should also verify that the parameters specify a valid
 *			date (as discussed last week).
 *
 *	CAR:
 *	[x] Car should be a class. It should have two Constructors: 
 *	[x]	one that takes parameters with which to initialize all its data members
 *			(make, model, year, datePurchased, purchasePrice, isSold, dateSold,
 *			salePrice) 
 *	[x]	and one that takes parameters with which to initialize all of those
 *			except the last two. 
 *	[x]	Car should have a function called getProfit that returns the profit on
 *			that car if it has been sold, or the special value NAN (not a number,
 *			declared in math.h) if it hasn't been sold yet.
 *	CARLOT:
 *	[x]	You will write a CarLot class that contains a vector of Car as a data
 *			member. 
 *	[x]	CarLot should have a function called addCar that takes a Car parameter
 *			and adds it to the vector. 
 *	[x]	CarLot should have a function called listCurrentInv that lists the data
 *			for all Cars that have not yet been sold, and then prints out the count of
 *			how many cars that is. 
 *	[x]	CarLot should have a function called getMonthProfit that takes as
 *			parameters a month and year and returns the total profit for sales in that
 *			month.
 */

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>	// to_string()
#include <stdexcept>// throw exceptions
#include <string>		// to_string()
#include <cmath>  	// NAN
#include <cstdlib>
#include <vector>

#define DEBUG false

std::string monthString[] = { 
	"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", 
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

/************************************************************************
 *   ____        _       
 *  |  _ \  __ _| |_ ___ 
 *  | | | |/ _` | __/ _ \
 *  | |_| | (_| | ||  __/
 *  |____/ \__,_|\__\___|
 *                     
 ************************************************************************/
class Date {
 private:
	int Day;
	int Month;
	int Year;


 public:
	Date() {if (DEBUG) std::cout << "Empty date constructor called" << std::endl;}
	Date(int, int, int);
	std::string str();
	void print();
	int getDay() { return Day; }
	int getMonth() { return Month; }
	int getYear() { return Year; }
};

Date::Date(int mm, int dd, int yyyy)	
{
	Month = mm;
	Day = dd;
	Year = yyyy;
	int 	monthDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if (DEBUG) std::cout << "Date constructor with args " << Month << "/" << Day << "/" << Year << std::endl;
	if ( Year < 1900 || Year > 2015 )
		throw std::invalid_argument("ERROR: Year must be between 1900 and 2015");
	else if ( Month < 1 || Month > 12 )
		throw std::invalid_argument("ERROR: Month must be 1-12");
  else if ( Day < 1 || Day >  monthDays[Month] )
		throw std::invalid_argument("ERROR: Wrong number of days in month");
  // The assignment asks us not to handle these exceptions so the program
	// will abort and dump core if any of these are thrown
}

/* This function takes the date as three integers (month, day year)
 * and returns a nicely formatted string suitable for printing */
std::string Date::str()
{
	std::string tmpStr = "";
	std::ostringstream m,d,y;

	m << Month;
	tmpStr += m.str();
	tmpStr += "/";
	d << Day;
	tmpStr += d.str();
	tmpStr += "/";
	y << Year;
	tmpStr += y.str();

	return (tmpStr);
}
void Date::print()
{
	// Print the date. This is only used for debugging
	std::cout << "Date::print " << Month << "/" << Day << "/" << Year << std::endl;
}

/************************************************************************
 *    ____           
 *	 / ___|__ _ _ __ 
 *	| |   / _` | '__|
 *	| |__| (_| | |   
 *	 \____\__,_|_|   
 *
 ************************************************************************/
class Car {
	std::string make;
	std::string model;
	int			year;
	Date		datePurchased;
	double	purchasePrice;
	bool		isSold;
	Date		dateSold;
	double	salePrice;

 public:
 	Car() {}
 	Car(std::string make, std::string model, int year, Date datePurchased,
  			double purchasePrice, bool isSold, Date dateSold, double salePrice);
 	Car(std::string make, std::string model, int year, Date datePurchased,
			double purchasePrice, bool isSold);
	double getProfit();

	void 	print();
	void 	printHeader();
	bool 	IsSold(){return isSold;}
	int 	getSaleMonth() {return dateSold.getMonth();}
	int 	getSaleYear(){return dateSold.getYear();}

};
/* Constructor for a car that has been sold and has a sold date and price */
Car::Car(std::string _make, std::string _model, int _year, Date _datePurchased,
				double _purchasePrice, bool _isSold, Date _dateSold, double _salePrice)
{
	make = _make;
	model = _model;
	year = _year;
	datePurchased = _datePurchased;
	purchasePrice = _purchasePrice;
	isSold = _isSold;
	dateSold = _dateSold;
	salePrice = _salePrice;
}

/* Constructor for a car that has not been sold */
Car::Car(std::string _make, std::string _model, int _year, Date _datePurchased,
				double _purchasePrice, bool _isSold)
{
	make = _make;
	model = _model;
	year = _year;
	datePurchased = _datePurchased;
	purchasePrice = _purchasePrice;
	isSold = _isSold;
	if (DEBUG) 
	{
		std::cout << "Car onstructor 170 " << std::endl;
		std::cout << "long form: " << datePurchased.getDay() << "/" 
			<< datePurchased.getMonth() << "/" << datePurchased.getYear() << std::endl;
		std::cout << "short form: ";
		datePurchased.print();
	}
}

double Car::getProfit()
{
	if (isSold)
		return ( salePrice - purchasePrice);
	else
		return (NAN);
}

/*
 * Car::printHeader
 * 
 * Print the column headers for car listings
 * Arguments: boolean, do or do not print additional columns for cars sold
 */
void Car::printHeader()
{
	std::cout << std::endl <<
	"                             Purchase     Purchase";
	if (isSold) 
		std::cout << "        Sales       Sales";

	std::cout << std::endl <<
		"   Year  Make    Model          Price         Date";
	if (isSold) 
		std::cout << "         Date       Price";

	std::cout << std::endl;
}

void Car::print()
{
  // This is just a long, somewhat tedious, series of formatted cout commands

  if (DEBUG) std::cout << "Entering Car::print" << std::endl;

  std::cout << 
		std::fixed <<
		std::setprecision(2) << 
		std::left <<
		"   " << std::setw(6) <<
		year << std::setw(8) <<
		make << std::setw(8) <<
		model << std::setw(4) <<
		std::right <<
		"$" << 
		std::setw(8) << std::right<<
		purchasePrice <<
		std::setw(13) << std::right <<
		datePurchased.str();
	if (isSold)
	{
		std::cout <<
			std::setprecision(2) <<
			std::setw(13) << std::right <<
			dateSold.str() << 
			std::setw(4) << std::right << 
			"$" << 
			std::setw(8) << std::right << 
			salePrice <<
			std::left;
	}
  std::cout	<< std::endl;
}

/************************************************************************
 *    ____           _          _   
 *	 / ___|__ _ _ __| |    ___ | |_ 
 *	| |   / _` | '__| |   / _ \| __|
 *	| |__| (_| | |  | |__| (_) | |_ 
 *	 \____\__,_|_|  |_____\___/ \__|
 *		                                
 ************************************************************************/
class CarLot {
 private:
	std::vector<Car> Cars;

 public:
	void 	addCar(Car newCar);
	void 	listCurrentInv();
	void 	getMonthProfit(int, int);
};

/* Constructor */
void CarLot::addCar(Car newCar)
{
	Cars.push_back(newCar);
}

void CarLot::listCurrentInv()
{
	bool header=true; // whether or not to print the column headers
	int totalCars=0;  // keep a running total

	if (DEBUG) std::cout << "CarLot::list" << std::endl; // DEBUG
	std::cout << std::endl << "Listing all cars in inventory:" << std::endl;
	for (int i=0; i< Cars.size(); i++)
	{
		if (DEBUG) 
		{
			// print everything in debug mode
			Cars[i].print();
		}
		else if (! Cars[i].IsSold())
		{
			// otherwise, only print cars that haven't sold
			if (header)
			{
				Cars[i].printHeader();
				header=false;
			}
			Cars[i].print();
			totalCars++;
		}
	}
	if (totalCars == 0)
	{
		std::cout << std::endl << "No cars currently in inventory" << std::endl;
	}
	else 
	{
		std::cout << std::endl << "TOTAL: " << totalCars 
			<< " cars in inventory as of today" << std::endl;
	}
}

void CarLot::getMonthProfit(int month, int year)
{
	bool printHeader=true;  // whether or not to print the column headers
	bool carsFound=false;		// any cars sold in the month/year requested?
	double totalProfit = 0; // a running total

	if (DEBUG) std::cout << "CarLot::getMonthProfit" << std::endl;
	for (int i=0; i< Cars.size(); i++)
	{
		if (Cars[i].IsSold())
		{
			if (Cars[i].getSaleMonth() == month && Cars[i].getSaleYear() == year)
			{
				if (printHeader)
				{
					std::cout << std::endl << "Listing all cars sold in " <<
						month << "/" << year << ":" <<std::endl;
					Cars[i].printHeader();
					printHeader=false;
					carsFound = true;
				}
				Cars[i].print();
				totalProfit += (Cars[i].getProfit());
			}
		}
	}
	if (! carsFound)
	{
		std::cout <<  std::endl << "No cars sold in " << month << "/" << year 
			<< std::endl;
	}
	else
	{
		std::cout << std::endl << std::fixed << std::setprecision(2) 
			<< "Net profit: $" << totalProfit << std::endl;
	}
}

/************************************************************************
 *
 * main()
 *
 * Print a menu of choices and handle user requests
 *
 ************************************************************************/
enum 	Action {Add, List, Profit, Quit, unknown}; // Menu options


/* Function prototypes */
void	readOneLine(std::string inputLine, CarLot &carInventory);
void	readDataFromFile(CarLot &carInventory);
Date	 validateDateInput(std::string inputString);
Action getUserAction();
Car newCar();

main(int argc, char**argv) {
	Action nextAction = Quit;	 // the user's choice of actions
	Car tmpCar;
	CarLot carInventory;
	Date dateProfit;
	std::string tmpInput;

	// Secret debugging capability loads data file into program
	if (argc > 1)
		readDataFromFile(carInventory);

	std::cout << "Welcome to CarManager 2.0, new and improved!" <<std::endl <<
		"Your first choice in car lot inventory systems." << std::endl;
		do
		{
			nextAction = getUserAction();
			switch (nextAction) {
				case Add:
					tmpCar = newCar();
					carInventory.addCar(tmpCar);
					break;
				case List:
					carInventory.listCurrentInv();
					break;
				case Profit:
					std::cout << "Enter the month/year for calculating profit [mm/yyyy]: ";
					getline(std::cin, tmpInput);
					dateProfit = validateDateInput(tmpInput);
					carInventory.getMonthProfit(dateProfit.getMonth(), dateProfit.getYear());
					break;
				case Quit:
					break;
				default:
					std::cout << "Unrecognized command, please try again." <<std::endl;
					break;
			}
		}
		while (nextAction != Quit);
}

/*
 * newCar()
 *
 * This function handles user input for fields that will be 
 * passed to the Car::Car  constructor.  The Car object is created
 * in this function and passed back to the caller.
 *
 * Returns: A Car object
 *
 */
Car newCar()
{
	int buflen=2048;
	char answer;					// Single char user input
	char buffer[buflen];	// temporary string storage
	bool goodData;
	std::string indent = "*    ";
	std::string tmpInput; // String user input

	std::string make;
	std::string model;
	int			year;
	double	purchasePrice;
	bool		isSold;
	double	salePrice;
	Date	dateSold;
	Date	datePurchased;


	std::cout << indent << "Car make: ";
		getline(std::cin, make);
	std::cout << indent << "Car model: ";
		getline(std::cin, model);
	std::cout << indent << "Car year:";
		getline(std::cin, tmpInput);
		year = atoi(tmpInput.c_str());
	std::cout << indent << "Date of purchase[mm/dd/yyyy]: ";
	getline(std::cin, tmpInput);
	datePurchased = validateDateInput(tmpInput);
	if (DEBUG) std::cout << "datePurchased " << datePurchased.getMonth() << "/" << datePurchased.getDay() << "/" << datePurchased.getYear() << std::endl;
	std::cout << indent << "Purchase Price[0-]:";
	getline(std::cin, tmpInput);
	purchasePrice = atof(tmpInput.c_str());

	std::cout << indent << "Has this car been sold?[yn] ";
 	answer = std::cin.get();	
	std::cin.getline(buffer,buflen);
	if (answer == 'y' || answer == 'Y')
		isSold = true;
 	else
		isSold = false;

  if (isSold)
	{
		std::cout << indent << "Date of sale [mm/dd/yyyy]: ";
		getline(std::cin, tmpInput);
		dateSold = validateDateInput(tmpInput);
		std::cout << indent << "Sale Price:";
		getline(std::cin, tmpInput);
		salePrice = atof(tmpInput.c_str());
		Car tmpCar(make,model,year, datePurchased,purchasePrice, isSold,dateSold,salePrice );
		// TODO!
		//Car *tmpCar;
    //tmpCar  = new Car(.......);
		//if (DEBUG) tmpCar.print();
		return (tmpCar);
	}
	else {
		Car tmpCar(make,model,year, datePurchased,purchasePrice, isSold);
		//if (DEBUG) tmpCar.print();
		return (tmpCar);
	}
}

/*****************************************************
 * 
 ****************************************************/
Date	 validateDateInput(std::string inputString)
{
	std::string dash = "/"; // Our separator
	std::string tmpStr;			// For the substrings we find between separators
	std::size_t dash1, dash2; // The string position of separator characters
	int tmpMonth = 0, tmpDay = 0, tmpYear = 0;

	dash1 = inputString.find(dash);
	dash2 = (inputString.substr(dash1+1)).find(dash);

	if (DEBUG) std::cout << "dash1 = " << dash1 << "  dash2 = " << dash2 << std::endl;

	if (dash1 !=0 )
	{
		tmpStr = inputString.substr(0,dash1);
		tmpMonth = atoi(tmpStr.c_str());

		if (dash2 != std::string::npos )
		{
			tmpStr = inputString.substr(dash1+1,dash2);
			tmpDay = atoi(tmpStr.c_str());
	
			tmpStr = inputString.substr(dash1+dash2+2);
			tmpYear = atoi(tmpStr.c_str());
		}
		else
		{
			tmpStr = inputString.substr(dash1+1);
			tmpYear = atoi(tmpStr.c_str());
		  tmpDay  = 1;	
		}
	}
	if (DEBUG) std::cout << "Create a Date with " << tmpMonth << "/" << tmpDay << "/" << tmpYear << std::endl;
	Date tmpDate(tmpMonth, tmpDay, tmpYear);
	return (tmpDate);
}

/*****************************************************
 * getUserAction
 * 
 * Print the menu and get the user's menu choice
 * Returns: An Action (enum int)
 ****************************************************/
Action	 getUserAction()
{
	char Menu[] = {'A','L','P','Q'};
	char menuChoice;
	Action actionChoice;
	int buflen=1024;
	char buffer[buflen];
	int i;

	std::cout << std::endl <<
		"[A]dd a car to inventory" << std::endl <<
		"[L]ist cars in inventory" << std::endl <<
		"[P]rofit (calculated per month)" << std::endl <<
		"[Q]uit" << std::endl << std::endl <<
		"What do you want to do? (A,L,P,Q): ";
  menuChoice = std::cin.get();     // get the first character
	std::cin.getline(buffer,buflen); // throw away what's left in the buffer
	for (i=0; i<4; i++ )
	{
		if ( toupper(menuChoice) == Menu[i] )
		{
			actionChoice = (Action) i;
			return (actionChoice);
		}
	}
	return (unknown);
}


/*****************************************************
 * readDataFromFile
 * 
 * Hidden function to read Car data from a file for 
 * easier debugging
 * Arguments: A reference to a vector of Car
 *****************************************************/
void readDataFromFile(CarLot &carInventory)
{
	std::string comment = "#"; // not implemented yet
	std::string inputLine;
	std::ifstream dataFile("carLot.data");

  if ( dataFile.is_open() )
	{
		while ( ! dataFile.eof() )
		{
			getline(dataFile, inputLine);
			readOneLine(inputLine, carInventory);
		}
	}
}

/*****************************************************
 * 
 ****************************************************/
void readOneLine(std::string inputLine, CarLot &carInventory)
{
	bool IsSold;
	bool goodData;
	char tmpbuf[1024];			// cstring for parsing the line
	char delimiter = ':'; 	// The word separating character in the file
  std::vector <std::string> Word;	// The input line, separated into words
	std::string item;				// convert cstrings into std::strings
	Date purDate, selDate;	// convert the strings into Date structs


	if(DEBUG) std::cout << "readOneLine\n";

  std::stringstream ss(inputLine);
  while (ss.getline(tmpbuf, 1024, delimiter)) {
		if(DEBUG) std::cout << "tmpbuf = " << tmpbuf << "\n";
		item = tmpbuf;
		Word.push_back(item);
  }
	if ( Word.size() == 0 )
		return;

	// Word should contain:
	// 	0     1      2     3             4              5 
	// 	Make, Model, Year, PurchaseDate, PurchasePrice, IsSold
	// 
	// 	6          7
	// 	SaleDate, SalesPrice
	//
  purDate = validateDateInput(Word[3]);
	if (Word[5].compare("true") == 0)
	{
		IsSold = true;
  	selDate = validateDateInput(Word[6]);
	}
	else
		IsSold = false;

  // Declare and initialize a temporary struct
	//Car tmpCar = {Word[0],Word[1], atoi(Word[2].c_str()), purDate, atof(Word[4].c_str()),IsSold };
	if (IsSold) 
	{
		Car tmpCar((std::string)Word[0],(std::string)Word[1], atoi(Word[2].c_str()), purDate, atof(Word[4].c_str()),IsSold,selDate,atof(Word[7].c_str() ));
		carInventory.addCar(tmpCar);
	}
	else
	{
		Car tmpCar((std::string)Word[0],(std::string)Word[1], atoi(Word[2].c_str()), purDate, atof(Word[4].c_str()),IsSold );
		carInventory.addCar(tmpCar);
	}
}
