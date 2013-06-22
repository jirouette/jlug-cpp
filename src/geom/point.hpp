#ifndef POINT_HPP_INCLUDED
#define POINT_HPP_INCLUDED

/**
* \file point.hpp
* \author jirouette
*/

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{

    /**
    * \class Point3D
    * \brief 3D-Point
    */

    template <typename T>
    class Point3D
    {
        public:
        T
        x, /*!< X-value */
        y, /*!< Y-value */
        z; /*!< Z-value */

        Point3D(T pX, T pY, T pZ);
        Point3D(T pX, T pY);
        Point3D(T pX);
        Point3D(void);
    };

    typedef Point3D<double> Point;

}

#include "point.cpp" // Template
#endif // POINT_HPP_INCLUDED
