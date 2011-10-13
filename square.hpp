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

            virtual void draw(void);
    };
}



#endif // SQUARE_HPP_INCLUDED