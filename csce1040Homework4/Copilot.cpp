///*=============Copilot.cpp================*/
/*
 DESCRIPTION:   
 AUTHOR:        Andrew P. Sansom
 VERSION:       1.0.0
 VERSION DATE:  4/15/19
 EMAIL:         andrewsansom@my.unt.edu
 COURSE:        CSCE 1040
 =============Copilot.cpp================*/

#include "Copilot.h"
#include <iostream>
#include <iomanip>

Copilot::Copilot(){
    
}

void Copilot::printInfo(){
    CrewMember::printInfo();
    std::cout << "Copilot \tRating: " << std::setw(6) << copilotRating << std::setw(7) << "Hours:" << cumulativeFlightHours << std::endl;
}

void Copilot::addFlightHours(float additionalHours){
    cumulativeFlightHours+=additionalHours;
} // Adds additionalHours to cumulative flight hours

void Copilot::setCoPilotRating(std::string copilotRating_){
    while (copilotRating_.size() != 4){
        std::cout << "Pilot rating must be 4 characters.\n";
        std::cout << "Enter a 4 character code:\n";
        std::cin >> copilotRating_;
    }
    copilotRating=copilotRating_;
}
