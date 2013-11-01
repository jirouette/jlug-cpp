#include "point.hpp"
#ifndef POINT_CPP_INCLUDED
#define POINT_CPP_INCLUDED
/**
* \file point.cpp
* \author jirouette
*/


/**
* \brief Default constructor
*/
template<typename T>
jlug::Point3D<T>::Point3D(void)
{
    x = y = z = static_cast<T>(0);
}

/**
* \brief Constructor
* \param pX : X-coordinates
* \param pY : Y-coordinates
* \param pZ : Z-coordinates
*/
template<typename T>
jlug::Point3D<T>::Point3D(T pX, T pY, T pZ)
{
    x = pX;
    y = pY;
    z = pZ;
}

/**
* \brief Constructor
* \param pX : X-coordinates
* \param pY : Y-coordinates
*/
template<typename T>
jlug::Point3D<T>::Point3D(T pX, T pY)
{
    Point3D<T>::Point3D(pX, pY, static_cast<T>(0));
}

/**
* \brief Constructor
* \param pX : X-coordinates
*/
template<typename T>
jlug::Point3D<T>::Point3D(T pX)
{
    Point3D<T>::Point3D(pX, static_cast<T>(0));
}

#endif // POINT_CPP_INCLUDED
