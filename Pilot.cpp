///*=============Pilot.cpp================*/
/*
 DESCRIPTION:   
 AUTHOR:        Andrew P. Sansom
 VERSION:       1.0.0
 VERSION DATE:  4/10/19
 EMAIL:         andrewsansom@my.unt.edu
 COURSE:        CSCE 1040
 =============Pilot.cpp================*/

#include "Pilot.h"
#include <iostream>
#include <iomanip>
/*std::string name;
 int ID;
 int status; //available = 1, on leave = 0 , sick = -1
 std::string pilotRating;
 float cumulativeFlightHours;*/

Pilot::Pilot(){
    setName("");
    setID(0);
    setStatus(0);
    setPilotRating("00000");
    setCumulativeFlightHours(0);
}


Pilot::Pilot(std::string name_, int ID_, int status_, std::string pilotRating_, float cumulativeFlightHours_){
    setName(name_);
    setID(ID_);
    setStatus(status_);
    setPilotRating(pilotRating_);
    setCumulativeFlightHours(cumulativeFlightHours_);
}

void Pilot::setPilotRating(std::string pilotRating_){
    while (pilotRating_.size() != 5){
        std::cout << "Pilot rating must be 5 characters.\n";
        std::cout << "Enter a 5 character code:\n";
        std::cin >> pilotRating_;
    }
    pilotRating=pilotRating_;
}

void Pilot::printInfo(){
    CrewMember::printInfo();
    std::cout << "Pilot \tRating: " << std::setw(7) << pilotRating << std::setw(7) << "Hours:" << std::setw(5) << cumulativeFlightHours << std::endl;
}

void Pilot::addFlightHours(float additionalHours){
    cumulativeFlightHours+=additionalHours;
} // Adds additionalHours to cumulative flight hours


void Pilot::editInfo(){
    printInfo();
    //PUT THE STUFF HERE
    int option=-1; //Set to -1, just to avoid interference.
    while (option != 0){
        std::cout << "Which property would you like to change?\n" <<
        "0. Change nothing. Exit.\n"
        "1. Name\n"
        "2. Pilot Rating\n"
        "3. Add flight hours\n"
        "4. Edit cumulative flight hours\n";
        std::cout << "Number of property you wish to change: ";
        std::cin >> option; std::cin.ignore();
        switch(option){
            case 0:
                break;
            case 1:{
                std::string newName;
                std::cout << "New name of employee: ";
                getline(std::cin, newName);
                setName(newName);
                std::cout << "Name changed.\n";
                break;
            }
            case 2:{
                std::string newRatingCode;
                std::cout << "New pilot rating code (5 characters): ";
                setPilotRating(newRatingCode);
                break;
            }
            case 3:{
                float newHoursToAdd;
                std::cout << "Number of hours to add to pilot's record: ";
                std::cin >> newHoursToAdd; std::cin.ignore();
                addFlightHours(newHoursToAdd);
                break;
            }
            case 4:{
                float newcumulativeFlightHours;
                std::cout << "Enter Pilot's new cumulative flight hours: ";
                std::cin >> newcumulativeFlightHours; std::cin.ignore();
                setCumulativeFlightHours(newcumulativeFlightHours);
                break;
            }
            default:
                std::cout << "Unrecognized Input. Please enter the number of the option you would like.\n";
                break;
        }
    }
}
