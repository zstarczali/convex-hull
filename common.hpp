#ifndef COMMON_HPP
#define COMMON_HPP

#define _USE_MATH_DEFINES
#define EPS 0.0000001
#include <iostream>
#include <cmath> // std::abs
#include <vector>

template <class T>
void SafeDelete(T *&pVal)
{
    delete pVal;
    pVal = NULL;
}

template <class T>
void SafeDeleteArray(T *&pVal)
{
    delete[] pVal;
    pVal = NULL;
}

#endif