/* vim:ts=2:
 *
 *                     Shoshana Abrass
 *                  CS162 Final Project
 *                     March 17, 2015
 *
 * File name:
 *
 *
 * Purpose:
 *
 *
 *
 */

#include <iostream>
#include <string>

#include "Thing.h"

/* ***********************************************************
 * Constructors
 * ********************************************************* */
Thing::Thing (std::string Na, std::string St)
{
	Name=Na;
	Story=St;
	Weight=1;
	UseFunc = NULL;
	OpenFunc = NULL;
	isContainer=false;
	Open=true;
}

/* ********************************************************* */
void Thing::Print () 
{
	std::cout << Name << ". ";
}

/* ********************************************************* */
std::vector<Thing*> Thing::Examine(int &counter, bool verbose, bool silent)
{
	std::vector<Thing*> Nothing;

	std::cout << Name << ". " << Story << std::endl;

  if (DEBUG_EXAMINE) 
	{ 
		std::cout  << "DEBUG: from Thing::Examine " << std::endl;
		std::cout << "		Name = " << Name << std::endl
			<< "		Story = " << Story << std::endl
			<< "		Weight = " << Weight << std::endl
			<< "		UseFunc = " << UseFunc << std::endl
			<< "		OpenFunc = " << OpenFunc << std::endl
			<< "		isContainer = " << isContainer << std::endl
			<< "		Open = " << Open << std::endl;
	}
	return Nothing; // return an empty vector
}
