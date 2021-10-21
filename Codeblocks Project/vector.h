#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <assert.h>
#include <vector>

template <class T>
class Vector
{
    public:
        Vector();
        Vector(int cap);
        ~Vector();

        /**
         * @brief add an index to array
         *
         * @param data - data to be added to array
         * @return void
         */
        void add(T data);
        /**
         * @brief clear array
         *
         * @return void
         */
        void clear();
        /**
         * @brief get capacity
         *
         * @return int
         */
        int getCapacity();
        /**
         * @brief get size
         *
         * @return int
         */
        int getSize();
        /**
         * @brief overloads subscript operators
         *
         * @param i - index of array
         * @return T
         */
        T operator[] (int i);
    private:
        /**
         * @brief increase size
         *
         * @return void
         */
        void increaseSize();
        std::vector<T> m_vector;
};

template <class T>
Vector<T>::~Vector()
{
    m_vector.clear();
}

template <class T>
Vector<T>::Vector()
{
}

template <class T>
Vector<T>::Vector(int cap)
{
    m_vector.reserve(cap);
}

template <class T>
int Vector<T>::getCapacity()
{
    return m_vector.capacity();
}

template <class T>
int Vector<T>::getSize()
{
    return m_vector.size();
}

template <class T>
void Vector<T>::add(T data)
{
    m_vector.push_back(data);
}

template <class T>
void Vector<T>::clear()
{
    m_vector.clear();
}

//overload subscript operators
template <class T>
T Vector<T>::operator [] (int i)
{
    assert(i >= 0 && (unsigned)i <= (m_vector.size()-1)); //make sure index is within bounds
    return m_vector[i]; //return array index
}

#endif // VECTOR_H
