#ifndef INPUT_HPP_INCLUDED
#define INPUT_HPP_INCLUDED

/**
* \file input.hpp
* \author jirouette
*/

#include <SFML/Window.hpp>
#include "geom/rectangle.hpp"
#include "utils.hpp"

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    /**
    * \class Input
    * \brief Store and check input states.
    */
    class Input
    {
        public:
            Input(const sf::Input& sfinput);
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
