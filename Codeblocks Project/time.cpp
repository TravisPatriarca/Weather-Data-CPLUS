#include "time.h"
#include <iostream>

//default constructor
time::time()
: hours("00"), minutes("00") {}

//parameter constructor
time::time(std::string hh, std::string mm)
{
    hours = hh;
    minutes = mm;
}

//get hours
std::string time::getHours() const
{
    return hours;
}

//get minutes
std::string time::getMinutes() const
{
    return minutes;
}

//sets hours
void time::setHours(std::string hh)
{
    hours = hh;
}

//sets minutes
void time::setMinutes(std::string mm)
{
    minutes = mm;
}
