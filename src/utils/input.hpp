#ifndef INPUT_HPP_INCLUDED
#define INPUT_HPP_INCLUDED

/**
* \file input.hpp
* \author jirouette
*/

#include <SFML/Window.hpp>
#include "geom/rectangle.hpp"
#include "utils.hpp"
#include "utils/window.hpp"
#include "scripts/lunar.hpp"

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    class Window;
    /**
    * \class Input
    * \brief Store and check input states.
    */
    class Input
    {
        private:
            friend class Lunar<Input>;
            static const char className[];
            static Lunar<Input>::RegType methods[];

        public:
            Input(const sf::Input& sfinput);
            Input(lua_State* L);
            ~Input();

            bool operator[](const jlug::KeyCode::Code& keycode);


            bool isDown(const jlug::KeyCode::Code& keycode);
            jlug::Rect getMousePos(void);
            unsigned int getMouseX(void);
            unsigned int getMouseY(void);


        protected:
            const sf::Input& input; /*!< attribute which stores inputs. */
    };
}

#endif // INPUT_HPP_INCLUDED
