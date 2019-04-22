/*=============main.cpp================*/
/*
 DESCRIPTION:   Rudimentary Airline Model Program
 AUTHOR:        Andrew P. Sansom
 VERSION:       1.0.0
 VERSION DATE:  3/19/19
 EMAIL:         andrewsansom@my.unt.edu
 COURSE:        CSCE 1040
 =============main.cpp================*/

#include <iostream>
#include <string>


#include "Planes.h"
#include "CrewMembers.h"
#include "Flights.h"

Planes PLANES;
CrewMembers CREWMEMBERS;
Flights FLIGHTS;

void load(){
    PLANES.loadData();
    CREWMEMBERS.loadData();
    //FLIGHTS.loadData();
} //loads all the data from a previously saved file.

void save(){
    PLANES.storeData();
    CREWMEMBERS.storeData();
    //FLIGHTS.storeData();
} //saves all the data to a file on the drive.

int main (){

    
    std::cout << "Homework 4 - Mean Green Airlines\nAUTHOR:        Andrew P. Sansom\nCOURSE:        CSCE 1040\nEMAIL:         andrewsansom@my.unt.edu\n";
    
    //main() presents a menu dialog to the user, which then allows them to choose other actions. Every time a user operation is completed, it autosaves the information. The main function also uses Flights’s updateAllFlightStatuses() periodically.
    std::string menuDialogOptions =
    "\n\nPlease enter the number of the desired option below.\n"
    "0. Save and Quit\n"
    "1. Add Employee \n"
    "2. Remove Employee \n"
    "3. Modify Employee \n"
    "4. Add Plane\n"
    "5. Remove Plane\n"
    "6. Modify Plane\n"
    "7. Add Flight\n"
    "8. Remove Flight\n"
    "9. Edit Flight\n"
    "10. Print Single Flight Plan\n"
    "11.Print All Flight Plans\n"
    "12.Print Single Employee Record\n"
    "13.Print All Employee Records\n"
    "14.Print Single Plane Record\n"
    "15.Print All Plane Records\n"
    "16.Cancel A Flight\n"
    "17.Delete All Canceled Flights\n"
    "18.Delete All Completed Flights\n"
    "19.Print Schedule of a Single Plane\n"
    "20.Print Schedule of an Employee\n"
    "21.Print List of Flights of a Single Status\n"
    "22.Save All Data\n"
    "23.Load All Data\n";
    
    int userOption;
    
    load();
    //get input and do the corresponding function.
    do {
        std::cout << menuDialogOptions << std::endl;
        std::cin >> userOption; std::cin.ignore();
        switch(userOption){
            case 0:
                std::cout <<"Saving and quitting...\n";
                save();
                return 0;
                break;
            case 1: CREWMEMBERS.addCrew(); break;
            case 2: CREWMEMBERS.deleteCrew(); break;
            case 3: CREWMEMBERS.editCrew(); break;
            case 4: PLANES.addPlane(); break;
            case 5: PLANES.deletePlane(); break;
            case 6: PLANES.editPlane(); break;
            case 7: FLIGHTS.addFlight(&PLANES, &CREWMEMBERS); break;
            case 8: FLIGHTS.deleteFlight(); break;
            case 9: FLIGHTS.editFlight(&PLANES, &CREWMEMBERS); break; 
            case 10: FLIGHTS.printIndividualFlightInfo(); break; 
            case 11: FLIGHTS.printListOfFlights(); break;
            case 12: CREWMEMBERS.printIndividualInfo(); break;
            case 13: CREWMEMBERS.printListOfPeople(); break;
            case 14: PLANES.printIndividualPlaneInfo(); break;
            case 15: PLANES.printListOfPlanes(); break;
            case 16: FLIGHTS.cancelFlight(); break;
            case 17: FLIGHTS.deleteAllCanceledFlights(); break;
            case 18: FLIGHTS.deleteAllCompletedFlights(); break;
            case 19: FLIGHTS.printPlaneSchedule(); break;
            case 20: FLIGHTS.printCrewMemberSchedule(); break;
            case 21: FLIGHTS.printListOfFlightsByStatus(); break;
            case 22: save(); break;
            case 23: load(); break;
            default:
                std::cout << "Unrecognized Input. Please enter the number of the option you would like.\n";
                break;
        }
        //save(); //Auto-save after every operation.
        FLIGHTS.updateAllFlightStatuses(); //Auto-update all flight statuses after every operation.
    } while (userOption != '0');
    return 0;
}
