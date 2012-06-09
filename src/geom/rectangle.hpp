#ifndef RECTANGLE_HPP_INCLUDED
#define RECTANGLE_HPP_INCLUDED

/**
* \file rectangle.hpp
* \author JirialMovie
*/

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{

    /**
    * \class Rectangle
    * \brief Rectangle with upper-left corner and downer-right corner defined.
    * May be used as a vector.
    */
    template <typename T>
    class Rectangle
    {
        public:
        T
        x, /*!< X-value */
        y, /*!< Y-value */
        w, /*!< Width of the rectangle. */
        h;  /*!< Height of the rectangle. */

        Rectangle(T pX, T pY, T pW, T pH);
        Rectangle(T pX, T pY, T pW);
        Rectangle(T pX, T pY);
        Rectangle(T pX);
        Rectangle(void);
    };

    typedef Rectangle<int> Rect;

}

#include "rectangle.cpp" // Template
#endif // RECTANGLE_HPP_INCLUDED
