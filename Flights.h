///*=============Flights.h================*/
/*
 DESCRIPTION:   
 AUTHOR:        Andrew P. Sansom
 VERSION:       1.0.0
 VERSION DATE:  3/19/19
 EMAIL:         andrewsansom@my.unt.edu
 COURSE:        CSCE 1040
 =============Flights.h================*/

#ifndef Flights_h
#define Flights_h

#include <stdio.h>
#include <vector>
#include <string>
#include <ctime>

//class Flight;
#include "Flight.h"
#include "CrewMembers.h"
#include "Planes.h"
class Planes;

class Flights{
private:
    std::vector<Flight> FLIGHTS;
public:
    void addFlight(Planes* PLANES, CrewMembers* CREWMEMBERS); //presents a dialog to the user that asks for the potential flight’s startTime (date/time), endTime (date/time), startPort (string), endPort (string), numberOfPilots (integer), numberOfCrewCabin (integer), pilotIDs (List), cabinCrewIDs (List), numberOfPassengers (integer). Before accepting each value, it checks if the value is valid. I.E. If the if the flight is longer than 8 hours, it must have 2 pilots and 2 copilots and twice the minimum crew of the plane. It also checks, when recording pilotIDs and cabinCrewIDs, if the crewmember is of the correct occupation/type. It then creates a new flight, adds it to the collection, and sets all of its info to the recorded values. Also checks if the plane has a range sufficiently large to make the flight.
    void editFlight(Planes* PLANES, CrewMembers* CREWMEMBERS); //presents a dialog to the user asking which properties they would like to change. It then prompts for the new value, checking against its restrictions. If the user tries to change a value that will cause another property to have an illegal value, it warns the user. If the user decides to continue, it then asks for updated values of the other properties.
    void deleteFlight(); //presents a dialog to the user that asks for the ID of the flight that they would like to delete. It then asks for confirmation before deleting the flight object and updating the collection.
    void cancelFlight(); //prompts the user for the flightID of the flight the user wishes to cancel. It then searches for that flight, and changes its status to “Canceled”
    Flight* findFlightByID(int flightID); //searches for every flight with the givenID.
    std::vector<Flight*> findFlightsByPlane(std::string planeID); //searches for every flight with the plane with planeID.
    std::vector<Flight*> findFlightsByCrew(int crewID); //searches for every flight with a crewmember with crewID.
    std::vector<Flight*> findFlightsByStatus(int status); //searches for every flight with status.
    void printIndividualFlightInfo(int flightID); //prints to the console the information of the flight with flightID.
    void printIndividualFlightInfo(); //Same as above, but asks the user for the ID first.
    void printListOfFlights(); //runs printIndividualFlightInfo(flightID) for every flight in the collection.
    
    void printPlaneSchedule(std::string planeID); //searches for every flight that uses the plane with planeID, then prints that flight’s info to the console.
    void printPlaneSchedule(); //same as above, but first prompts input from user.
    void printCrewMemberSchedule(int personID); //searches for every flight that uses the crew member with personID, then prints that flight’s info to the console.
    void printCrewMemberSchedule();//same as above, but first prompts input from user.
    void printListOfFlightsByStatus(int status); //searches for every flight with status, and then runs printIndividualFlightInfo() with that flight’s ID.
    void printListOfFlightsByStatus(); //same as above, but first prompts input from user.
    void deleteAllCanceledFlights(); //searches for every flight that is marked as “Cancelled”, then deletes that flight with the deleteFlight() method.
    void deleteAllCompletedFlights(); //searches for every flight that is marked as “Completed”, then deletes that flight with the deleteFlight() method.
    void updateAllFlightStatuses(); //loops over each Flight in the collection. If a flight is not canceled, it checks if the date/time is after the end time. If so, it will update the status from “Active” to “Completed”.
    bool isIDtaken(int flightID); //checks all of the flights to see if there is already a flight with the specified id.
    void updateCrewForAllFlightsWithPlane(std::string planeID); //searches for every flight with planeID, and then checks if the crewAssigned is atleast that plane’s minimumNumberOfSeats (if a short flight) or twice the minimum (if a long flight). If there is a deficit, it asks the user to supply more crew Members until the deficit is fixed. NOTE: This would normally only be called automatically when the user modifies a plane’s minimumNumberOfSeats.
    bool isCrewMemberAvailable(int crewID, time_t startTime,time_t endTime);
    bool checkIfPlaneIsAvailable(std::string planeID, time_t startTime,time_t endTime); //searches for every flight with the given planeID and sees if time is between its start time and end time return true if available, false if not.
    
    void loadData(); //Loads data from disk.
    void storeData(); //Saves data from disk.
};

#endif /* Flights_h */
