///*=============Cabin.h================*/
/*
 DESCRIPTION:   
 AUTHOR:        Andrew P. Sansom
 VERSION:       1.0.0
 VERSION DATE:  4/15/19
 EMAIL:         andrewsansom@my.unt.edu
 COURSE:        CSCE 1040
 =============Cabin.h================*/

#ifndef Cabin_h
#define Cabin_h

#include "CrewMember.h"
#include <string>

enum CabinCrewType : int {FirstClass=0, BusinessClass, EconomyFront, EconomyRear, Lead};

class Cabin : public CrewMember {
private:
    CabinCrewType crewType;
    
    
public:
    Cabin();
    ~Cabin()=default;
    CabinCrewType getCrewType(){return crewType;};
    void setCrewType(CabinCrewType crewType_);
    void setCrewType();//Same as above, but prompts input from user;
    
    std::string getCrewTypeAsString(); //Retuns a string that says the crewType.
    
    void printInfo(); // Prints information to the console.
    int getType(){return CABINCREWTYPE;}; //returns with the integer code corresponding to the Cabin Crew Member type of employee. (Unrelated to the particular CabinCrew Type (i.e. position on the plane))
};

#endif /* Cabin_h */
