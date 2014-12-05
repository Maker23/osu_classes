/* vim: ts=2
 *
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/11/24
 *  Last Modification date: 2014/11/30
 *  Filename: geom.cpp
 *
 *  Overview:
 *
 *
 */

#include <iostream>
#include <cstdlib>  // abs()
#include <cmath>  	// pow(),sqrt()
#include <limits>		// infinity


bool	getPointValues(std::string, double &, double &);

/**********************************************************/
class Point
{
 
	double X,Y;

 public:
 	/* constructors */
	Point() {};
	Point(double X_coord, double Y_coord)
	{
		X = X_coord;
		Y = Y_coord;
	}

  /* function prototypes */
	double distanceTo(const Point&);
	double getX();
	double getY();
	void  set(double, double);
};

double Point::getX()
{
	return X;
}
double Point::getY()
{
	return Y;
}
void Point::set(double X_coord, double Y_coord)
{
	X = X_coord;
	Y = Y_coord;
}

double Point::distanceTo(const Point &p2)
{
	double x_distance = fabs(X-p2.X);
	double y_distance = fabs(Y-p2.Y);

	return( (double)sqrt(pow(x_distance,2) + pow(y_distance,2)));
}
/**********************************************************/
class LineSegment
{
  Point P1;
	Point P2;

 public:
	LineSegment(Point P_One, Point P_Two)
	{
		P1.set(P_One.getX(), P_One.getY());
		P2.set(P_Two.getX(), P_Two.getY());
	}

	double length();
	double slope();
};

double LineSegment::length()
{
	return(P1.distanceTo(P2));
}
double LineSegment::slope()
{
	double slope;

  if (P1.getX() < P2.getX())
		slope = (P2.getY() - P1.getY())/(P2.getX() - P1.getX());
	else
		slope = (P1.getY() - P2.getY())/(P1.getX() - P2.getX());
	
	return(slope);
}

/**********************************************************/

int main () 
{
	double X, Y;
	char answer;
	Point p1,p2;


  std::cout << "This program will compute the length and slope of a line"
		<< std::endl << "in an XY coordinate system." << std::endl;
  do
	{
		std::cout << std::endl;
		getPointValues("Point 1", X,Y);
		p1.set(X,Y);
		getPointValues("Point 2", X,Y); 
		p2.set(X,Y);
	
		LineSegment line(p1, p2);
		std::cout << "Length of line = " << line.length() << std::endl;
		std::cout << "Slope of line  = " << line.slope() << std::endl;

		std::cout << "Compute again? [y|n] ";
		std::cin.get(answer);
		std::cin.ignore(2048,'\n');
	}
	while ( toupper(answer) == 'Y');

}

bool getPointValues(const std::string Prompt, double &X, double &Y)
{
	std::string tmpStr;
	bool goodData;
	int comma;

	do {
  	std::cout << "Enter X and Y coordinates for " << Prompt << " [x,y]: ";
		getline(std::cin,tmpStr);
		comma = tmpStr.find(",");
		if ( comma == tmpStr.npos)
		{
			std::cout << "ERROR, please use comma to separate X and Y values" << std::endl;
			goodData = false;
		}
		else
		{
			X = strtod((tmpStr.substr(0, comma)).c_str(), NULL);
			Y = strtod((tmpStr.substr(comma+1, tmpStr.length() - comma)).c_str(),NULL);
			// std::cout << "X = " << X << "  Y = " << Y << std::endl;
			goodData = true;
		}
	}
  while ( ! goodData);
}
