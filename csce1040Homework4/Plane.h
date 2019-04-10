///*=============Plane.h================*/
/*
 DESCRIPTION:   
 AUTHOR:        Andrew P. Sansom
 VERSION:       1.0.0
 VERSION DATE:  3/19/19
 EMAIL:         andrewsansom@my.unt.edu
 COURSE:        CSCE 1040
 =============Plane.h================*/

#ifndef Plane_h
#define Plane_h

#include <string>

class Plane{
private:
    std::string make; //(string)
    std::string model;
    std::string tailNumber;// (string)
    int numberOfSeats; //(integer)
    int range; //How many miles can the plane fly in a single flight?
    int minimumNumberOfCrew; //(integer)
    
public:
    std::string getID(){return tailNumber;};
    std::string getMake(){return make;};
    std::string getModel(){return model;};
    int getNumberOfSeats(){return numberOfSeats;};
    int getRange(){return range;};
    int getMinimumNumberOfCrew(){return minimumNumberOfCrew;};
    
    void setID(std::string number){tailNumber=number;};
    void setMake(std::string _make){make=_make;};
    void setModel(std::string _model){model = _model;};
    void setNumberOfSeats(int _seats){numberOfSeats=_seats;};
    void setRange(int _range){range = _range;};
    void setMinimumNumberOfCrew(int _mincrew){minimumNumberOfCrew=_mincrew;};
    
    void printInfo();
};
#endif /* Plane_h */
