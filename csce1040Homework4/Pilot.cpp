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
