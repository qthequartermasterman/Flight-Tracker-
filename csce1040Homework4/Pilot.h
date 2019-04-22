///*=============Pilot.h================*/
/*
 DESCRIPTION:   
 AUTHOR:        Andrew P. Sansom
 VERSION:       1.0.0
 VERSION DATE:  4/10/19
 EMAIL:         andrewsansom@my.unt.edu
 COURSE:        CSCE 1040
 =============Pilot.h================*/

#ifndef Pilot_h
#define Pilot_h

#include "CrewMember.h"
#include <string>

class Pilot : public CrewMember {
private:
    std::string pilotRating;
    float cumulativeFlightHours;
    
    
public:
    Pilot();
    ~Pilot()=default;
    Pilot(std::string name_,
          int ID_,
          int status_, //available = 1, on leave = 0 , sick = -1
          std::string pilotRating_,
          float cumulativeFlightHours_);
    
    std::string getPilotRating(){return pilotRating;};
    float getCumulativeFlightHours(){return cumulativeFlightHours;};
    
    void setPilotRating(std::string pilotRating_);
    void setCumulativeFlightHours(float cumulativeFlightHours_){cumulativeFlightHours=cumulativeFlightHours_;};
    
    void addFlightHours(float additionalHours); //Adds additionalHours to the Pilot's cumulativeFlightHours
    
    void printInfo(); // Prints information to the console.
    
    int getType(){return PILOTTYPE;};
};
#endif /* Pilot_h */
