///*=============CrewMembers.cpp================*/
/*
 DESCRIPTION:   
 AUTHOR:        Andrew P. Sansom
 VERSION:       1.0.0
 VERSION DATE:  3/19/19
 EMAIL:         andrewsansom@my.unt.edu
 COURSE:        CSCE 1040
 =============CrewMembers.cpp================*/

#include "CrewMembers.h"

#include <iostream>
#include <iterator>
#include <iomanip>
#include <fstream>

void CrewMembers::addCrew(){
    CrewMember newEmployee;
    std::string name;
    std::string type;
    bool validType = false;
    int id;
    
    std::cout << "Creating New Employee:\n";
    //Enter Name
    std::cout << "Name of Employee: ";
    std::getline(std::cin, name);
    newEmployee.setName(name);
    //Enter career type
    std::cout << "Type of Employee (Pilot, Cabin): ";
    std::cin >> type; std::cin.ignore();
    do{
        if (type[0] == 'P' || type[0] == 'p'){
            newEmployee.setCareerType("Pilot");
            validType = true;
        } else if (type[0] == 'C' || type[0] == 'c'){
            newEmployee.setCareerType("Cabin");
            validType = true;
        } else{
            std::cout << "Invalid Employee Type. Correct Employee type: ";
            std::cin>>type; std::cin.ignore();
        }
    } while (!validType);
    //Enter ID
    std::cout << "Employee ID: ";
    std::cin >> id; std::cin.ignore();
    while (CrewMembers::isIDtaken(id)){
        std::cout << "Employee ID already in use. Please choose another: ";
        std::cin >> id; std::cin.ignore();
    }
    newEmployee.setID(id);
    
    CREWMEMBERS.push_back(newEmployee);
} //presents a dialog to the user that asks for the potential CrewMember’s ID (integer) and careerType (string, such as Pilot or Cabin).
void CrewMembers::editCrew(){
    int id;
    std::cout <<"Editing Employee...\n" << "Employee ID: ";
    std::cin >> id; std::cin.ignore();
    
    CrewMember* crewMemberWithID = findCrewMemberByID(id);
    if (crewMemberWithID){
        //PUT THE STUFF HERE
        int option=-1; //Set to -1, just to avoid interference.
        while (option != 0){
            std::cout << "Which property would you like to change?\n" <<
            "0. Change nothing. Exit.\n"
            "1. Name\n"
            "2. Career Type\n";
            std::cout << "Number of property you wish to change: ";
            std::cin >> option; std::cin.ignore();
            switch(option){
                case 0:
                    break;
                case 1:{
                    std::string newName;
                    std::cout << "New name of employee: ";
                    getline(std::cin, newName);
                    crewMemberWithID->setName(newName);
                    std::cout << "Name changed.\n";
                    break;
                }
                case 2:{
                    std::string type;
                    bool validType = false;
                    std::cout << "New Type (Pilot, Cabin): ";
                    std::cin >> type; std::cin.ignore();
                    do{
                        if (type[0] == 'P' || type[0] == 'p'){
                            crewMemberWithID->setCareerType("Pilot");
                            validType = true;
                        } else if (type[0] == 'C' || type[0] == 'c'){
                            crewMemberWithID->setCareerType("Cabin");
                            validType = true;
                        } else{
                            std::cout << "Invalid Employee Type. Correct Employee type (Pilot, Cabin): ";
                            std::cin>>type; std::cin.ignore();
                        }
                    } while (!validType);
                    std::cout << "Type change.\n";
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
    
    
} //presents a dialog to the user asking which properties they would like to change. It then prompts for the new value, checking against its restrictions (for example, if an ID is already taken). If the user tries to change a value that will cause another property to have an illegal value, it warns the user. If the user decides to continue, it then asks for updated values of the other properties.
void CrewMembers::deleteCrew(){
    int id;
    bool removedEmployee = false;
    std::vector<CrewMember>::iterator ptr;
    
    std::cout <<"Deleting Employee...\n" << "Employee ID: ";
    std::cin >> id; std::cin.ignore();
    
    for (ptr = CREWMEMBERS.begin(); ptr < CREWMEMBERS.end(); ptr++){
        if (ptr->getID()==id){
            CREWMEMBERS.erase(ptr);
            std::cout << "Removed Employee.\n";
            removedEmployee = true;
        }
    }
    if (!removedEmployee) std::cout << "Employee with that ID was not found... Aborting...\n";
} //presents a dialog to the user that asks for the ID of the CrewMember that they would like to delete. It then asks for confirmation before deleting the CrewMember object and updating the collection.
/*CrewMember CrewMembers::findCrewMembersByName(std::string name){
    
} //searches for every Crew Member with the given name
 */
CrewMember* CrewMembers::findCrewMemberByID(int crewID){
    std::vector<CrewMember>::iterator ptr;
    for (ptr = CREWMEMBERS.begin(); ptr < CREWMEMBERS.end(); ptr++){
        if (ptr->getID()==crewID){
            return &(*ptr);
        }
    }
    std::cout << "Crew Member with given ID not found in system.";
    return nullptr;
} //searches for every CrewMember with the given crewID.
/*std::vector<CrewMember> CrewMembers::findCrewMembersByType(std::string type){
    return ;
} //searches for every CrewMember with the given type.
 */
void CrewMembers::printListOfPeople(){
    std::cout << "Printing list of all employees.\n";
    std::cout << std::left << std::setw(8) << "ID:" << std::setw(20) << "Name:" << std::setw(8) << "Position"<<std::endl;
    std::vector<CrewMember>::iterator ptr;
    for (ptr = CREWMEMBERS.begin(); ptr < CREWMEMBERS.end(); ptr++){
        ptr->printInfo();
    }
} //iterates over every CrewMember in the collection and runs printIndividualInfo(crewID) with their respective crewID.
void CrewMembers::printIndividualInfo(int crewID){
    CrewMember* crewMemberWithID = findCrewMemberByID(crewID);
    if (crewMemberWithID){
        std::cout << std::left << std::setw(8) << "ID:" << std::left << std::setw(20) << "Name:" << std::setw(8) << "Position"<<std::endl;
        crewMemberWithID->printInfo();
    } else {
        std::cout << "Crew Member with that ID is not found. Aborting print.\n";
    }
} //displays an individual CrewMember’s information in an organized table to the console.
void CrewMembers::printIndividualInfo(){
    int crewID;
    std::cout << "Please enter the ID of the employee who's record you would like to see.\n";
    std::cin >> crewID;
    printIndividualInfo(crewID);
    
} //Same as above, but first asks the user for the ID of the individual.
std::string CrewMembers::checkCareerType(int crewID){
    return "";
} //returns the careerType of the crewmember with crewID in the collection.
bool CrewMembers::isIDtaken(int crewID){
    std::vector<CrewMember>::iterator ptr;
    for (ptr = CREWMEMBERS.begin(); ptr < CREWMEMBERS.end(); ptr++){
        if (ptr->getID()==crewID){
            return true;
        }
    }
    return false;
} //checks all of the CrewMembers to see if there is already a CrewMember with the specified id.

void CrewMembers::storeData(){
    std::ofstream fout;
    fout.open("crewmembers.dat");
    
    //Iterate over each plane, and add the data
    std::vector<CrewMember>::iterator ptr;
    fout << CREWMEMBERS.size() << std::endl; //The number of planes. This will just make life easier as we load data.
    for (ptr = CREWMEMBERS.begin(); ptr < CREWMEMBERS.end(); ptr++){
        fout << ptr->getID() << std::endl;
        fout << ptr->getName() << std::endl;
        fout << ptr->getCareerType() << std::endl;
    }
    fout.close();
} //Saves data from disk.

void CrewMembers::loadData(){
    CREWMEMBERS.clear();
    std::ifstream fin;
    int numberOfCrew;
    fin.open("crewmembers.dat");
    fin >> numberOfCrew; fin.ignore();
    //Iterate over the planes in the document.
    for (int i =0; i < numberOfCrew; i++){
        CrewMember newCrew;
        std::string name;
        std::string careerType;
        int ID;
        fin >> ID; fin.ignore();
        std::getline(fin, name);
        std::getline(fin, careerType);
        
        newCrew.setName(name);
        newCrew.setCareerType(careerType);
        newCrew.setID(ID);
        
        CREWMEMBERS.push_back(newCrew);
    }
    fin.close();
} //Loads data from disk.
