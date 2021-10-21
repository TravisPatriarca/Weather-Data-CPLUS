#include "time.h"
#include "date.h"
#include "bst.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <limits>
#include <sstream>
#include <map>
#include <vector>

//WindLog struct
typedef struct {
    date d;
    time t;
    float speed;
    float solRad;
    float temp;
} WindLogType;

//months names Jan-Feb array
const std::string MONTH_NAMES[12] = {"January", "Feburary", "March", "April", "May", "June", "July", "August", "September", "October", "Novemeber", "December"};
//output file name
const std::string OUT_FILE = "WindTempSolar.csv";
const std::string INDEX_FILE = "data/met_index.txt";

//Calculate Total function
template <class T>
T calcSum(std::vector<T> &arr)
{
    T total = 0;
    for (int i=0; i<arr.size(); i++)
    {
        total += arr[i];
    }

    return total;
}

//calculate average function
template <class T>
T calcAvg(std::vector<T> &arr)
{
    T total, avg;

    total = calcSum(arr);

    avg = total/static_cast<T>(arr.size());
    return avg;
}

//population standard deviation function
template <class T>
T calcStdev(std::vector<T> &arr)
{
    T stdev;
    T sum = 0;

    T avg = calcAvg(arr);

    for (int i=0; i<arr.size(); i++)
    {
        sum += (arr[i] - avg) * (arr[i] - avg); //stdev formula
    }

    stdev = sqrt(sum/static_cast<T>(arr.size()));

    return stdev;
}

//population standard deviation function
template <class T>
T findMax(std::multimap<T, WindLogType> &map)
{
    double max = -1;
    for (auto elem : map)
    {
        if (elem.first > max) //compare month & days
        {
            max = elem.first;
        }
    }

    return max;
}

void printMenu()
{
    std::cout <<
    "1. Calculate average wind speed and sample deviation for specified month and year.\n" <<
    "2. Calculate average ambient air temperature and sample deviation for each month of a specified year.\n" <<
    "3. Calculate total solar radiation in kWh/m2 for each month of a specified year.\n" <<
    "4. Calculate average wind speed (km/h), average ambient air temperature and total solar radion in kWh/m2." <<
    "for each month of a specified year in file (WindTempSolar.csv).\n" <<
    "5. Print highest solar radiation for inputted date (d/m/yyyy).\n" <<
    "6. Exit program.\n\n";
}

int menuSelect()
{
    int input;
    std::cin.clear();
    std::cin >> input;
    std::cin.ignore(256, '\n'); //clear cin buffer
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cout << "Invalid Entry, try again...\n";
        std::cin.ignore(256, '\n');
        std::cin >> input;
        std::cin.ignore(256, '\n'); //clear cin buffer
    }
    return input;
}

int getMonth()
{
    int month;
    do
    {
        std::cin.clear();
        std::cout << "Enter a month 1-12\n";
        std::cin >> month;
        std::cin.ignore(256, '\n'); //clear cin buffer
        while(std::cin.fail())
        {
            std::cin.clear();
            std::cout << "Invalid Entry, try again...\n";
            std::cin.ignore(256, '\n');
            std::cin >> month;
            std::cin.ignore(256, '\n'); //clear cin buffer
        }
    }while(month < 1 || month > 12); //check month between 1-12 (inclusive)
    return month;
}

int getYear()
{
    int year;
    std::cin.clear();
    std::cout << "Enter a year e.g 2015\n";
    std::cin >> year;
    std::cin.ignore(256, '\n'); //clear cin buffer
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cout << "Invalid Entry, try again...\n";
        std::cin.ignore(256, '\n');
        std::cin >> year;
        std::cin.ignore(256, '\n'); //clear cin buffer
    }
    return year;
}

std::string getDate()
{
    std::cin.clear();
    std::string dateInfo;
    std::cout << "Enter a date (d/m/yyyy): \n";
    std::cin >> dateInfo;
    std::cin.ignore(256, '\n'); //clear cin buffer

    return dateInfo;
}

//get sub vector from speed
std::vector<double> getSubvecspeed(std::map<std::string, WindLogType> &windlog, int month, int year)
{
    std::vector<double> vec;

    for (auto elem : windlog)
    {
        if (elem.second.d.getMonth() == month && elem.second.d.getYear() == year) //compare month & days
        {
            vec.push_back(elem.second.speed);
        }
    }

    return vec;
}

//get sub vector from temp
std::vector<double> getSubvectemp(std::map<std::string, WindLogType> &windlog, int month, int year)
{
    std::vector<double> vec;

    for (auto elem : windlog)
    {
        if (elem.second.d.getMonth() == month && elem.second.d.getYear() == year) //compare month & days
        {
            vec.push_back(elem.second.temp);
        }
    }

    return vec;
}

//get sub vector from solar radiation
std::vector<double> getSubvecsr(std::map<std::string, WindLogType> &windlog, int month, int year)
{
    std::vector<double> vec;

    for (auto elem : windlog)
    {
        if (elem.second.d.getMonth() == month && elem.second.d.getYear() == year) //compare month & days
        {
            vec.push_back(elem.second.solRad);
        }
    }

    return vec;
}

std::multimap<double, WindLogType> getSubmapsr(std::map<std::string, WindLogType> &windlog, int day, int month, int year)
{
    std::multimap<double, WindLogType> mmap;

    for (auto elem : windlog)
    {
        if (elem.second.d.getDay() == day && elem.second.d.getMonth() == month && elem.second.d.getYear() == year) //compare month & days
        {
            mmap.insert(std::pair<double, WindLogType>(elem.second.solRad, elem.second));

            //std::cout << elem.second.solRad << "\n";
        }
    }
    return mmap;
}

float convertToKWH(float SR)
{
    SR = (SR * (1.0/6.0)) / 1000.0; //KWH conversion formula
    return SR;
}

float convertToWm(float SR)
{
    SR = (SR / (1.0/6.0)) * 1000.0; //KWH conversion formula
    return SR;
}

//menu option 1
void doOption1(std::map<std::string, WindLogType> &windlog, Bst<std::string> &dataTree)
{
    int month, year;
    month = getMonth();
    year = getYear();

    if (dataTree.search((month<10 ? "0" : "") + std::to_string(month)+std::to_string(year)))
    {
        std::vector<double> subVec = getSubvecspeed(windlog, month, year); //get sub vector speed
        std::cout << MONTH_NAMES[month-1] << " " << year << ":\n";
        std::cout << "Average speed: " << calcAvg(subVec) << " km/h\n";
        std::cout << "Sample stdev: " << calcStdev(subVec) << "\n";
    }
    else
       std::cout << MONTH_NAMES[month-1] << ": NO DATA \n";
}

//menu option 2
void doOption2(std::map<std::string, WindLogType> &windlog, Bst<std::string> &dataTree)
{
    int year;
    year = getYear();
    std::cout << year << "\n";
    for (int i=0; i<12; i++)
    {
        if (dataTree.search(((i+1)<10 ? "0" : "") + std::to_string(i+1) + std::to_string(year)))
        {
            std::vector<double> subVec = getSubvectemp(windlog, i+1, year); //get sub vector temp
            std::cout << MONTH_NAMES[i] << ": average " << calcAvg(subVec) << " degrees C, stdev: " << calcStdev(subVec) << "\n";
        }
        else
            std::cout << MONTH_NAMES[i] << ": NO DATA \n";
    }
}

//menu option 3
void doOption3(std::map<std::string, WindLogType> &windlog, Bst<std::string> &dataTree)
{
    int year;
    year = getYear();
    std::cout << year << "\n";
    for (int i=0; i<12; i++)
    {
        if (dataTree.search(((i+1)<10 ? "0" : "") + std::to_string(i+1) + std::to_string(year)))
        {
            std::vector<double> subVec = getSubvecsr(windlog, i+1, year); //get sub vector solar radiation
            std::cout << MONTH_NAMES[i] << ": " << calcSum(subVec) << "kWh/m2\n";
        }
        else
            std::cout << MONTH_NAMES[i] << ": NO DATA \n";
    }
}

//menu option 4
void doOption4(std::map<std::string, WindLogType> &windlog, Bst<std::string> &dataTree)
{
    int year; //change to month, year
    std::ofstream outFile(OUT_FILE);
    outFile << std::fixed;
    outFile.precision(1);
    bool dataFlag = false;
    do
    {
        year = getYear();
        outFile << year << "\n";

        for (int i=0; i<12; i++)
        {
            if (dataTree.search(((i+1)<10 ? "0" : "") + std::to_string(i+1) + std::to_string(year)))
            {
                std::vector<double> subVecSpeed = getSubvecspeed(windlog, i+1, year); //get sub vector speed
                std::vector<double> subVecTemp = getSubvectemp(windlog, i+1, year); //get sub vector temp
                std::vector<double> subVecSR = getSubvecsr(windlog, i+1, year); //get sub vector solar radiation

                dataFlag = true;
                outFile << MONTH_NAMES[i] << "," << calcAvg(subVecSpeed) << "(" << calcStdev(subVecSpeed) << ")," << calcAvg(subVecTemp) << "(" << calcStdev(subVecTemp) << ")," << calcSum(subVecSR) << "\n";
            }
            else
                std::cerr << MONTH_NAMES[i] << ": NO DATA \n";
        }

        if (!dataFlag) //check if file has been read into
            std::cout << "-----====No DATA for that year try again...====-----\n";
        else
            std::cout << "Logged in file (" << OUT_FILE << ")\n";
    }
    while (!dataFlag);

    outFile.close();
}

void doOption5(std::map<std::string, WindLogType> &windlog)
{
    std::string d = getDate();

    std::string day, month, year;
    std::stringstream dateInfoStream(d); //convert string to act as stream
    getline(dateInfoStream, day, '/');
    getline(dateInfoStream, month, '/');
    getline(dateInfoStream, year, '\n');

    try
    {
        std::multimap<double, WindLogType> subMap = getSubmapsr(windlog, stoi(day), stoi(month), stoi(year));
        if (subMap.size() > 0)
        {
            double maxSr = findMax(subMap);

            std::cout << "Date: " << d << "\n";
            std::cout << "High solar radiation for the day: " << convertToWm(maxSr) << "W/m2\n\nTime:\n";

            typedef std::multimap<double, WindLogType>::iterator MapIterator;

            if (maxSr != -1)
            {
                std::pair<MapIterator, MapIterator> pair = subMap.equal_range(maxSr); //get lower and upper iterators for value maxSr
                for (MapIterator it = pair.first; it!=pair.second; it++)
                {
                    std::cout << (it->second.t.getMinutes()) << ":" << (it->second.t.getHours()) << '\n';
                }
            }
            else
                std::cerr << "\nError No MaxSR...\n";
        }
        else
        {
            std::cout << "\nNo Data...\n";
            doOption5(windlog);
        }
    }
    catch (...)
    {
        std::cerr << "Invalid date try again...." << std::endl;
        doOption5(windlog);
    }
}

int main()
{
    //Vector<WindLogType> windlog;
    std::map<std::string, WindLogType> windlog;
    Bst<std::string> dataTree;

    std::string DP, Dta, Dts, EV, QFE, QFF, QNH, RF, RH, S, SR, ST1, ST2, ST3, ST4, Sx, T;

    std::string day, month, year;
    std::string hours, minutes;
    std::string line, key;

    std::string path = "data/";
    std::string inFile;
    std::ifstream indexFile(INDEX_FILE);

    int size = 0;

    while (!indexFile.eof())
    {
        getline(indexFile, inFile);

        if (!inFile.empty())
        {
            std::ifstream inData(path + inFile);


            inData.ignore(256, '\n');
            WindLogType tempLog;

            while (!inData.eof())
            {
                getline(inData, line, '\n');
                std::stringstream lineData(line);
                getline(lineData, day, '/');
                getline(lineData, month, '/');
                getline(lineData, year, ' ');
                getline(lineData, minutes, ':');
                getline(lineData, hours, ',');

                for (int i=0; i<9; i++)
                    lineData.ignore(256, ',');

                getline(lineData, S, ',');
                getline(lineData, SR, ',');

                for (int i=0; i<5; i++)
                    lineData.ignore(256, ',');

                getline(lineData, T);

                if (!day.empty() && !month.empty() && !year.empty() && !minutes.empty() && !hours.empty())
                {
                    try
                    {
                        tempLog.d.setDay(stoi(day));
                        tempLog.d.setMonth(stoi(month));
                        tempLog.d.setYear(stoi(year));

                        tempLog.t.setHours(hours);
                        tempLog.t.setMinutes(minutes);

                        tempLog.speed = stof(S);

                        float SRF;
                        if (stoi(SR) <= 100)
                            SRF = 0;
                        else
                            SRF = convertToKWH(stof(SR)); //convert solar radiation

                        tempLog.solRad = SRF;
                        tempLog.temp = stof(T);
                        key = year + month + day + " " + minutes + hours;
                        windlog.insert(std::pair<std::string, WindLogType>(key, tempLog));
                        dataTree.insert(month+year);
                    }
                    catch (...)
                    {
                        std::cerr << "Invalid Data Input - " << day << "/" << month << "/" << year << " " << minutes << ":" << hours << "\n";;
                    }
                }
            }

            std::cerr << inFile << " " << windlog.size()-size << " entries\n";

            size = windlog.size();
        }
    }

    int select = -1;
    std::cout << std::fixed << "Total entries: " << windlog.size() << std::endl << std::endl;
    std::cout.precision(1); //set 1 decimal place
    do
    {
        printMenu();
        select = menuSelect();

        switch (select)
        {
            case 1:
                doOption1(windlog, dataTree);
                break;
            case 2:
                doOption2(windlog, dataTree);
                break;
            case 3:
                doOption3(windlog, dataTree);
                break;
            case 4:
                doOption4(windlog, dataTree);
                break;
            case 5:
                doOption5(windlog);
                break;
            case 6:
                return 0;
            default:
                std::cerr << "Not a valid Option";
        }

        std::cout << "\n";
    }while (true);
    return 0;
}
