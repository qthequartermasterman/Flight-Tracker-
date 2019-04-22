///*=============CrewMembers.h================*/
/*
 DESCRIPTION:   
 AUTHOR:        Andrew P. Sansom
 VERSION:       1.0.0
 VERSION DATE:  3/19/19
 EMAIL:         andrewsansom@my.unt.edu
 COURSE:        CSCE 1040
 =============CrewMembers.h================*/

#ifndef CrewMembers_h
#define CrewMembers_h

#include <stdio.h>
#include <string>
#include <vector>

//class CrewMember; //Forward declare CrewMember so we can use it.
#include "CrewMember.h"


class CrewMembers{
private:
    std::vector<CrewMember*> CREWMEMBERS;
public:
    
    ~CrewMembers();
    
    void addCrew(); //presents a dialog to the user that asks for the potential CrewMember’s ID (integer) and careerType (string, such as Pilot or Cabin).
    void editCrew(); //presents a dialog to the user asking which properties they would like to change. It then prompts for the new value, checking against its restrictions (for example, if an ID is already taken). If the user tries to change a value that will cause another property to have an illegal value, it warns the user. If the user decides to continue, it then asks for updated values of the other properties.
    void deleteCrew(); //presents a dialog to the user that asks for the ID of the CrewMember that they would like to delete. It then asks for confirmation before deleting the CrewMember object and updating the collection.
    CrewMember findCrewMembersByName(std::string name); //searches for every Crew Member with the given name
    CrewMember* findCrewMemberByID(int crewID); //searches for every CrewMember with the given crewID.
    std::vector<CrewMember> findCrewMembersByType(std::string type); //searches for every CrewMember with the given type.
    void printListOfPeople(); //iterates over every CrewMember in the collection and runs printIndividualInfo(crewID) with their respective crewID.
    void printIndividualInfo(int crewID); //displays an individual CrewMember’s information in an organized table to the console.
    void printIndividualInfo(); //Same as above, but first asks the user for the ID of the individual.
    std::string checkCareerType(int crewID); //returns the careerType of the crewmember with crewID in the collection.
    bool isIDtaken(int crewID); //checks all of the CrewMembers to see if there is already a CrewMember with the specified id.
    void loadData(); //Loads data from disk.
    void storeData(); //Saves data from disk.
    
    bool isCrewMemberOfType(int crewMemberID, int crewMemberType); //returns true if the crewmember with the given ID is of the correct type.
};


#endif /* CrewMembers_h */
