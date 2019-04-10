///*=============Flights.cpp================*/
/*
 DESCRIPTION:   
 AUTHOR:        Andrew P. Sansom
 VERSION:       1.0.0
 VERSION DATE:  3/19/19
 EMAIL:         andrewsansom@my.unt.edu
 COURSE:        CSCE 1040
 =============Flights.cpp================*/

#include "Flights.h"
#include <iostream>
#include <iomanip>
#include <fstream>

time_t getDateTimeFromUser(){
    struct tm time_container;
    int tempTimeInt;
    bool validMonth=false;
    std::string tempTimeString;
    std::cout << "Year (4 digits): ";
    std::cin >> tempTimeInt;
    time_container.tm_year = tempTimeInt-1900;
    while (!validMonth){
        std::cout << "Month (3 letter abbreviation): ";
        std::cin >> tempTimeString;
        if (tempTimeString=="Jan" || tempTimeString=="jan"){
            time_container.tm_mon = 0;
            validMonth = true;
        } else if (tempTimeString=="Feb" || tempTimeString=="feb"){
            time_container.tm_mon = 1;
            validMonth = true;
        }else if (tempTimeString=="Mar" || tempTimeString=="mar"){
            time_container.tm_mon = 2;
            validMonth = true;
        }else if (tempTimeString=="Apr" || tempTimeString=="apr"){
            time_container.tm_mon = 3;
            validMonth = true;
        }else if (tempTimeString=="May" || tempTimeString=="may"){
            time_container.tm_mon = 4;
            validMonth = true;
        }else if (tempTimeString=="Jun" || tempTimeString=="jun"){
            time_container.tm_mon = 5;
            validMonth = true;
        }else if (tempTimeString=="Jul" || tempTimeString=="jul"){
            time_container.tm_mon = 6;
            validMonth = true;
        }else if (tempTimeString=="Aug" || tempTimeString=="aug"){
            time_container.tm_mon = 7;
            validMonth = true;
        }else if (tempTimeString=="Sep" || tempTimeString=="sep"){
            time_container.tm_mon = 8;
            validMonth = true;
        }else if (tempTimeString=="Oct" || tempTimeString=="oct"){
            time_container.tm_mon = 9;
            validMonth = true;
        }else if (tempTimeString=="Nov" || tempTimeString=="nov"){
            time_container.tm_mon = 10;
            validMonth = true;
        }else if (tempTimeString=="Dec" || tempTimeString=="dec"){
            time_container.tm_mon = 11;
            validMonth = true;
        } else {
            std::cout << "Invalid Month. Please enter three letter abbreviation.\n";
        }
    }
    std::cout << "Day of Month (1-31): ";
    std::cin >> tempTimeInt;
    time_container.tm_mday = tempTimeInt;
    std::cout << "Hour of Day (0-23hrs UTC): ";
    std::cin >> tempTimeInt;
    time_container.tm_hour = tempTimeInt;
    std::cout << "Minutes (0-59): ";
    std::cin >> tempTimeInt;
    time_container.tm_min = tempTimeInt;
    std::cout << "Seconds (0-59): ";
    std::cin >> tempTimeInt; std::cin.ignore();
    time_container.tm_sec = tempTimeInt;
    
    return mktime(&time_container);
}


void Flights::addFlight(Planes* PLANES, CrewMembers* CREWMEMBERS){
    
    Flight newFlight;
    int flightID;
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
    int status=-1; //(integer) 0 = canceled, 1 = Active, 2 = Completed, -1 is not set
    int tempID=-1;
    
    std::cout << "Creating New Flight:\n";
    //Enter FlightID
    std::cout << "Flight ID: ";
    std::cin >> flightID; std::cin.ignore();
    while (Flights::isIDtaken(flightID)){
        std::cout << "Flight ID already in use. Please choose another: ";
        std::cin >> flightID; std::cin.ignore();
    }
    newFlight.setID(flightID);
    //Enter Departure Airport
    std::cout << "Departure Airport Code: ";
    std::getline(std::cin, startPort);
    newFlight.setStartPort(startPort);
    //Enter Arrival Airport
    std::cout << "Arrival Airport Code: ";
    std::getline(std::cin, endPort);
    newFlight.setEndPort(endPort);
    //Enter Departure Time
    std::cout << "Entering Departure Date/Time (UTC).\n";
    startTime = getDateTimeFromUser();
    newFlight.setStartTime(startTime);
    //Enter Arrival Time
    std::cout << "Entering Arrival Date/Time (UTC).\n";
    endTime = getDateTimeFromUser();
    newFlight.setEndTime(endTime);
    
    //Enter PlaneID
    std::cout << "Plane ID: ";
    std::getline(std::cin, planeID);
    while (!PLANES->isIDtaken(planeID)){
        std::cout << "There is no plane with that ID found in the system. Please enter a valid plane ID.\n";
        std::cout << "Plane ID: ";
        std::getline(std::cin, planeID);
    }
    while(!checkIfPlaneIsAvailable(planeID, startTime,endTime)){
        std::cout << "That plane is unavailable at that time. Please choose another plane.\n";
        std::cout << "Plane ID: ";
        std::getline(std::cin, planeID);
    }
    newFlight.setPlaneID(planeID);
    
    
    //Enter numberOfPassengers
    std::cout << "Number Of Passengers: ";
    std::cin >> numberOfPassengers; std::cin.ignore();
    while (!PLANES->doesPlaneHaveEnoughSeats(planeID, numberOfPassengers)){
        std::cout << "There are not enough seats on this plane. Please enter a smaller number.\n";
        std::cin >> numberOfPassengers; std::cin.ignore();
    }
    newFlight.setNumberOfPassengers(numberOfPassengers);
    
    //Enter Status
    while (status>2 || status<0){
        std::cout << "What is the curent status of this flight?\n" <<
        "0. Canceled\n"
        "1. Active\n"
        "2. Completed\n";
        std::cout << "Number of status: ";
        std::cin >> status; std::cin.ignore();
        switch(status){
            case 0:
            case 1:
            case 2: break;
            default:
                std::cout << "Unrecognized Input. Please enter the number of the status.\n";
                break;
        }
    }
    newFlight.setStatus(status);
    //Set minimums
    if (endTime-startTime > 28800){
        numberOfPilots = 4; //Two pilots and two co pilots
        numberOfCrewCabin = 2*(PLANES->getMinCrewOfPlane(planeID)); //Twice the minimum required by the plane
    } else {
        numberOfPilots = 2;
        numberOfCrewCabin = PLANES->getMinCrewOfPlane(planeID); //The minimum required by the plane
    }
    newFlight.setNumberOfPilots(numberOfPilots);
    newFlight.setNumberOfCrewCabin(numberOfCrewCabin);

    std::cout << "Enter Pilot IDs, one at a time. After adding enough pilots, enter 0 to finish.\n";
    std::cout << "Minimum required number of pilots: " << numberOfPilots << std::endl;
    while (true){
        //Yes. This is ugly. But it's less ugly than using goto. And it requires too much time to restructure this in a more elegant way.
        //for additional reading, see xkcd.com/292/
        std::cout << "Pilot #" << pilotIDs.size()+1 << ": ";
        std::cin >> tempID; std::cin.ignore();
        if (tempID != 0){
            //Check to make sure we're adding an additional ID.
            if (isCrewMemberAvailable(tempID, startTime, endTime)){
                pilotIDs.push_back(tempID);
            } else {
                std::cout << "Employee is not available during that time.\n";
            }

        } else {
            //If the user doesn't want to add an additional pilot, we make sure they have added enough. If so, we let them go on. If not, we force them with our iron fist.
            if (pilotIDs.size()>=numberOfPilots){
                break;
            } else {
                std::cout << "Too few pilots. Please enter additional Pilot IDs.\n";
                tempID=-1; //Reset this so that we don't accidentally stop another loop too early.
            }
        }

    }
    newFlight.setPilotIDs(pilotIDs);
    tempID=-1; //Reset this so that we don't accidentally stop another loop too early.
    
    std::cout << "Enter Cabin Crew Member IDs, one at a time. Enter 0 to finish.\n";
    std::cout << "Minimum required number of Cabin Crew: " << numberOfCrewCabin << std::endl;
    
    while (true){
        //Yes. This is ugly. But it's less ugly than using goto. And it requires too much time to restructure this in a more elegant way.
        //for additional reading, see xkcd.com/292/
        std::cout << "Crew Member #" << cabinCrewIDs.size()+1 << ": ";
        std::cin >> tempID; std::cin.ignore();
        if (tempID != 0){
            //Check to make sure we're adding an additional ID.
            cabinCrewIDs.push_back(tempID);
        } else {
            //If the user doesn't want to add an additional pilot, we make sure they have added enough. If so, we let them go on. If not, we force them with our iron fist.
            if (cabinCrewIDs.size()>=numberOfCrewCabin){
                break;
            } else {
                std::cout << "Too few cabin crew. Please enter additional Pilot IDs.\n";
                tempID=-1; //Reset this so that we don't accidentally stop another loop too early.
            }
        }
        
    }
    newFlight.setCabinCrewIDs(cabinCrewIDs);
    
    FLIGHTS.push_back(newFlight);
} //presents a dialog to the user that asks for the potential flight’s startTime (date/time), endTime (date/time), startPort (string), endPort (string), numberOfPilots (integer), numberOfCrewCabin (integer), pilotIDs (List), cabinCrewIDs (List), numberOfPassengers (integer). Before accepting each value, it checks if the value is valid. I.E. If the if the flight is longer than 8 hours, it must have 2 pilots and 2 copilots and twice the minimum crew of the plane. It also checks, when recording pilotIDs and cabinCrewIDs, if the crewmember is of the correct occupation/type. It then creates a new flight, adds it to the collection, and sets all of its info to the recorded values. Also checks if the plane has a range sufficiently large to make the flight.


void Flights::editFlight(Planes* PLANES, CrewMembers* CREWMEMBERS){
    int id;
    std::cout <<"Editing Flight...\n" << "Flight ID: ";
    std::cin >> id; std::cin.ignore();
    
    Flight* flightWithID = findFlightByID(id);
    if (flightWithID){
        //PUT THE STUFF HERE
        int option=-1; //Set to -1, just to avoid interference.
        while (option != 0){
            std::cout << "Which property would you like to change?\n" <<
            "0. Change nothing. Exit.\n"
            "1. Departure airport code\n"
            "2. Arrival airport code\n"
            "3. Reset departure time\n"
            "4. Reset arrival time\n"
            "5. Airplane ID\n"
            "6. Number of passengers\n"
            "7. Status\n"
            "8. Reset Pilots\n"
            "9. Reset Cabin Crew\n";
            std::cout << "Number of property you wish to change: ";
            std::cin >> option; std::cin.ignore();
            switch(option){
                case 0:
                    break;
                case 1:{
                    //Enter Departure Airport
                    std::string startPort;
                    std::cout << "Departure Airport Code: ";
                    std::getline(std::cin, startPort);
                    flightWithID->setStartPort(startPort);
                    std::cout << "Departure airport changed.\n";
                    break;
                }
                case 2:{
                    //Enter Arrival Airport
                    std::string endPort;
                    std::cout << "Arrival Airport Code: ";
                    std::getline(std::cin, endPort);
                    flightWithID->setEndPort(endPort);
                    std::cout << "Arrival airport changed.\n";
                    break;
                }
                case 3:{
                    //Enter Departure Time
                    time_t startTime;
                    std::cout << "Entering Departure Date/Time (UTC).\n";
                    startTime = getDateTimeFromUser();
                    flightWithID->setStartTime(startTime);
                    std::cout << "Time changed.\n";
                    break;
                }
                case 4:{
                    //Enter Departure Time
                    time_t startTime;
                    std::cout << "Entering Arrival Date/Time (UTC).\n";
                    startTime = getDateTimeFromUser();
                    flightWithID->setEndTime(startTime);
                    std::cout << "Time changed.\n";
                    break;
                }
                case 5:{
                    //Enter PlaneID
                    std::string planeID;
                    std::cout << "Plane ID: ";
                    std::getline(std::cin, planeID);
                    while (!PLANES->isIDtaken(planeID)){
                        std::cout << "There is no plane with that ID found in the system. Please enter a valid plane ID.\n";
                        std::cout << "Plane ID: ";
                        std::getline(std::cin, planeID);
                    }
                    while(!checkIfPlaneIsAvailable(planeID, flightWithID->getStartTime(),flightWithID->getEndTime())){
                        std::cout << "That plane is unavailable at that time. Please choose another plane.\n";
                        std::cout << "Plane ID: ";
                        std::getline(std::cin, planeID);
                    }
                    flightWithID->setPlaneID(planeID);
                    break;
                }
                case 6:{
                    //Enter numberOfPassengers
                    int numberOfPassengers;
                    std::cout << "Number Of Passengers: ";
                    std::cin >> numberOfPassengers; std::cin.ignore();
                    while (!PLANES->doesPlaneHaveEnoughSeats(flightWithID->getPlaneID(), numberOfPassengers)){
                        std::cout << "There are not enough seats on this plane. Please enter a smaller number.\n";
                        std::cin >> numberOfPassengers; std::cin.ignore();
                    }
                    flightWithID->setNumberOfPassengers(numberOfPassengers);
                    break;
                }
                case 7:{
                    //Enter Status
                    int status=-1;
                    while (status>2 || status<0){
                        std::cout << "What is the curent status of this flight?\n" <<
                        "0. Canceled\n"
                        "1. Active\n"
                        "2. Completed\n";
                        std::cout << "Number of status: ";
                        std::cin >> status; std::cin.ignore();
                        switch(status){
                            case 0:
                            case 1:
                            case 2: break;
                            default:
                                std::cout << "Unrecognized Input. Please enter the number of the status.\n";
                                break;
                        }
                    }
                    flightWithID->setStatus(status);
                    break;
                }
                case 8:{
                    int tempID = -1;
                    int numberOfPilots;
                    int numberOfCrewCabin;
                    time_t endTime = flightWithID->getEndTime();
                    time_t startTime = flightWithID->getStartTime();
                    std::string planeID = flightWithID->getPlaneID();
                    std::vector<int> pilotIDs;
                    //Set minimums
                    if (endTime-startTime > 28800){
                        numberOfPilots = 4; //Two pilots and two co pilots
                        numberOfCrewCabin = 2*(PLANES->getMinCrewOfPlane(planeID)); //Twice the minimum required by the plane
                    } else {
                        numberOfPilots = 2;
                        numberOfCrewCabin = PLANES->getMinCrewOfPlane(planeID); //The minimum required by the plane
                    }
                    flightWithID->setNumberOfPilots(numberOfPilots);
                    flightWithID->setNumberOfCrewCabin(numberOfCrewCabin);
                    
                    std::cout << "Enter Pilot IDs, one at a time. After adding enough pilots, enter 0 to finish.\n";
                    std::cout << "Minimum required number of pilots: " << numberOfPilots << std::endl;
                    while (true){
                        //Yes. This is ugly. But it's less ugly than using goto. And it requires too much time to restructure this in a more elegant way.
                        //for additional reading, see xkcd.com/292/
                        std::cout << "Pilot #" << pilotIDs.size()+1 << ": ";
                        std::cin >> tempID; std::cin.ignore();
                        if (tempID != 0){
                            //Check to make sure we're adding an additional ID.
                            if (isCrewMemberAvailable(tempID, startTime, endTime)){
                                pilotIDs.push_back(tempID);
                            } else {
                                std::cout << "Employee is not available during that time.\n";
                            }
                            
                        } else {
                            //If the user doesn't want to add an additional pilot, we make sure they have added enough. If so, we let them go on. If not, we force them with our iron fist.
                            if (pilotIDs.size()>=numberOfPilots){
                                break;
                            } else {
                                std::cout << "Too few pilots. Please enter additional Pilot IDs.\n";
                                tempID=-1; //Reset this so that we don't accidentally stop another loop too early.
                            }
                        }
                        
                    }
                    flightWithID->setPilotIDs(pilotIDs);
                    break;
                }
                case 9:{
                    int tempID = -1;
                    int numberOfPilots;
                    int numberOfCrewCabin;
                    time_t endTime = flightWithID->getEndTime();
                    time_t startTime = flightWithID->getStartTime();
                    std::string planeID = flightWithID->getPlaneID();
                    std::vector<int> cabinCrewIDs;
                    //Set minimums
                    if (endTime-startTime > 28800){
                        numberOfPilots = 4; //Two pilots and two co pilots
                        numberOfCrewCabin = 2*(PLANES->getMinCrewOfPlane(planeID)); //Twice the minimum required by the plane
                    } else {
                        numberOfPilots = 2;
                        numberOfCrewCabin = PLANES->getMinCrewOfPlane(planeID); //The minimum required by the plane
                    }
                    flightWithID->setNumberOfPilots(numberOfPilots);
                    flightWithID->setNumberOfCrewCabin(numberOfCrewCabin);
                    
                    std::cout << "Enter Cabin Crew Member IDs, one at a time. Enter 0 to finish.\n";
                    std::cout << "Minimum required number of Cabin Crew: " << numberOfCrewCabin << std::endl;
                    while (true){
                        //Yes. This is ugly. But it's less ugly than using goto. And it requires too much time to restructure this in a more elegant way.
                        //for additional reading, see xkcd.com/292/
                        std::cout << "Crew Member #" << cabinCrewIDs.size()+1 << ": ";
                        std::cin >> tempID; std::cin.ignore();
                        if (tempID != 0){
                            //Check to make sure we're adding an additional ID.
                            if (isCrewMemberAvailable(tempID, startTime, endTime)){
                                cabinCrewIDs.push_back(tempID);
                            } else {
                                std::cout << "Employee is not available during that time.\n";
                            }
                            
                        } else {
                            //If the user doesn't want to add an additional pilot, we make sure they have added enough. If so, we let them go on. If not, we force them with our iron fist.
                            if (cabinCrewIDs.size()>=numberOfCrewCabin){
                                break;
                            } else {
                                std::cout << "Too few crew members. Please enter additional Crew Member IDs.\n";
                                tempID=-1; //Reset this so that we don't accidentally stop another loop too early.
                            }
                        }
                        
                    }
                    flightWithID->setCabinCrewIDs(cabinCrewIDs);
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



void Flights::deleteFlight(){
    int id;
    bool removedFlight = false;
    std::vector<Flight>::iterator ptr;
    
    std::cout <<"Deleting Flight...\n" << "Flight ID: ";
    std::cin >> id; std::cin.ignore();
    
    for (ptr = FLIGHTS.begin(); ptr < FLIGHTS.end(); ptr++){
        if (ptr->getID()==id){
            FLIGHTS.erase(ptr);
            std::cout << "Removed Flight.\n";
            removedFlight = true;
        }
    }
    if (!removedFlight) std::cout << "Flight with that ID was not found... Aborting...\n";
} //presents a dialog to the user that asks for the ID of the flight that they would like to delete. It then asks for confirmation before deleting the flight object and updating the collection.
void Flights::cancelFlight(){
    int id;
    bool removedFlight = false;
    std::vector<Flight>::iterator ptr;
    
    std::cout <<"Cancelling Flight...\n" << "Flight ID: ";
    std::cin >> id; std::cin.ignore();
    
    for (ptr = FLIGHTS.begin(); ptr < FLIGHTS.end(); ptr++){
        if (ptr->getID()==id){
            ptr->setStatus(0);
            std::cout << "Cancelled Flight.\n";
            removedFlight = true;
        }
    }
    if (!removedFlight) std::cout << "Flight with that ID was not found... Aborting...\n";
} //prompts the user for the flightID of the flight the user wishes to cancel. It then searches for that flight, and changes its status to “Canceled”
Flight* Flights::findFlightByID(int flightID){
    std::vector<Flight>::iterator ptr;
    for (ptr = FLIGHTS.begin(); ptr < FLIGHTS.end(); ptr++){
        if (ptr->getID()==flightID){
            return &(*ptr);
        }
    }
    std::cout << "Flight with given ID not found in system.";
    return nullptr;

} //searches for every flight with the givenID.
std::vector<Flight*> Flights::findFlightsByPlane(std::string planeID){
    std::vector<Flight*> vec;
    std::vector<Flight>::iterator ptr;
    //Loop over every flight. If the flight uses the given plane, then add a pointer to that flight in the vector we will return.
    for (ptr = FLIGHTS.begin(); ptr < FLIGHTS.end(); ptr++){
        if(ptr->getPlaneID()==planeID) {
            vec.push_back(&(*ptr));
        }
    }
    //if (vec.size()==0) std::cout << "No other flights found with that plane.\n";
    return vec;
} //searches for every flight with the plane with planeID.
std::vector<Flight*> Flights::findFlightsByCrew(int crewID){
    std::vector<Flight*> vec;
    std::vector<Flight>::iterator ptr;
    //Loop over every flight. If the crewmember is onboard, then add a pointer to that flight to the vector we will return.
    for (ptr = FLIGHTS.begin(); ptr < FLIGHTS.end(); ptr++){
        if(ptr->isCrewOnFlight(crewID)) {
            vec.push_back(&(*ptr));
        }
    }
    //if (vec.size()==0) std::cout << "No other flights with that crew member found.\n";
    return vec;
} //searches for every flight with a crewmember with crewID.
std::vector<Flight*> Flights::findFlightsByStatus(int status){
    std::vector<Flight*> vec;
    
    std::vector<Flight>::iterator ptr;
    for (ptr = FLIGHTS.begin(); ptr < FLIGHTS.end(); ptr++){
        if (ptr->getStatus()==status){
            vec.push_back(&(*ptr));
        }
    }
    if (vec.size()==0) std::cout << "No such flights found.\n";
    return vec;
} //searches for every flight with status.
void Flights::printIndividualFlightInfo(int flightID){
    Flight* flightWithID = findFlightByID(flightID);
    if (flightWithID){
        flightWithID->printInfo();
    } else {
        std::cout << "Flight with that ID is not found. Aborting print.\n";
    }
} //prints to the console the information of the flight with flightID.
void Flights::printIndividualFlightInfo(){
    int flightID;
    std::cout << "Please enter the ID of the flight who's record you would like to see.\n";
    std::cin >> flightID;
    printIndividualFlightInfo(flightID);
} //Same as above, but asks the user for the ID first.
void Flights::printListOfFlights(){
    std::cout << "Printing list of all flights.\n";
    std::vector<Flight>::iterator ptr;
    for (ptr = FLIGHTS.begin(); ptr < FLIGHTS.end(); ptr++){
        ptr->printInfo();
    }
} //runs printIndividualFlightInfo(flightID) for every flight in the collection.
void Flights::printPlaneSchedule(std::string planeID){
    std::cout << "Printing all flights with the requested plane...\n";
    std::vector<Flight*> listOfFlightWithStatus = findFlightsByPlane(planeID);
    std::vector<Flight*>::iterator ptr;
    for (ptr = listOfFlightWithStatus.begin(); ptr < listOfFlightWithStatus.end(); ptr++){
        (*ptr)->printInfo();
    }
} //searches for every flight that uses the plane with planeID, then prints that flight’s info to the console.
void Flights::printPlaneSchedule(){
    std::string planeID;
    std::cout << "Plane ID whose scheduled flights you would like to see: ";
    std::getline(std::cin, planeID);
    printPlaneSchedule(planeID);
}
void Flights::printCrewMemberSchedule(int personID){
    std::cout << "Printing all flights with the requested crew member...\n";
    std::vector<Flight*> listOfFlightWithStatus = findFlightsByCrew(personID);
    std::vector<Flight*>::iterator ptr;
    for (ptr = listOfFlightWithStatus.begin(); ptr < listOfFlightWithStatus.end(); ptr++){
        (*ptr)->printInfo();
    }
} //searches for every flight that uses the crew member with personID, then prints that flight’s info to the console.
void Flights::printCrewMemberSchedule(){
    int id;
    std::cout << "ID of employee whose scheduled flights you would like to see: ";
    std::cin >> id; std::cin.ignore();
    printCrewMemberSchedule(id);
}
void Flights::printListOfFlightsByStatus(int status){
    std::cout << "Printing all flights with the requested status...\n";
    std::vector<Flight*> listOfFlightWithStatus = findFlightsByStatus(status);
    std::vector<Flight*>::iterator ptr;
    for (ptr = listOfFlightWithStatus.begin(); ptr < listOfFlightWithStatus.end(); ptr++){
        (*ptr)->printInfo();
    }
} //searches for every flight with status, and then runs printIndividualFlightInfo() with that flight’s ID.
void Flights::printListOfFlightsByStatus(){
    int status=-1;
    //Enter Status
    while (status>2 || status<0){
        std::cout << "Which flight status would you like to see?\n" <<
        "0. Canceled\n"
        "1. Active\n"
        "2. Completed\n";
        std::cout << "Number of status: ";
        std::cin >> status; std::cin.ignore();
        switch(status){
            case 0:
            case 1:
            case 2: break;
            default:
                std::cout << "Unrecognized Input. Please enter the number of the status.\n";
                break;
        }
    }
    printListOfFlightsByStatus(status);
}
void Flights::deleteAllCanceledFlights(){
    std::vector<Flight>::iterator ptr;
    for (ptr = FLIGHTS.begin(); ptr < FLIGHTS.end(); ptr++){
        if (ptr->getStatus()==0){
            FLIGHTS.erase(ptr);
        }
    }
} //searches for every flight that is marked as “Cancelled”, then deletes that flight with the deleteFlight() method.
void Flights::deleteAllCompletedFlights(){
    std::vector<Flight>::iterator ptr;
    for (ptr = FLIGHTS.begin(); ptr < FLIGHTS.end(); ptr++){
        if (ptr->getStatus()==2){
            FLIGHTS.erase(ptr);
        }
    }
} //searches for every flight that is marked as “Completed”, then deletes that flight with the deleteFlight() method.
void Flights::updateAllFlightStatuses(){
    std::vector<Flight>::iterator ptr;
    for (ptr = FLIGHTS.begin(); ptr < FLIGHTS.end(); ptr++){
        if (ptr->getStatus() && ptr->getEndTime() < time(0)){
            ptr->setStatus(2);
        }
    }
} //loops over each Flight in the collection. If a flight is not canceled, it checks if the date/time is after the end time. If so, it will update the status from “Active” to “Completed”.
bool Flights::isIDtaken(int flightID){
    std::vector<Flight>::iterator ptr;
    for (ptr = FLIGHTS.begin(); ptr < FLIGHTS.end(); ptr++){
        if (ptr->getID() == flightID){
            return true;
        }
    }
    return false;
} //checks all of the flights to see if there is already a flight with the specified id.
void Flights::updateCrewForAllFlightsWithPlane(std::string planeID){
    
} //searches for every flight with planeID, and then checks if the crewAssigned is atleast that plane’s minimumNumberOfSeats (if a short flight) or twice the minimum (if a long flight). If there is a deficit, it asks the user to supply more crew Members until the deficit is fixed. NOTE: This would normally only be called automatically when the user modifies a plane’s minimumNumberOfSeats.

bool Flights::isCrewMemberAvailable(int crewID, time_t startTime,time_t endTime){
    std::vector<Flight*> listOfFlightsWithCrewMember = findFlightsByCrew(crewID);
    
    std::vector<Flight*>::iterator ptr;
    for (ptr = listOfFlightsWithCrewMember.begin(); ptr < listOfFlightsWithCrewMember.end(); ptr++){
        
        //Check if there is overlap in the time intervals.
        //Double pointers? Sure. Why not.
        if ((startTime <= (*ptr)->getEndTime()) && ((*ptr)->getStartTime() <= endTime) ){
            return false;
        }
    }
    return true;
}

bool Flights::checkIfPlaneIsAvailable(std::string planeID, time_t startTime, time_t endTime){
    std::vector<Flight*> listOfFlightsWithPlane = findFlightsByPlane(planeID);
    
    std::vector<Flight*>::iterator ptr;
    for (ptr = listOfFlightsWithPlane.begin(); ptr < listOfFlightsWithPlane.end(); ptr++){
        //Check if there is overlap in the time intervals.
        //Double pointers? Sure. Why not.
        if ((startTime <= (*ptr)->getEndTime()) && ((*ptr)->getStartTime() <= endTime) ){
            return false;
        }
    }
    return true;
} //searches for every flight with the given planeID and sees if time is between its start time and end time return true if available, false if not.





void Flights::loadData(){
    FLIGHTS.clear();
    std::ifstream fin;
    int numberOfFlights=0;
    fin.open("flights.dat");
    if (fin.is_open()){
        fin >> numberOfFlights; fin.ignore();
        //Iterate over the planes in the document.
        for (int i =0; i < numberOfFlights; i++){
            Flight newFlight;
            int flightID;
            std::string planeID;
            int numberOfPilots; //(integer) [flights over 8 hours need 2 pilots and 2 copilots]
            int numberOfCrewCabin; //(integer) [8 hour flights need twice the minimum]
            int numberOfAssignedPilots;
            int numberOfAssignedCrewCabin;
            std::vector<int> pilotIDs; //vector of all the pilots aboard a flight.
            std::vector<int> cabinCrewIDs; //vector of all the cabincrew aboard a flight.
            time_t startTime; // (date/time)
            time_t endTime; //(date/time)
            std::string startPort; //string representing the airport that the plane departs from.
            std::string endPort; //string representing the airport that the plane arrives at.
            int numberOfPassengers; //(integer)
            int status; //(integer) 0 = canceled, 1 = Active, 2 = Completed
            
            fin >> flightID; fin.ignore();
            std::getline(fin, planeID);
            fin >> numberOfPilots; fin >> numberOfAssignedPilots;
            fin >> numberOfCrewCabin; fin >> numberOfAssignedCrewCabin;
            for (int i = 0; i < numberOfAssignedPilots; i++){
                int tempID;
                fin >> tempID;
                pilotIDs.push_back(tempID);
            }
            fin.ignore();
            for (int i = 0; i < numberOfAssignedCrewCabin; i++){
                int tempID;
                fin >> tempID;
                cabinCrewIDs.push_back(tempID);
            }
            fin.ignore();
            fin >> startTime;
            fin >> endTime; fin.ignore();
            std::getline(fin, startPort);
            std::getline(fin, endPort);
            fin >> numberOfPassengers;
            fin >> status;
            fin.ignore();
            
            newFlight.setID(flightID);
            newFlight.setPlaneID(planeID);
            newFlight.setNumberOfPilots(numberOfPilots);
            newFlight.setNumberOfCrewCabin(numberOfCrewCabin);
            newFlight.setPilotIDs(pilotIDs);
            newFlight.setCabinCrewIDs(cabinCrewIDs);
            newFlight.setStartTime(startTime);
            newFlight.setEndTime(endTime);
            newFlight.setStartPort(startPort);
            newFlight.setEndPort(endPort);
            newFlight.setNumberOfPassengers(numberOfPassengers);
            newFlight.setStatus(status);
            
            FLIGHTS.push_back(newFlight);
        }
        fin.close();
    }
} //Loads data from disk.
void Flights::storeData(){

    std::ofstream fout;
    fout.open("flights.dat");
    
    //Iterate over each flight, and add the data
    std::vector<Flight>::iterator ptr;
    fout << FLIGHTS.size() << std::endl; //The number of planes. This will just make life easier as we load data.
    for (ptr = FLIGHTS.begin(); ptr < FLIGHTS.end(); ptr++){
        fout << ptr->getID() << std::endl;
        fout << ptr->getPlaneID() << std::endl;
        fout << ptr->getNumberOfPilots() << " " << ptr->getPilotIDs().size() << std::endl;
        fout << ptr->getNumberOfCrewCabin() << " " << ptr->getCabinCrewIDs().size() << std::endl;
        std::vector<int>::iterator idPtr;
        //Iterate over the Pilots, printing each id to the file followed by a space.
        for (idPtr = (ptr->getPilotIDs()).begin(); idPtr < (ptr->getPilotIDs()).end();idPtr++){
            fout << *idPtr << " ";
        }
        fout<<std::endl;
        //Iterate over the CabinCrew, printing each id to the file followed by a space.
        for (idPtr = (ptr->getCabinCrewIDs()).begin(); idPtr < (ptr->getCabinCrewIDs()).end();idPtr++){
            fout << *idPtr << " ";
        }
        fout<<std::endl;
        fout << ptr->getStartTime()<< std::endl;
        fout << ptr->getEndTime() <<std::endl;
        fout << ptr->getStartPort() << std::endl;
        fout << ptr->getEndPort() << std::endl;
        fout << ptr->getNumberOfPassengers() << std::endl;
        fout << ptr->getStatus() << std::endl;
    }
    fout.close();

} //Saves data from disk.
