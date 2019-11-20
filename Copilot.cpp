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

void Copilot::editInfo(){
    printInfo();
    //PUT THE STUFF HERE
    int option=-1; //Set to -1, just to avoid interference.
    while (option != 0){
        std::cout << "Which property would you like to change?\n" <<
        "0. Change nothing. Exit.\n"
        "1. Name\n"
        "2. Copilot Rating\n"
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
                setCoPilotRating(newRatingCode);
                break;
            }
            case 3:{
                float newHoursToAdd;
                std::cout << "Number of hours to add to copilot's record: ";
                std::cin >> newHoursToAdd; std::cin.ignore();
                addFlightHours(newHoursToAdd);
                break;
            }
            case 4:{
                float newcumulativeFlightHours;
                std::cout << "Enter copilot's new cumulative flight hours: ";
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
