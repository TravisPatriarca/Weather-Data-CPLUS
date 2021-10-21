#include "../date.h"
#include <iostream>

int main()
{
    date da;
    //da.setDay("03");
    //da.setMonth("05");
    //da.setYear("2020");
    //std::cout << da.getDay() << "\n";
    //std::cout << da.getMonth() << "\n";
    //std::cout << da.getYear() << "\n";
    //std::cout << "\n";

    //compiler error
    /*da.setDay();
    //da.setMonth();
    da.setYear();
    std::cout << da.getDay() << "\n";
    std::cout << da.getMonth() << "\n";
    std::cout << da.getYear() << "\n";
    std::cout << "\n";*/

    //no matching function
    //da.setDay(1);
    //da.setMonth(2);
    //da.setYear(3);
    //std::cout << da.getDay() << "\n";
    //std::cout << da.getMonth() << "\n";
    //std::cout << da.getYear() << "\n";
    //std::cout << "\n";

    //no matching function
    /*da.setDay(" ");
    da.setMonth(" ");
    da.setYear(" ");
    std::cout << da.getDay() << "\n";
    //std::cout << da.getMonth() << "\n";
    //std::cout << da.getYear() << "\n";
   // std::cout << "\n"; */

    //no matching function
    da.setDay("\n");
    //da.setMonth("\n");
    //da.setYear("\n");
    std::cout << da.getDay() << "\n";
    //std::cout << da.getMonth() << "\n";
    //std::cout << da.getYear() << "\n";
    //std::cout << "\n";

    return 0;
}
