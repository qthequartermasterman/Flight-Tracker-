///*=============Planes.h================*/
/*
 DESCRIPTION:   
 AUTHOR:        Andrew P. Sansom
 VERSION:       1.0.0
 VERSION DATE:  3/19/19
 EMAIL:         andrewsansom@my.unt.edu
 COURSE:        CSCE 1040
 =============Planes.h================*/

#ifndef Planes_h
#define Planes_h

#include <stdio.h>
#include <vector>
#include <string>

//class Plane;
#include "Plane.h"


class Planes{
private:
    std::vector<Plane> PLANES;
public:
    void addPlane(); /*presents a dialog to the user that asks for the potential plane’s data:
        -Make (string)
        -Model (integer)
        -Tail Number (string)
        -Number of Seats (integer)
        -Range (integer)
        -minimumNumberOfCrew (integer)
        -Before accepting each value, it checks if the value is valid. E.G. Seat Number, Range, and minimumNumberOfCrew must all be nonnegative. It then creates a new plane, adds it to the collection, and sets all of its info to the recorded values.*/
    
    void editPlane(); //presents a dialog to the user asking which properties they would like to change. It then prompts for the new value, checking against its restrictions. If the user tries to change a value that will cause another property to have an illegal value, it warns the user. If the user decides to continue, it then asks for updated values of the other properties.
        //NOTE: This might mean that some already booked flights might have too few CrewMembers. If the minimumNumberOfCrew increases, then run “updateCrewForAllFlightsWithPlane(planeID)”, which will prompt the user to update the crews on flights with this plane.
    void deletePlane(); //presents a dialog to the user that asks for the ID of the plane that they would like to delete. It then asks for confirmation before deleting the plane object and updating the collection.
    Plane* findPlaneByID(std::string planeID); //returns all planes with the given planeID.
    void printListOfPlanes(); //runs printIndividualPlaneInfo(planeID) for every plane in the collection.
    void printIndividualPlaneInfo(); //displays an individual plane’s information in an organized table to the console.
    void printIndividualPlaneInfo(std::string planeID); //displays an individual plane’s information in an organized table to the console.
    bool doesPlaneHaveEnoughSeats(std::string planeID, int necessaryNumberOfSeats); //searches for the plane in its collection with planeID, and checks if it has greater than or equal to the necessaryNumberOfSeats, returning the result.
    bool isIDtaken(std::string planeID); //checks all of the planes to see if there is already a plane with the specified id.
    int getMinCrewOfPlane(std::string planeID); //Returns the minimum number of crew required for a certain plane.
    void loadData(); //Loads data from disk.
    void storeData(); //Saves data from disk.
};
#endif /* Planes_h */
