///*=============Flight.h================*/
/*
 DESCRIPTION:   
 AUTHOR:        Andrew P. Sansom
 VERSION:       1.0.0
 VERSION DATE:  3/19/19
 EMAIL:         andrewsansom@my.unt.edu
 COURSE:        CSCE 1040
 =============Flight.h================*/

#ifndef Flight_h
#define Flight_h

#include <stdio.h>
#include <string>
#include <vector>
#include <ctime>

//class CrewMember;
#include "CrewMember.h"

class Flight{
private:
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
    int status; //(integer) 0 = canceled, 1 = Active, 2 = Completed
public:
    int getID(){return flightID;};
    std::string getPlaneID(){return planeID;};
    int getNumberOfPilots(){return numberOfPilots;}; //(integer) [flights over 8 hours need 2 pilots and 2 copilots]
    int getNumberOfCrewCabin(){return numberOfCrewCabin;}; //(integer) [8 hour flights need twice the minimum]
    std::vector<int> getPilotIDs(){return pilotIDs;}; //vector of all the pilots aboard a flight.
    std::vector<int> getCabinCrewIDs(){return cabinCrewIDs;}; //vector of all the cabincrew aboard a flight.
    time_t getStartTime(){return startTime;}; // (date/time)
    time_t getEndTime(){return endTime;}; //(date/time)
    std::string getStartPort(){return startPort;}; //string representing the airport that the plane departs from.
    std::string getEndPort(){return endPort;}; //string representing the airport that the plane arrives at.
    int getNumberOfPassengers(){return numberOfPassengers;}; //(integer)
    int getStatus(){return status;}; //(integer) 0 = canceled, 1 = Active, 2 = Completed
    
    void setID(int ID){flightID=ID;};
    void setPlaneID(std::string _planeID){planeID = _planeID;};
    void setNumberOfPilots(int num){numberOfPilots=num;}; //(integer) [flights over 8 hours need 2 pilots and 2 copilots]
    void setNumberOfCrewCabin(int num){numberOfCrewCabin=num;}; //(integer) [8 hour flights need twice the minimum]
    void setPilotIDs(std::vector<int> ids){pilotIDs=ids;}; //vector of all the pilots aboard a flight.
    void setCabinCrewIDs(std::vector<int> ids){cabinCrewIDs=ids;}; //vector of all the cabincrew aboard a flight.
    void setStartTime(time_t time){startTime=time;}; // (date/time)
    void setEndTime(time_t time){endTime=time;}; //(date/time)
    void setStartPort(std::string port){startPort = port;}; //string representing the airport that the plane departs from.
    void setEndPort(std::string port){endPort = port;}; //string representing the airport that the plane arrives at.
    void setNumberOfPassengers(int num){numberOfPassengers = num;}; //(integer)
    void setStatus(int stat){status = stat;}; //(integer) 0 = canceled, 1 = Active, 2 = Completed
    bool isCrewOnFlight(int crewID);

    void printInfo();
};

#endif /* Flight_h */
