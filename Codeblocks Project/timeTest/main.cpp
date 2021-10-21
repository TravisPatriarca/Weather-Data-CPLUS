#include "../time.h"
#include <iostream>

int main()
{
    time t;
    //t.setMinutes("2");
    //t.setHours("40");
    //std::cout << t.getMinutes() << "\n";
    //std::cout << t.getHours() << "\n";

    //compiler error
    //t.setMinutes();
    //t.setHours();
    //std::cout << t.getMinutes() << "\n";
    //std::cout << t.getHours() << "\n";

    //no matching function
    //t.setMinutes(2);
    //t.setHours(3);
    //std::cout << t.getMinutes() << "\n";
    //std::cout << t.getHours() << "\n";

    //no matching function
    //t.setMinutes(" ");
    //t.setHours(" ");
    //std::cout << t.getMinutes() << "\n";
    //std::cout << t.getHours() << "\n";

    t.setMinutes("\n");
    t.setHours("\n");
    std::cout << t.getMinutes() << "\n";
    //std::cout << t.getHours() << "\n";
    return 0;
}
