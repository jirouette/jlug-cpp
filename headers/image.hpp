#ifndef IMAGE_HPP_INCLUDED
#define IMAGE_HPP_INCLUDED

/**
* \file image.hpp
* \author JirialMovie
*/

#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include <exception>
#include <stdexcept>
#include <iostream>

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
            GLuint texture; /*!< OpenGL's texture ID */
            sf::Sprite image; /*!< Graphic library's variable. Core of the image. */
            sf::Image raw; /*!< SFML raw */
            jlug::Rect blitRect; /*!< Rect which sets limits of blitting an Image. */
            unsigned int width; /*!< width we will use, but not always the real width */
            unsigned int height; /*!< height we will use, but now always the real height */


        public:
            Image(const std::string& filename);
            Image(void);
            ~Image(void);
            Image& operator=(const std::string& filename);
            Image& operator()(const std::string& filename);

            unsigned int getRealWidth(void);
            unsigned int getRealHeight(void);
            jlug::Rect getRealSize(void);

            unsigned int getWidth(void);
            unsigned int getHeight(void);
            jlug::Rect getSize(void);


            jlug::Rect getBlitRect(void);
            GLuint& getTexture(void);

            void setBlitRect(const jlug::Rect& rect);
            void setBlitRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
            void setAlpha(float alpha);

            static unsigned int getTextureSize(unsigned int size);

            friend class jlug::Window;
    };
}


#endif // IMAGE_HPP_INCLUDED
