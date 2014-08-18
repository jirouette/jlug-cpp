#ifndef SHAPE_HPP_INCLUDED
#define SHAPE_HPP_INCLUDED

/**
* \file shape.hpp
* \author jirouette
*/

#include "utils.hpp"
#include <SFML/Graphics.hpp>

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
      /**
      * \class Shape
      * \brief Abstract class which sets 3D context
      */
    class Shape
    {
        public:
            /**
            * \enum Transformation
            * \brief type of the transformation
            */
            enum Transformation {TRANSLATION, ROTATION, SCALING};

        protected:
            jlug::Point centerAxes; /*!< point of the center of the shape */
            jlug::Point color; /*!< color of the shape */
            GLuint texture; /*!< texture */

            jlug::Rectangle<double> textureSize; /*!< size of the texture source */
            jlug::Rectangle<double> textureZone; /*!< position of the wanted texture in the texture source */

            jlug::Point pixelTranslation; /*!< translates vertex into pixels */

            std::queue< std::pair<jlug::Shape::Transformation, jlug::Point> > transformations; /*!< transformations */


            virtual void applyTransformations(void);

        public:
            Shape(void);
            ~Shape(void);

            virtual void translate(const jlug::Point& tAxes);
            virtual void rotate(const jlug::Point& rAxes);
            virtual void scale(const jlug::Point& sAxes);

            virtual void translate(const double& x, const double& y, const double& z);
            virtual void rotate(const double& x, const double& y, const double& z);
            virtual void scale(const double& x, const double& y, const double& z);

            virtual void cancelTransformations(void);

            virtual void setPosition(const jlug::Point& pAxes);
            virtual void setPosition(const double& x, const double& y, const double& z);
            virtual jlug::Point getPosition(void);

            virtual void setColor(const jlug::Point& colors);
            virtual void setColor(const double& r, const double& g, const double& b);
            virtual jlug::Point getColor(void);

            virtual void setTexture(GLuint id);
            virtual GLuint getTexture(void);

            void setTextureSize(const jlug::Rectangle<double>& size);
            virtual void setTextureSize(const double& x, const double& y, const double& w, const double& h);
            virtual jlug::Rectangle<double> getTextureSize(void);

            virtual void setTextureZone(const jlug::Rectangle<double>& zone);
            virtual void setTextureZone(const double& x, const double& y, const double& w, const double& h);
            virtual jlug::Rectangle<double> getTextureZone(void);

            virtual void setPixelTranslation(double x, double y);
            virtual jlug::Point getPixelTranslation(void);



            virtual void draw(void) = 0; // Must be implemanted in daughter class



    };
}

#endif // SHAPE_HPP_INCLUDED
