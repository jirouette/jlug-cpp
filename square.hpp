#ifndef SQUARE_HPP_INCLUDED
#define SQUARE_HPP_INCLUDED

#include "shape.hpp"

namespace jlug
{
    class Square : public Shape
    {
        public:
            Square(void);
            ~Square(void);
            void setVertex(bool rightSide, bool upSide, const jlug::Point& vertex);

            virtual void draw(void);

        protected:
            jlug::Point upperLeftCorner;
            jlug::Point upperRightCorner;
            jlug::Point downerLeftCorner;
            jlug::Point downerRightCorner;
    };
}



#endif // SQUARE_HPP_INCLUDED
