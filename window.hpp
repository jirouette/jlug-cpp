#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

/**
* \file window.hpp
* \author JirialMovie
*/

#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "image.hpp"
#include "input.hpp"

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    /**
    * \class Window
    * \brief Display a window where we will draw and listen events
    */
    class Window
    {
        public:
            Window(unsigned int width, unsigned int height, const std::string& name = "jLug");
            ~Window(void);
            void setBlitRect(const jlug::Rect& rect);
            void setBlitRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
            void blit(jlug::Image& img);
            void blit(jlug::Image& img, int x, int y);
            void blit(jlug::Image& img, const jlug::Rect& pos);
            void flip(void);
            void clear(void);
            void close(void);
            void processEvents(void);

            unsigned int getWidth(void);
            unsigned int getHeight(void);
            jlug::Rect getSize(void);
            const jlug::Input& getInput(void);

            bool isOpen(void);
        private:
            sf::RenderWindow win; /*!< Graphic library's window */
            jlug::Rect blitRect; /*!< rect which delimits the blit */
    };
}



#endif // WINDOW_HPP_INCLUDED