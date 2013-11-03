#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

/**
* \file window.hpp
* \author jirouette
*/

#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "geom/utils.hpp"
#include "geom/point.hpp"
#include "geom/rectangle.hpp"
#include "loadable/image.hpp"
#include "utils/input.hpp"
#include "utils/constants.hpp"
#include "scripts/lunar.hpp"

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    class Input;
    /**
    * \class Window
    * \brief Display a window where we will draw and listen events
    */
    class Window
    {
        private:
            friend class Lunar<Window>;
            static const char className[];
            static Lunar<Window>::RegType methods[];

        public:
            Window(unsigned int width, unsigned int height, const std::string& name = "jLug");
            Window(lua_State* L);
            ~Window(void);
            void setBlitRect(const jlug::Rect& rect);
            void setBlitRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
            void blit(jlug::Image& img);
            void blit(jlug::Image& img, int x, int y);
            void blit(jlug::Image& img, const jlug::Rect& pos);
            void text(const std::string& sentence, int x, int y);
            void flip(void);
            int flip(lua_State* L);
            void clear(void);
            int clear(lua_State* L);
            void close(void);
            int close(lua_State* L);
            void processEvents(void);

            void debug(const std::string& str);
            int debug(lua_State* L);
            int test(lua_State* L);

            unsigned int getWidth(void);
            unsigned int getHeight(void);
            jlug::Rect getSize(void);
            const jlug::Input& getInput(void);

            bool isOpen(void);
            int isOpen(lua_State* L);
        protected:
            void beforeDisplaying(void);
            void afterDisplaying(void);

            sf::RenderWindow win; /*!< Graphic library's window */
            jlug::Rect blitRect; /*!< rect which delimits the blit */
            std::string debugStr; /*!< debug-text */
            sf::String debugWinstr; /*!< Graphic library's string */
            sf::String winstr;
            sf::Font font; /*!< Graphic library's font */
    };
}



#endif // WINDOW_HPP_INCLUDED
