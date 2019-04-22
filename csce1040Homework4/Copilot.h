///*=============Copilot.h================*/
/*
 DESCRIPTION:   
 AUTHOR:        Andrew P. Sansom
 VERSION:       1.0.0
 VERSION DATE:  4/15/19
 EMAIL:         andrewsansom@my.unt.edu
 COURSE:        CSCE 1040
 =============Copilot.h================*/

#ifndef Copilot_hpp
#define Copilot_hpp

#include "CrewMember.h"
#include <string>

class Copilot : public CrewMember {
private:
    std::string copilotRating;
    float cumulativeFlightHours;
    
    
public:
    Copilot();
    ~Copilot()=default;
    
    std::string getCopilotRating(){return copilotRating;};
    float getCumulativeFlightHours(){return cumulativeFlightHours;};
    
    void setCoPilotRating(std::string copilotRating_);
    void setCumulativeFlightHours(float cumulativeFlightHours_){cumulativeFlightHours=cumulativeFlightHours_;};
    
    void addFlightHours(float additionalHours); //Adds additionalHours to the Pilot's cumulativeFlightHours
    
    void printInfo(); // Prints information to the console.
    int getType(){return COPILOTTYPE;};
};
#endif /* Copilot_h */
