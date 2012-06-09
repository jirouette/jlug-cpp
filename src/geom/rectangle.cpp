#include "rectangle.hpp"
#ifndef RECTANGLE_CPP_INCLUDED
#define RECTANGLE_CPP_INCLUDED
/**
* \file rectangle.cpp
* \author JirialMovie
*/

/**
* \brief Default constructor
*/
template<typename T>
jlug::Rectangle<T>::Rectangle(void)
{
    x = y = w = h = static_cast<T>(0);
}

/**
* \brief Constructor
* \param pX : X-coordinates
* \param pY : Y-coordinates
* \param pW : width
* \param pH : height
*/
template<typename T>
jlug::Rectangle<T>::Rectangle(T pX, T pY, T pW, T pH)
{
    x = pX;
    y = pY;
    w = pW;
    h = pH;
}

/**
* \brief Constructor
* \param pX : X-coordinates
* \param pY : Y-coordinates
* \param pW : width
*/
template<typename T>
jlug::Rectangle<T>::Rectangle(T pX, T pY, T pW)
{
    Rectangle<T>::Rectangle(pX, pY, pW, static_cast<T>(0));
}


/**
* \brief Constructor
* \param pX : X-coordinates
* \param pY : Y-coordinates
*/
template<typename T>
jlug::Rectangle<T>::Rectangle(T pX, T pY)
{
    Rectangle<T>::Rectangle(pX, pY, static_cast<T>(0));
}

/**
* \brief Constructor
* \param pX : X-coordinates
*/
template<typename T>
jlug::Rectangle<T>::Rectangle(T pX)
{
    Rectangle<T>::Rectangle(pX, static_cast<T>(0));
}

#endif // RECTANGLE_CPP_INCLUDED
