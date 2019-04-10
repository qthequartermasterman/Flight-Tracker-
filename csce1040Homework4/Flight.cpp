///*=============Flight.cpp================*/
/*
 DESCRIPTION:   
 AUTHOR:        Andrew P. Sansom
 VERSION:       1.0.0
 VERSION DATE:  3/19/19
 EMAIL:         andrewsansom@my.unt.edu
 COURSE:        CSCE 1040
 =============Flight.cpp================*/

#include "Flight.h"
#include <iostream>
#include <iomanip>
#include <ctime>


/*
 int flightID
 std::string planeID;
 int numberOfPilots; //(integer) [flights over 8 hours need 2 pilots and 2 copilots]
 int numberOfCrewCabin; //(integer) [8 hour flights need twice the minimum]
 std::vector<int> pilotIDs; //vector of all the pilots aboard a flight.
 std::vector<int> cabinCrewIDs; //vector of all the cabincrew aboard a flight.
 time_t startTime; // (date/time)
 time_t endTime; //(date/time)
 std::string startPort; //string representing the airport that the plane departs from.
 std::string endPort; //string representing the airport that the plane arrives at.
 int numberOfPassengers; //(integer)
 int status; //(integer) 0 = canceled, 1 = Active, 2 = Completed
 */
void Flight::printInfo(){
    
    std::cout << std::left << std::setw(10) << "Flight ID" << std::setw(10) << "Plane ID" << std::setw(15) << "Passengers" << std::setw(10) << "Status\n";
    std::cout << std::left << std::setw(10) << flightID << std::setw(10) << planeID << std::setw(15) << numberOfPassengers << std::setw(10);
    switch (status){
        case 0: std::cout << "Cancelled\n"; break;
        case 1: std::cout << "Active\n"; break;
        case 2: std::cout << "Completed\n"; break;
    }
    //Print Pilot information
    std::cout << std::left << std::setw(20) << "Minimum Pilots: " << std::setw(3) << numberOfPilots << std::setw(20) << "Assigned Pilots: " << std::setw(3) << pilotIDs.size() << std::endl;
    std::cout << "Pilots: ";
    //Print each pilot's id.
    for (std::vector<int>::iterator i = pilotIDs.begin(); i < pilotIDs.end(); i++){
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    //Print Crew information
    std::cout << std::left << std::setw(20) << "Minimum Crew: " << std::setw(3) << numberOfCrewCabin << std::setw(20) << "Assigned Crew: " << std::setw(3) << cabinCrewIDs.size() << std::endl;
    std::cout << "Cabin Crew: ";
    //Print each crewmember's id.
    for (std::vector<int>::iterator i = cabinCrewIDs.begin(); i < cabinCrewIDs.end(); i++){
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    //Print Departure/Arrival information
    std::cout << std::setw(12) << "Departure:" << std::setw(15) << startPort << std::setw(30) << ctime(&startTime) << std::endl;
    std::cout << std::setw(12) << "Arrival:" << std::setw(15) << endPort << std::setw(30) << ctime(&endTime) << std::endl;
    
}

bool Flight::isCrewOnFlight(int crewID){
    std::vector<int>::iterator ptr;
    //Check if employee is onboard as a cabin crew
    for (ptr = cabinCrewIDs.begin(); ptr < cabinCrewIDs.end(); ptr++){
        if (*ptr == crewID){
            return true;
        }
    }
    //CHeck if onboard as a pilot
    for (ptr = pilotIDs.begin(); ptr < pilotIDs.end(); ptr++){
        if (*ptr == crewID){
            return true;
        }
    }
    return false;
}
