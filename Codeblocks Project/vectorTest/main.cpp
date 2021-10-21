#include "../vector.h"
#include <iostream>

template <class T>
void printVec(Vector<T> &vec)
{
    for (int i=0; i<vec.getSize(); i++)
    {
        std::cout << vec[i] << std::endl;
    }
}

int main()
{
    //Vector<int> intVec;
    //intVec.add(1);
    //intVec.add(2);
    //intVec.add(3);
    //intVec.add("3");
    //printVec(intVec);

    //Vector<std::string> stringVec;
    //stringVec.add("hello");
    //stringVec.add("i am");
    //stringVec.add("good");
    //stringVec.add(3);
    //printVec(stringVec);

    //std::cout << stringVec[-1] << std::endl;
    //std::cout << stringVec[stringVec.getSize()] << std::endl;

    Vector<int> testVector(20);
    std::cout << "Capacity: " << testVector.getCapacity() << std::endl;
    std::cout << "Size: " << testVector.getSize() << std::endl;


    return 0;
}
