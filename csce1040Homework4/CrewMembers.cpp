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
#include "Pilot.h"
#include "Copilot.h"
#include "Cabin.h"

#include <iostream>
#include <iterator>
#include <iomanip>
#include <fstream>

void CrewMembers::addCrew(){
    CrewMember *newEmployee = nullptr;
    std::string name;
    std::string type;
    bool validType = false;
    int id;
    
    std::cout << "Creating New Employee:\n";
    //Enter career type
    std::cout << "Type of Employee (Pilot, Copilot, Cabin): ";
    std::cin >> type; std::cin.ignore();
    
    //Enter Name
    std::cout << "Name of Employee: ";
    std::getline(std::cin, name);

    //Enter ID
    std::cout << "Employee ID: ";
    std::cin >> id; std::cin.ignore();
    while (CrewMembers::isIDtaken(id)){
        std::cout << "Employee ID already in use. Please choose another: ";
        std::cin >> id; std::cin.ignore();
    }

    //Specific Career type data
    do{
        if (type[0] == 'P' || type[0] == 'p'){
            //newEmployee.setCareerType("Pilot");
            newEmployee = new Pilot();
            validType = true;
            
            //Pilot Data
            std::string pilotRating;
            float cumulativeFlightHours;
            Pilot* newPilot = dynamic_cast<Pilot*>(newEmployee);
            
            std::cout << "Enter 5 digit Pilot code: ";
            std::cin >> pilotRating; std::cin.ignore();
            newPilot->setPilotRating(pilotRating);
            std::cout << "Enter Pilot's cumulative flight hours: ";
            std::cin >> cumulativeFlightHours; std::cin.ignore();
            newPilot->setCumulativeFlightHours(cumulativeFlightHours);
            
            
        } else if ((type[0] == 'C' || type[0] == 'c') && (type[1]=='a' || type[1]=='A')){
            //newEmployee.setCareerType("Cabin");
            newEmployee = new Cabin();
            validType = true;
            Cabin* newCabin = dynamic_cast<Cabin*>(newEmployee);
            newCabin->setCrewType();
        } else if((type[0] == 'C' || type[0] == 'c') && (type[1]=='o' || type[1]=='O')){
            newEmployee = new Copilot();
            validType = true;
            
            //CoPilot Data
            std::string pilotRating;
            float cumulativeFlightHours;
            Copilot* newCoPilot = dynamic_cast<Copilot*>(newEmployee);
            
            std::cout << "Enter 4 digit Copilot code: ";
            std::cin >> pilotRating; std::cin.ignore();
            newCoPilot->setCoPilotRating(pilotRating);
            std::cout << "Enter Copilot's cumulative flight hours: ";
            std::cin >> cumulativeFlightHours; std::cin.ignore();
            newCoPilot->setCumulativeFlightHours(cumulativeFlightHours);
            
        }else{
            std::cout << "Invalid Employee Type. Correct Employee type: ";
            std::cin>>type; std::cin.ignore();
        }
    } while (!validType);
    
    newEmployee->setName(name);
    newEmployee->setID(id);

    
    
    
    
    
    
    
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
                            //crewMemberWithID->setCareerType("Pilot");
                            validType = true;
                        } else if (type[0] == 'C' || type[0] == 'c'){
                            //crewMemberWithID->setCareerType("Cabin");
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
    std::vector<CrewMember*>::iterator ptr;
    
    std::cout <<"Deleting Employee...\n" << "Employee ID: ";
    std::cin >> id; std::cin.ignore();
    
    for (ptr = CREWMEMBERS.begin(); ptr < CREWMEMBERS.end(); ptr++){
        if ((*ptr)->getID()==id){
            delete (*ptr);
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
    std::vector<CrewMember*>::iterator ptr;
    for (ptr = CREWMEMBERS.begin(); ptr < CREWMEMBERS.end(); ptr++){
        if ((*ptr)->getID()==crewID){
            return (*ptr);
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
    std::cout << std::left << std::setw(8) << "ID:" << std::setw(20) << "Name:" <<std::endl;
    std::vector<CrewMember*>::iterator ptr;
    for (ptr = CREWMEMBERS.begin(); ptr < CREWMEMBERS.end(); ptr++){
        (*ptr)->printInfo();
    }
} //iterates over every CrewMember in the collection and runs printIndividualInfo(crewID) with their respective crewID.
void CrewMembers::printIndividualInfo(int crewID){
    CrewMember* crewMemberWithID = findCrewMemberByID(crewID);
    if (crewMemberWithID){
        std::cout << std::left << std::setw(8) << "ID:" << std::left << std::setw(20) << "Name:" <<std::endl;
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
    std::vector<CrewMember*>::iterator ptr;
    for (ptr = CREWMEMBERS.begin(); ptr < CREWMEMBERS.end(); ptr++){
        if ((*ptr)->getID()==crewID){
            return true;
        }
    }
    return false;
} //checks all of the CrewMembers to see if there is already a CrewMember with the specified id.

void CrewMembers::storeData(){
    std::ofstream fout;
    fout.open("crewmembers.dat");
    
    //Iterate over each plane, and add the data
    std::vector<CrewMember*>::iterator ptr;
    fout << CREWMEMBERS.size() << std::endl; //The number of planes. This will just make life easier as we load data.
    for (ptr = CREWMEMBERS.begin(); ptr < CREWMEMBERS.end(); ptr++){
        fout << (*ptr)->getType() << std::endl; //Type of employee
        fout << (*ptr)->getID() << std::endl; //employee id
        fout << (*ptr)->getName() << std::endl; //employee name
        //The career specific data will look different depending on the type of employee.
        if ((*ptr)->getType()==PILOTTYPE){
            Pilot* pilot = dynamic_cast<Pilot*>(*ptr);
            fout << pilot->getPilotRating() << std::endl;
            fout << pilot->getCumulativeFlightHours() << std::endl;
        } else if ((*ptr)->getType()==COPILOTTYPE){
            Copilot* copilot = dynamic_cast<Copilot*>(*ptr);
            fout << copilot->getCopilotRating() << std::endl;
            fout << copilot->getCumulativeFlightHours() << std::endl;
        } else if ((*ptr)->getType()==CABINCREWTYPE){
            Cabin* cabin = dynamic_cast<Cabin*>(*ptr);
            fout << cabin->getCrewType() << std::endl;
        }
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
        int careerType;
        fin >> careerType; fin.ignore();
        if (careerType == PILOTTYPE){
            Pilot* newPilot = new Pilot();
            std::string name;
            int ID;
            std::string pilotRating;
            int inflightHours;
            
            fin >> ID; fin.ignore();
            std::getline(fin, name);
            fin >> pilotRating; fin.ignore();
            fin >> inflightHours; fin.ignore();
            
            newPilot->setName(name);
            newPilot->setID(ID);
            newPilot->setPilotRating(pilotRating);
            newPilot->setCumulativeFlightHours(inflightHours);
            CREWMEMBERS.push_back(newPilot);
        } else if (careerType == COPILOTTYPE){
            Copilot* newCoPilot = new Copilot();
            std::string name;
            int ID;
            std::string copilotRating;
            int inflightHours;
            
            fin >> ID; fin.ignore();
            std::getline(fin, name);
            fin >> copilotRating; fin.ignore();
            fin >> inflightHours; fin.ignore();
            
            newCoPilot->setName(name);
            newCoPilot->setID(ID);
            newCoPilot->setCoPilotRating(copilotRating);
            newCoPilot->setCumulativeFlightHours(inflightHours);
            CREWMEMBERS.push_back(newCoPilot);
        }else if (careerType == CABINCREWTYPE){
            Cabin* newCabin = new Cabin();
            std::string name;
            int ID;
            int cabinCrewType;
            
            fin >> ID; fin.ignore();
            std::getline(fin, name);
            fin >> cabinCrewType; fin.ignore();
            
            newCabin->setName(name);
            newCabin->setID(ID);
            newCabin->setCrewType(static_cast<CabinCrewType>(cabinCrewType));
            CREWMEMBERS.push_back(newCabin);
        }
        
    }
    fin.close();
} //Loads data from disk.


bool CrewMembers::isCrewMemberOfType(int crewMemberID, int crewMemberType){
    CrewMember* crewMemberWithID = findCrewMemberByID(crewMemberID);
    if (crewMemberWithID->getType() == crewMemberType){
        return true;
    } else {
        return false;
    }
}//returns true if the crewmember with the given ID is of the correct type.


CrewMembers::~CrewMembers(){
    std::vector<CrewMember*>::iterator it;
    for (it = CREWMEMBERS.begin(); it < CREWMEMBERS.end(); it++){
        delete (*it);
    }
}
