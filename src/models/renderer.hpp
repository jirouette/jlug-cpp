#ifndef RENDERER_HPP_INCLUDED
#define RENDERER_HPP_INCLUDED

/**
* \file renderer.hpp
* \author jirouette
*/

#include "models/shape.hpp"
#include "models/polygon.hpp"
#include <iostream>
#include <list>

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    /**
    * \class Renderer
    * \brief Display a complex 3D shape
    */
    class Renderer : public Shape
    {
        public:
            Renderer();
            virtual ~Renderer();

            virtual void translate(const double& x, const double& y, const double& z);
            virtual void rotate(const double& x, const double& y, const double& z);
            virtual void scale(const double& x, const double& y, const double& z);

            virtual void cancelTransformations();

            virtual void construct() = 0;
            virtual void draw();

        protected:
            std::list<jlug::Polygon> polygons;
    };
}



#endif // RENDERER_HPP_INCLUDED
