///*=============Plane.cpp================*/
/*
 DESCRIPTION:   
 AUTHOR:        Andrew P. Sansom
 VERSION:       1.0.0
 VERSION DATE:  3/19/19
 EMAIL:         andrewsansom@my.unt.edu
 COURSE:        CSCE 1040
 =============Plane.cpp================*/

#include "Plane.h"
#include <iostream>
#include <iomanip>

void Plane::printInfo(){
    std::cout << std::setw(10) << make << std::setw(6) << model << std::setw(6) << tailNumber << std::setw(6) << numberOfSeats << std::setw(6) << range << std::setw(6) << minimumNumberOfCrew << std::endl;
}
