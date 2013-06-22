#ifndef SQUARE_HPP_INCLUDED
#define SQUARE_HPP_INCLUDED

/**
* \file square.hpp
* \author jirouette
*/

#include "models/shape.hpp"
/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    /**
    * \class Square
    * \brief Display a Rect-shape in a 3D context
    */
    class Square : public Shape
    {
        public:
            Square(void);
            ~Square(void);
            void setVertex(bool rightSide, bool upSide, const jlug::Point& vertex);

            virtual void draw(void);

        protected:
            jlug::Point upperLeftCorner; /*!< vertex of the upper left corner of the rect-shape */
            jlug::Point upperRightCorner; /*!< vertex of the upper right corner of the rect-shape */
            jlug::Point downerLeftCorner; /*!< vertex of the downer left corner of the rect-shape */
            jlug::Point downerRightCorner; /*!< vertex of the downer right corner of the rect-shape */
    };
}



#endif // SQUARE_HPP_INCLUDED
