///*=============Cabin.cpp================*/
/*
 DESCRIPTION:   
 AUTHOR:        Andrew P. Sansom
 VERSION:       1.0.0
 VERSION DATE:  4/15/19
 EMAIL:         andrewsansom@my.unt.edu
 COURSE:        CSCE 1040
 =============Cabin.cpp================*/

#include "Cabin.h"

#include <iostream>
#include <iomanip>

Cabin::Cabin(){
    
}

std::string Cabin::getCrewTypeAsString(){
    switch (crewType){
            //FirstClass, BusinessClass, EconomyFront, EconomyRear, Lead
        case FirstClass: return "First Class"; break;
        case BusinessClass: return "Business Class"; break;
        case EconomyFront: return "Economy Front"; break;
        case EconomyRear: return "Economy Rear"; break;
        case Lead: return "Lead"; break;
        default: return ""; break;
    }
    
} //Retuns a string that says the crewType.

void Cabin::setCrewType(CabinCrewType crewType_){
    crewType = crewType_;
}

void Cabin::setCrewType(){
    int userInputType;
    do {
        std::cout << "Please enter the number of the role of the the cabin crew member.\n";
        std::cout << "0.FirstClass\n"
        "1.BusinessClass\n"
        "2.EconomyFront\n"
        "3.EconomyRear\n"
        "4.Lead\n";
        std::cout << "Please enter the number of the role of the the cabin crew member:";
        std::cin >> userInputType; std::cin.ignore();
    } while (userInputType < 0 || userInputType > 4);
    crewType = static_cast<CabinCrewType>(userInputType);
    
}//Requests the CrewType from the user.

void Cabin::printInfo(){
    CrewMember::printInfo();
    std::cout << "Cabin \tPosition: " << std::setw(12) << getCrewTypeAsString() << std::endl;
}

void Cabin::editInfo(){
    printInfo();
    //PUT THE STUFF HERE
    int option=-1; //Set to -1, just to avoid interference.
    while (option != 0){
        std::cout << "Which property would you like to change?\n" <<
        "0. Change nothing. Exit.\n"
        "1. Name\n"
        "2. Crew role\n";
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
                setCrewType();
                break;
            }
            default:
                std::cout << "Unrecognized Input. Please enter the number of the option you would like.\n";
                break;
        }
    }
} //Prompts user to edit info for cabin crew.
