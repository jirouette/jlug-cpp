#ifndef SHAPE_HPP_INCLUDED
#define SHAPE_HPP_INCLUDED

#include "utils.hpp"
#include <SFML/Graphics.hpp>

namespace jlug
{
    class Shape
    {
        public:
            //static void cube(const jlug::Point& center, double size, const jlug::Rect& textureSize, const jlug::Rect& rawSize, GLuint* texture = NULL);
            //static void sphere(const jlug::Point& center, double ray, const jlug::Rect& textureSize, const jlug::Rect& rawSize, GLuint* texture = NULL);


            //static void triangle(const jlug::Point& center, double size, const jlug::Rect& textureSize, const jlug::Rect& rawSize, GLuint* texture = NULL);
            static void square(const jlug::Point& center, double size, const jlug::Rect& textureSize, const jlug::Rect& rawSize, GLuint* texture = NULL);


        private:
            Shape(void);
            ~Shape(void);



    };
}

#endif // SHAPE_HPP_INCLUDED