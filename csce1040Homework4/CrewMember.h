///*=============CrewMember.h================*/
/*
 DESCRIPTION:   
 AUTHOR:        Andrew P. Sansom
 VERSION:       1.0.0
 VERSION DATE:  3/19/19
 EMAIL:         andrewsansom@my.unt.edu
 COURSE:        CSCE 1040
 =============CrewMember.h================*/

#ifndef CrewMember_h
#define CrewMember_h

#include <string>

class CrewMember{
private:
    int ID;
    std::string careerType; // (string, such as Pilot or Cabin)
    std::string name;
public:
    int getID(){return ID;};
    std::string getCareerType(){return careerType;};
    std::string getName(){return name;};
    
    void setID(int _crewid){ID = _crewid;};
    void setCareerType(std::string type){careerType=type;};
    void setName(std::string _name){name = _name;};
    
    void printInfo();
};

#endif /* CrewMember_h */
