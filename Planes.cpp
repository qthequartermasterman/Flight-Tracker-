///*=============Planes.cpp================*/
/*
 DESCRIPTION:   
 AUTHOR:        Andrew P. Sansom
 VERSION:       1.0.0
 VERSION DATE:  3/19/19
 EMAIL:         andrewsansom@my.unt.edu
 COURSE:        CSCE 1040
 =============Planes.cpp================*/

#include "Planes.h"
#include <iterator>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "Plane.h"

void Planes::addPlane(){
    Plane newPlane;
    std::string make;
    std::string model;
    std::string tailNumber;
    int numberOfSeats;
    int range;
    int minimumNumberOfCrew;
    
    std::cout << "Creating New Plane:\n";
    //Enter Make
    std::cout << "Make of Plane: ";
    std::getline(std::cin, make);
    newPlane.setMake(make);
    //Enter model
    std::cout << "Plane Model: ";
    std::cin >> model; std::cin.ignore();
    newPlane.setModel(model);
    //Enter TailNumber
    std::cout << "Tail Number: ";
    std::cin >> tailNumber; std::cin.ignore();
    while (Planes::isIDtaken(tailNumber)){
        std::cout << "Plane Tail Number already in use. Please choose another: ";
        std::cin >> tailNumber; std::cin.ignore();
    }
    newPlane.setID(tailNumber);
    //Enter number of seats
    std::cout << "Number of Seats: ";
    std::cin >> numberOfSeats; std::cin.ignore();
    while (numberOfSeats<=0){
        std::cout << "Invalid number of seats. Please enter a number greater than 0: ";
        std::cin >> numberOfSeats; std::cin.ignore();
    }
    newPlane.setNumberOfSeats(numberOfSeats);
    //Enter range
    std::cout << "Maximum range of plane (to the nearest mile): ";
    std::cin >> range; std::cin.ignore();
    while (range<=0){
        std::cout << "Invalid range. Please enter a number greater than 0: ";
        std::cin >> range; std::cin.ignore();
    }
    newPlane.setRange(range);
    //Enter minimumNumberOfCrew
    std::cout << "Minimum number of crew: ";
    std::cin >> minimumNumberOfCrew; std::cin.ignore();
    while (minimumNumberOfCrew<=0){
        std::cout << "Invalid number of crew. Please enter a number greater than 0: ";
        std::cin >> minimumNumberOfCrew; std::cin.ignore();
    }
    newPlane.setMinimumNumberOfCrew(minimumNumberOfCrew);
    PLANES.push_back(newPlane);
} /*presents a dialog to the user that asks for the potential plane’s data:
                  -Make (string)
                  -Model (string)
                  -Tail Number (string)
                  -Number of Seats (integer)
                  -Range (integer)
                  -minimumNumberOfCrew (integer)
                  -Before accepting each value, it checks if the value is valid. E.G. Seat Number, Range, and minimumNumberOfCrew must all be nonnegative. It then creates a new plane, adds it to the collection, and sets all of its info to the recorded values.*/

void Planes::editPlane(){
    std::string id;
    std::cout <<"Editing Plane...\n" << "Plane Tail Number: ";
    std::cin >> id; std::cin.ignore();
    
    Plane* planeWithID = findPlaneByID(id);
    if (planeWithID){
        //PUT THE STUFF HERE
        int option=-1; //Set to -1, just to avoid interference.
        while (option != 0){
            std::cout << "Which property would you like to change?\n" <<
            "0. Change nothing. Exit.\n"
            "1. Make\n"
            "2. Model\n"
            "3. Number of Seats\n"
            "4. Range\n"
            "5. Minimum Number of Crew\n";
            std::cout << "Number of property you wish to change: ";
            std::cin >> option; std::cin.ignore();
            switch(option){
                case 0:
                    break;
                case 1:{
                    std::string newName;
                    std::cout << "New make of plane: ";
                    getline(std::cin, newName);
                    planeWithID->setMake(newName);
                    std::cout << "Make changed.\n";
                    break;
                }
                case 2:{
                    std::string newName;
                    std::cout << "New model of plane: ";
                    std::getline(std::cin, newName);
                    planeWithID->setModel(newName);
                    std::cout << "Model changed.\n";
                    break;
                }
                case 3:{
                    int newNum;
                    std::cout << "WARNING: Changing the minimum number of crew might cause a flight to be overbooked.\n";
                    std::cout << "New number of seats: ";
                    std::cin >> newNum;
                    planeWithID->setNumberOfSeats(newNum);
                    std::cout << "Name changed.\n";
                    break;
                }
                case 4:{
                    int newNum;
                    std::cout << "WARNING: Changing the range might cause a flight to be too long.\n";
                    std::cout << "New range (to the nearest mile): ";
                    std::cin >> newNum;
                    planeWithID->setRange(newNum);
                    std::cout << "Range changed.\n";
                    break;
                }
                case 5:{
                    int newNum;
                    std::cout << "WARNING: Changing the minimum number of crew might cause a flight to be understaffed.\n";
                    std::cout << "New Minimum Number of Crew: ";
                    std::cin >> newNum;
                    planeWithID->setMinimumNumberOfCrew(newNum);
                    std::cout << "Minimum number of crew changed.\n";
                    break;
                }
                default:
                    std::cout << "Unrecognized Input. Please enter the number of the option you would like.\n";
                    break;
            }
        }
    } else {
        std::cout << "Crew Member with that ID is not found. Aborting edit.\n";
    }
} //presents a dialog to the user asking which properties they would like to change. It then prompts for the new value, checking against its restrictions. If the user tries to change a value that will cause another property to have an illegal value, it warns the user. If the user decides to continue, it then asks for updated values of the other properties.
//NOTE: This might mean that some already booked flights might have too few CrewMembers. If the minimumNumberOfCrew increases, then run “updateCrewForAllFlightsWithPlane(planeID)”, which will prompt the user to update the crews on flights with this plane.
void Planes::deletePlane(){
    std::string id;
    bool removedPlane = false;
    std::vector<Plane>::iterator ptr;
    
    std::cout <<"Deleting Plane...\n" << "Tail Number: ";
    std::cin >> id; std::cin.ignore();
    
    for (ptr = PLANES.begin(); ptr < PLANES.end(); ptr++){
        if (ptr->getID()==id){
            PLANES.erase(ptr);
            std::cout << "Removed Plane.\n";
            removedPlane = true;
        }
    }
    if (!removedPlane) std::cout << "Plane with that tail number was not found... Aborting...\n";
} //presents a dialog to the user that asks for the ID of the plane that they would like to delete. It then asks for confirmation before deleting the plane object and updating the collection.
Plane* Planes::findPlaneByID(std::string planeID){
    std::vector<Plane>::iterator ptr;
    for (ptr = PLANES.begin(); ptr < PLANES.end(); ptr++){
        if (ptr->getID() == planeID){
            return &(*ptr);
        }
    }
    
    return nullptr;
} //returns all planes with the given planeID.
void Planes::printListOfPlanes(){
    std::cout << "Printing list of all planes.\n";
    std::cout << std::left << std::setw(10) << "Make" << std::setw(6) <<"Model" << std::setw(6) << "Tail" << std::setw(6) << "Seats" << std::setw(6) << "Range" << std::setw(6) << "Minimum Crew" << std::endl;
    std::vector<Plane>::iterator ptr;
    for (ptr = PLANES.begin(); ptr < PLANES.end(); ptr++){
        ptr->printInfo();
    }
} //runs printIndividualPlaneInfo(planeID) for every plane in the collection.
void Planes::printIndividualPlaneInfo(std::string planeID){
    Plane* planeWithID = findPlaneByID(planeID);
    if (planeWithID){
        std::cout << std::right << std::setw(10) << "Make" << std::setw(6) <<"Model" << std::setw(6) << "Tail" << std::setw(6) << "Seats" << std::setw(6) << "Range" << std::setw(6) << "Minimum Crew" << std::endl;
        planeWithID->printInfo();
    } else {
        std::cout << "Plane with that ID is not found. Aborting print.\n";
    }
} //displays an individual plane’s information in an organized table to the console.

void Planes::printIndividualPlaneInfo(){
    std::string planeID;
    std::cout << "Please enter the tail number of the plane who's record you would like to see.\n";
    std::cin >> planeID;
    printIndividualPlaneInfo(planeID);
}

bool Planes::doesPlaneHaveEnoughSeats(std::string planeID, int necessaryNumberOfSeats){
    std::vector<Plane>::iterator ptr;
    for (ptr = PLANES.begin(); ptr < PLANES.end(); ptr++){
        if (ptr->getID() == planeID){
            if (ptr->getNumberOfSeats()>=necessaryNumberOfSeats){
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
} //searches for the plane in its collection with planeID, and checks if it has greater than or equal to the necessaryNumberOfSeats, returning the result.

bool Planes::isIDtaken(std::string planeID){
    std::vector<Plane>::iterator ptr;
    for (ptr = PLANES.begin(); ptr < PLANES.end(); ptr++){
        if (ptr->getID() == planeID){
            return true;
        }
    }
    return false;
} //checks all of the planes to see if there is already a plane with the specified id.

int Planes::getMinCrewOfPlane(std::string planeID){
    Plane* planeWithID = findPlaneByID(planeID);
    return planeWithID->getMinimumNumberOfCrew();
}

void Planes::loadData(){
    PLANES.clear();
    std::ifstream fin;
    int numberOfPlanes;
    fin.open("planes.dat");
    fin >> numberOfPlanes; fin.ignore();
    //Iterate over the planes in the document.
    for (int i =0; i < numberOfPlanes; i++){
        Plane newPlane;
        std::string make;
        std::string model;
        std::string tailNumber;
        int numberOfSeats;
        int range;
        int minimumNumberOfCrew;
        
        std::getline(fin,make);
        std::getline(fin,model);
        std::getline(fin,tailNumber);
        fin >> numberOfSeats;
        fin >> range;
        fin >> minimumNumberOfCrew;
        fin.ignore();
        
        newPlane.setMake(make);
        newPlane.setModel(model);
        newPlane.setID(tailNumber);
        newPlane.setNumberOfSeats(numberOfSeats);
        newPlane.setRange(range);
        newPlane.setMinimumNumberOfCrew(minimumNumberOfCrew);
        
        PLANES.push_back(newPlane);
    }
    fin.close();
} //Loads data from disk.
void Planes::storeData(){
    std::ofstream fout;
    fout.open("planes.dat");
    
    //Iterate over each plane, and add the data
    std::vector<Plane>::iterator ptr;
    fout << PLANES.size() << std::endl; //The number of planes. This will just make life easier as we load data.
    for (ptr = PLANES.begin(); ptr < PLANES.end(); ptr++){
        fout << ptr->getMake() << std::endl;
        fout << ptr->getModel() << std::endl;
        fout << ptr->getID() << std::endl;
        fout << ptr->getNumberOfSeats() << " ";
        fout << ptr->getRange() << " ";
        fout << ptr->getMinimumNumberOfCrew() << std::endl;
    }
    fout.close();
} //Saves data from disk.
