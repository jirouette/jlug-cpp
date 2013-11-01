#ifndef POLYGON_HPP_INCLUDED
#define POLYGON_HPP_INCLUDED

/**
* \file polygon.hpp
* \author jirouette
*/

#include "models/shape.hpp"
#include <iostream>
/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    /**
    * \class Polygon
    * \brief Display a shape in a 3D context
    */
    class Polygon : public Shape
    {
        public:
            Polygon();
            Polygon(GLenum m, size_t n);
            ~Polygon();
            void setVertex(size_t index, const jlug::Point& vertex);
            void setVertex(size_t index, const jlug::Point& vertex, const jlug::Point& texturePoint);

            void setTexturePoint(size_t index, const jlug::Point& texturePoint);

            void addVertex(const jlug::Point& vertex);
            void addVertex(const jlug::Point& vertex, const jlug::Point& texturePoint);

            void addTexturePoint(const jlug::Point& texturePoint);

            virtual void draw();

        protected:
            std::vector<jlug::Point> vertices; /*!< vertices of the shape */
            std::vector<jlug::Point> texturePoints;
            GLenum mode;
            size_t faces;
    };
}



#endif // POLYGON_HPP_INCLUDED
