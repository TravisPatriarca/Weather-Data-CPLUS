#include "date.h"
#include <string>

//default constructor
date::date()
: day(0), month(0), year(0){}

date::date(int d, int m, int y)
: day(d), month(m), year(y) {}

//get days
int date::getDay() const
{
    return day;
}

//set day
void date::setDay(int dd)
{
    day = dd;
}

//get month
int date::getMonth() const
{
    return month;
}

//set month
void date::setMonth(int mm)
{
    month = mm;
}

//get year
int date::getYear() const
{
    return year;
}

//set year
void date::setYear(int yyyy)
{
    year = yyyy;
}

bool date::operator<(const date &r) const
{
    int rYear = r.getYear();
    int rMonth = r.getMonth();
    int rDay = r.getDay();

    if (year < rYear)
        return true;
    else
        if (year > rYear)
            return false;
        else
            if (month < rMonth)
                return true;
            else
                if (month > rMonth)
                    return false;
                else
                    if (day < rDay)
                        return true;
                    else
                        return false;
}

bool date::operator>(const date& r) const
{
    int rYear = r.getYear();
    int rMonth = r.getMonth();
    int rDay = r.getDay();

    if (year > rYear)
        return true;
    else
        if (year < rYear)
            return false;
        else
            if (month > rMonth)
                return true;
            else
                if (month < rMonth)
                    return false;
                else
                    if (day > rDay)
                        return true;
                    else
                        return false;
}

bool date::operator == (const date& r) const
{
    int rYear = r.getYear();
    int rMonth = r.getMonth();
    int rDay = r.getDay();
    if (year == rYear && month == rMonth && day == rDay)
        return true;
    else
        return false;
}
