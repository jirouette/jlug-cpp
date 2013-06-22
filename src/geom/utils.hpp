#ifndef UTILS_GEOM_HPP_INCLUDED
#define UTILS_GEOM_HPP_INCLUDED

/**
* \file utils.hpp
* \author jirouette
*/


/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{

    namespace Axis
    {
        enum AxisName
        {
            X,
            Y,
            Z
        };
    }

    /**
    * \namespace jlug::Move
    * \brief Contains directions.
    */
    namespace Move
    {
        /**
        * \enum Direction
        * \brief Character's directions.
        */
        enum Direction
        {
            UP,
            DOWN,
            LEFT,
            RIGHT,
            NONE,

            Count
        };



    }
}

#endif // UTILS_GEOM_HPP_INCLUDED
