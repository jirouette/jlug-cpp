#include "utils.hpp"
#ifndef UTILS_CPP_INCLUDED
#define UTILS_CPP_INCLUDED
/**
* \file utils.cpp
* \author JirialMovie
*/

template<typename T>
jlug::Rectangle<T>::Rectangle(void)
{
    x = y = w = h = static_cast<T>(0);
}

template<typename T>
jlug::Rectangle<T>::Rectangle(T pX, T pY, T pW, T pH)
{
    x = pX;
    y = pY;
    w = pW;
    h = pH;
}

template<typename T>
jlug::Rectangle<T>::Rectangle(T pX, T pY, T pW)
{
    Rectangle<T>::Rectangle(pX, pY, pW, static_cast<T>(0));
}

template<typename T>
jlug::Rectangle<T>::Rectangle(T pX, T pY)
{
    Rectangle<T>::Rectangle(pX, pY, static_cast<T>(0));
}

template<typename T>
jlug::Rectangle<T>::Rectangle(T pX)
{
    Rectangle<T>::Rectangle(pX, static_cast<T>(0));
}

template<typename T>
jlug::Point3D<T>::Point3D(void)
{
    x = y = z = static_cast<T>(0);
}

template<typename T>
jlug::Point3D<T>::Point3D(T pX, T pY, T pZ)
{
    x = pX;
    y = pY;
    z = pZ;
}

template<typename T>
jlug::Point3D<T>::Point3D(T pX, T pY)
{
    Point3D<T>::Point3D(pX, pY, static_cast<T>(0));
}

template<typename T>
jlug::Point3D<T>::Point3D(T pX)
{
    Point3D<T>::Point3D(pX, static_cast<T>(0));
}

#endif // UTILS_CPP_INCLUDED