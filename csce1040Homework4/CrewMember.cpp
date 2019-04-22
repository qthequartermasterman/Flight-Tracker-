///*=============CrewMember.cpp================*/
/*
 DESCRIPTION:   
 AUTHOR:        Andrew P. Sansom
 VERSION:       1.0.0
 VERSION DATE:  3/19/19
 EMAIL:         andrewsansom@my.unt.edu
 COURSE:        CSCE 1040
 =============CrewMember.cpp================*/

#include "CrewMember.h"
#include <iostream>
#include <iomanip>

void CrewMember::printInfo(){
    std::cout << std::left << std::setw(8) << ID << std::setw(20) << name <<std::endl;
    /*std::cout << "\tName: " << name << std::endl;
    std::cout << "\tCareer Type: " << careerType << std::endl;
    std::cout << "\tID Number: " << ID << std::endl;*/
}
