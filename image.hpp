#ifndef IMAGE_HPP_INCLUDED
#define IMAGE_HPP_INCLUDED

/**
* \file image.hpp
* \author JirialMovie
*/

#include <SFML/Graphics.hpp>
#include "utils.hpp"

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    class Window; // pre-declared to use it as a friend of Image.
    /**
    * \class Image
    * \brief Manipulates image
    *
    * This class reuses the library graphic used in the project (SFML, SDL, ...)
    */
    class Image
    {
        protected:
            sf::Sprite image; /*!< Graphic library's variable. Core of the image. */
            jlug::Rect blitRect; /*!< Rect which sets limits of blitting an Image. */


        public:
            Image(const sf::Image& img);
            Image(void);
            ~Image(void);
            Image& operator=(const sf::Image& img);
            unsigned int getWidth(void);
            unsigned int getHeight(void);
            jlug::Rect getSize(void);
            jlug::Rect getBlitRect(void);

            void setBlitRect(const jlug::Rect& rect);
            void setBlitRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
            void setAlpha(float alpha);

            friend class jlug::Window;
    };
}


#endif // IMAGE_HPP_INCLUDED
