/* vim: ts=2
 *
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/11/17
 *  Last Modification date: 2014/11/23
 *  Filename: 
 *
 *  Overview:
 *	[x]	Write a struct called Date that consists of an int called day, an int
 *			called month and an int called year.
 *	[x] Write a struct called Car that 	consists of 
 *		a string called make, 
 *		a string called model, 
 *		an int called year, 
 *		a Date called datePurchased, 
 *		a double called purchasePrice, 
 *		a bool called isSold, 
 *		a Date called dateSold, and 
 *		a double called salePrice.
 *
 *	[x]	Create a vector of Car. 
 *	[x] Display a menu that gives the following options:
 *
 *	• Add entry: this allows the user to enter the information for a car, which
 *		is then added to the vector. You should prompt the user for dateSold and
 *		salePrice if and only if is Sold is true.
 *  • List current inventory: this lists the data for all Cars that have been
 *  	purchased, but not yet sold, and then prints out the count of how many cars
 *  	that is.
 *	• Profit for a month: this asks the user for a month and year and displays
 *		the total profit for sales in that month.
 *	• Quit: exits the program.
 *
 *	[x]	Write a separate function to handle each of the first three options. 
 *	[x] All prices and profits should be printed with two decimal places
 *			using showpoint, setprecision and fixed.
 *
 *	[x] Verify that values entered for day and month are valid.
 *			For example: 1/30 is a valid date, but 2/30 is not (don't worry about
 *			leap	years). Of course 15/72 is also not valid. 
 *	[x]	If an invalid date is entered,	prompt the user to try again.
 *
 *	No other input validation	required.
 *
 */

#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "_validateIntegerInput.cpp"
#define DEBUG false

struct Date {
	int Day;
	int Month;
	int Year;
};

struct Car {
	std::string Make;
	std::string Model;
	int Year;
	Date PurchaseDate;
	double PurchasePrice;
	bool IsSold;
	Date SaleDate;
	double SalePrice;
};

std::string Month[] = { 
	"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", 
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
int 	monthDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
enum 	Action {Add, List, Profit, Quit, unknown};

/* Function prototypes */
int 	printHeader(bool IncludeSold);
int 	printACar(Car &thisCar);
bool	validateDateInput(std::string inputString, Date & inputDate);
void 	addCar(std::vector <Car> &carInventory);
void 	listInventory(std::vector <Car> &carInventory);
void 	calculateProfit(std::vector <Car> &carInventory);
void	readOneLine(std::string inputLine, std::vector <Car> &carInventory);
void	readDataFromFile(std::vector <Car> &carInventory);
Action getUserAction();

/* Functions from _validateIntegerData: 
 *
 * int validateIntegerInput(int MinValue, int MaxValue, int MaxTries,
 * 	std::string Prompt)
 *
 * int validateIntegerInput(char *inputString, int MinValue, int MaxValue);
 */

int main (int argc, char**argv) 
{
	std::vector<Car> carInventory;	// The data for all cars
	Action nextAction = Quit;				// Controls the menu 

	if (argc > 1 )
 		readDataFromFile(carInventory); // super secret testing flag. Ha.

	std::cout << "Welcome to CarManager(tm).com, your car lot " <<
		"inventory management app!" << std::endl;
  do
	{
		nextAction = getUserAction();
		switch (nextAction){
			case Add:
				addCar(carInventory);
				break;
			case List:
				listInventory(carInventory);
				break;
			case Profit:
				calculateProfit(carInventory);
				break;
			case Quit:
				break;
			default:
				std::cout << "Unrecognized command, please try again." << std::endl;
				break;
		}
	}
	while (nextAction != Quit);
}

/****************************************************************
 * addCar (std::vector <Car> &carInventory(
 *
 * Parse user input to create a new car for inventory
 * Arguments: A reference to a vector of Car
 ***************************************************************/
void addCar(std::vector <Car> &carInventory)
{
	int buflen=2048;
	char answer;					// Single char user input
	char buffer[buflen];	// temporary string storage
	bool goodData;
	std::string indent = "*    ";
	std::string tmpInput; // String user input
	Car tmpCar;						// temporary Car storage

	std::cout << indent << "Car make: ";
		getline(std::cin, tmpCar.Make);
	std::cout << indent << "Car model: ";
		getline(std::cin, tmpCar.Model);
	std::cout << indent << "Car year:";
		tmpCar.Year = validateIntegerInput(1900,2015,2," ");
	do
	{
		std::cout << indent << "Date of purchase[mm/dd/yyyy]: ";
		getline(std::cin, tmpInput);
		goodData = validateDateInput(tmpInput,tmpCar.PurchaseDate);
	}
	while (goodData == false); // Keep trying indefinitely
	do
	{
		std::cout << indent << "Purchase Price[0-]:";
		getline(std::cin, tmpInput);
		tmpCar.PurchasePrice = atof(tmpInput.c_str());
	}
	while (tmpCar.PurchasePrice <= 0); // Keep trying indefinitely
	std::cout << indent << "Has this car been sold?[yn] ";
  	answer = std::cin.get();	
		std::cin.getline(buffer,buflen);
		if (answer == 'y' || answer == 'Y')
			tmpCar.IsSold = true;
  	else
			tmpCar.IsSold = false;
  if (tmpCar.IsSold)
	{
		do
		{
			std::cout << indent << "Date of sale [mm/dd/yyyy]: ";
			getline(std::cin, tmpInput);
			goodData = validateDateInput(tmpInput,tmpCar.SaleDate);
		}
		while (goodData == false);
		std::cout << indent << "Sale Price:";
			tmpCar.SalePrice = validateIntegerInput(1,2000000,2," ");
	}
  carInventory.push_back(tmpCar); // Copy the new Car into inventory
}
/****************************************************************
 * listInventory(std::vector <CAR> &carInventory) 
 * 
 * List unsold cars
 * Arguments: A reference to a vector of Car
 ***************************************************************/
void listInventory(std::vector <Car> &carInventory)
{
	int totalCars = carInventory.size(); // How large is the vector
	int numCars = 0;  // Cars unsold, still on the lot
	bool carsFound = false; // Are there any unsold cars?

	if (totalCars == 0)
	{
		// The vector is empty
		std::cout << "There are no cars currently in inventory." << std::endl;
		return;
	}

	for (int i=0; i<totalCars; i++)
		if (! carInventory[i].IsSold)
		{
			if (! carsFound)
			{
				std::cout << std::endl <<
					"Listing all cars in inventory:" << std::endl;
				printHeader(false);
				carsFound = true;
			}
			printACar(carInventory[i]);
			numCars++;
		}

	if (carsFound)
		std::cout << std::endl << "TOTAL: " << numCars 
			<< " cars in inventory as of today." << std::endl;
	else
		std::cout << "There are no cars currently in inventory." << std::endl;

	return;
}

/****************************************************************
 * calculateProfit(std::vector <Car> &carInventory)
 *
 * Ask the user for a year/month, calculate profit on cars sold in that month
 * Arguments: A reference to a vector of Car
 ***************************************************************/
void calculateProfit(std::vector <Car> &carInventory)
{
	int totalCars = carInventory.size();	// Size of the inventory vector
	std::string tmpInput1, tmpInput2;	// String user input
	bool goodData = false;
	double purchaseTotal = 0; // Running total to calculate profits
	double salesTotal = 0;		// Running total to calculate profits
	bool carsFound = false;
	Date profitDate;	 // Using a struct to take advantage of validateDateInput

	do
	{
		// It would be better to allow [mm/yyyy] but there's a limit t
		// how much time I can spend :/
		std::cout << "Enter a year for calculating profits [yyyy]: ";
		getline(std::cin, tmpInput1);
		std::cout << "Enter a month [mm]: ";
		getline(std::cin, tmpInput2);
		goodData = validateDateInput(tmpInput2 + "/1/"+tmpInput1,profitDate);
	}
	while (goodData == false);

	for (int i=0; i<totalCars; i++)
	{
		if (DEBUG) std::cout << "proftDate.Month = " << profitDate.Month << ", profitDate.Year = " << profitDate.Year << std::endl;
		if (carInventory[i].IsSold && (carInventory[i].SaleDate.Month == profitDate.Month) && carInventory[i].SaleDate.Year == profitDate.Year )
		{
			if ( ! carsFound)
			{
				// If this is the first car we're printing, print the header first
				std::cout << std::endl <<
					"Listing all cars sold in " << Month[profitDate.Month] <<  " " << profitDate.Year <<": " << std::endl;
				printHeader(true);
				carsFound = true;
			}
			printACar(carInventory[i]);
			purchaseTotal += carInventory[i].PurchasePrice;
			salesTotal += carInventory[i].SalePrice;
		}
	}
	if ( carsFound )
	{
		std::cout << std::endl;
		std::cout << 
			std::fixed <<
			std::setprecision(2) <<
			"Purchase cost: " << 
			"$" << 
			std::setw(8) << std::right<<
			purchaseTotal << std::endl << 
			"Sales  income: " << 
			"$" << 
			std::setw(8) << std::right<<
			salesTotal << std::endl <<
			"   Net profit: " << 
			"$" << 
			std::setw(8) << std::right<<
			salesTotal - purchaseTotal << std::endl;
	}
	else
	{
		std::cout << std::endl << "No cars sold in " << Month[profitDate.Month] << 
			" " << profitDate.Year << std::endl<<
			"Net profit:  $0.00"  << std::endl; 
	}
}

/****************************************************************
 * printHeader(bool IncludeSold)
 * 
 * Print the column headers for car listings
 * Arguments: boolean, do or do not print additional columns for cars sold
 ***************************************************************/
int printHeader(bool IncludeSold)
{
	std::cout << std::endl <<
	"                             Purchase     Purchase";
	if (IncludeSold) 
		std::cout << "         Sales          Sales";

	std::cout << std::endl <<
		"   Year  Make    Model          Price         Date";
	if (IncludeSold) 
		std::cout << "          Date          Price";

	std::cout << std::endl;
}

/****************************************************************
 * printACar(Car &thisCar)
 * 
 * Print formatted columns for a given Car
 * Arguments: A reference to a Car to be printed 
 ***************************************************************/
int printACar(Car &thisCar)
{
  // This is just a long, somewhat tedious, series of formatted cout commadns

  std::cout << 
		std::fixed <<
		std::setprecision(2) << 
		std::left <<
		"   " << std::setw(6) <<
		thisCar.Year << std::setw(8) <<
		thisCar.Make << std::setw(8) <<
		thisCar.Model << std::setw(4) <<
		std::right <<
		"$" << 
		std::setw(8) << std::right<<
		thisCar.PurchasePrice <<
		std::setw(5) << std::right <<
	 	thisCar.PurchaseDate.Month << "/" <<
		std::setw(2) << std::right <<
	 	thisCar.PurchaseDate.Day << "/" <<
		std::setw(7) << std::left <<
	 	thisCar.PurchaseDate.Year;
		
	if (thisCar.IsSold)
	{
		std::cout <<
			std::setprecision(2) <<
			std::setw(3) << std::right <<
			thisCar.SaleDate.Month << "/" <<
			std::setw(2) << std::right <<
			thisCar.SaleDate.Day << "/" <<
			std::setw(7) << std::left <<
			thisCar.SaleDate.Year << std::setw(4) <<
			std::right << 
			"$" << 
			std::setw(8) << std::right <<
			thisCar.SalePrice <<
			std::left;
	}
  std::cout	<< std::endl;


	return(1);
}

/****************************************************************
 * getUserAction
 * 
 * Print the menu and get the user's menu choice
 * Returns: An Action (enum int)
 ***************************************************************/
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

/****************************************************************
 * validateDateInput
 * 
 * Take a string "mm/dd/yyyy" and convert it to a Date struct
 * Arguments: std::string inputString, expecting "mm/dd/yyyy" format
 *            Date reference, validated date is written to this
 * Returns: true if the date is successfully parsed, false otherwise
 ***************************************************************/
bool	 validateDateInput(std::string inputString, Date & inputDate)
{
	std::string dash = "/"; // Our separator
	std::string tmpStr;			// For the substrings we find between separators
	int tmpMonth, tmpDay, tmpYear;
	std::size_t dash1, dash2; // The string position of separator characters

	dash1 = inputString.find(dash);
	if (dash1 !=0 )
	{
		std::string tmpStr = inputString.substr(0,dash1);
 		tmpMonth = validateIntegerInput((char *)tmpStr.c_str(),1,12);
		if (tmpMonth < 1)
			return(false);
			dash2 = (inputString.substr(dash1+1)).find(dash);
			if (dash2 !=0 )
			{
			tmpStr = inputString.substr(dash1+1,dash2);
			tmpDay = validateIntegerInput((char *)tmpStr.c_str(),1,monthDays[tmpMonth]);
			if (tmpDay < 1)
				return(false);
				tmpStr = inputString.substr(dash1+dash2+2);
				tmpYear = validateIntegerInput((char *)tmpStr.c_str(),1900,2014);
				if (tmpYear < 1900)
					return(false);
			}
	}
	inputDate.Month=tmpMonth;
	inputDate.Day=tmpDay;
	inputDate.Year=tmpYear;
	return(true);
}

/****************************************************************
 * readDataFromFile
 * 
 * Hidden function read Car data from a file for easier debugging
 * Arguments: A reference to a vector of Car
 ***************************************************************/
void readDataFromFile(std::vector <Car> &carInventory)
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
void readOneLine(std::string inputLine, std::vector <Car> &carInventory)
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
  validateDateInput(Word[3],purDate);
	if (Word[5].compare("true") == 0)
	{
		IsSold = true;
  	validateDateInput(Word[6],selDate);
	}
	else
		IsSold = false;

  // Declare and initialize a temporary struct
	Car tmpCar = {Word[0],Word[1], atoi(Word[2].c_str()), purDate, atof(Word[4].c_str()),IsSold };
	if (IsSold) 
	{
		tmpCar.SaleDate = selDate;
		tmpCar.SalePrice = atof(Word[7].c_str());
	}
  carInventory.push_back(tmpCar);
}
