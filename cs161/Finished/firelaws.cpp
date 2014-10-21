/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/10/06
 *  Last Modification date: 2014/10/12
 *  Filename: firelaws.cpp
 *
 *  Overview:
 *    Write a program that determines whether a meeting room is in violation of
 *    fire law regulations regarding the maximum room capacity.The program will
 *    read in the maximum room capacity and the number of people to attend the
 *    meeting. If the number of people is less than or equal to the maximum
 *    room capacity, the program announces that it is legal to hold the meeting
 *    and tells how many additional people may legally attend. If the number of
 *    people exceeds the maximum room capacity, the program announces that the
 *    meeting cannot be held as planned due to fire regulations and tells how
 *    many people must be excluded in order to meet the fire regulations.”
 *
 *  Input:
 *  	The capacity of the meeting room (an integer)
 *  	The number of people in the meeting (hopefully an integer)
 *
 *  Output:
 *  	Whether the meeting can be held safely in the room; if not, how many 
 *  	people should be excluded from the meeting to make it fire safe.
 *
 */

#include <iostream>


int main () 
{
	int	room_capacity = 0;	// How many people can the room legally hold
	int	num_attendees = 0; 	// How many people are attending the meeting
	int	over_capacity = 0; 	// How many people must be excluded from the meeting

	std::cout << "Enter the max capacity of the room [1-250]: ";
	std::cin >> room_capacity;
	if ( room_capacity <= 0 || room_capacity > 250 )
	{
		std::cout << "ERROR: We don't have any rooms in that size\n";
		return 1;
	}


	std::cout << "How many people are attending the meeting? [0-250]: ";
	std::cin >> num_attendees;

	if ( num_attendees <= room_capacity ) 
	{
		std::cout << "The meeting can safely be held.\n";
		std::cout << "You can invite " << room_capacity - num_attendees <<
			" more people\n";
		return 0;
	}
	else 
	{
		over_capacity = num_attendees - room_capacity;
		std::cout << "The meeting cannot be held as planned. " << over_capacity;
		if ( over_capacity == 1 )
		{
			std::cout << " person";
		}
		else 
		{
			std::cout << " people";
		}
			std::cout << " must be\n"
				"removed from the meeting to meet fire regulations.\n";
	}
}
