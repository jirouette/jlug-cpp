#include "input.hpp"

/**
* \file input.cpp
* \author JirialMovie
*/

/**
* \brief Constructor
*
* Default constructor. With this constructor, the instance is unusable.
*/
jlug::Input::Input()
            : input()
{}

/**
* \brief Constructor
* \param sfinput : Reference to graphic library's event type variable.
*
* Initialize the instance by affecting the reference attribute input with the parameter sfinput.
*/
jlug::Input::Input(const sf::Input& sfinput)
            : input(sfinput)
{
    //memcpy((void*)(&input), (void*)(&sfinput), sizeof(const sf::Input));
}

/**
* \brief Destructor
* Nothing to do.
*/
jlug::Input::~Input()
 {
    //delete input;
 }

/**
* \brief Check if a key is down or not.
* \param keycode : code of the key we're checking
* \return true if the key is down. false if the key is not down.
*
* Operator[] overloaded. Calls the isDown(const jlug::KeyCode::Code& keycode) method and returns it.
*/
bool jlug::Input::operator[](const jlug::KeyCode::Code& keycode)
 {
     return isDown(keycode);
 }

/*jlug::Input& jlug::Input::operator=(const sf::Input& sfinput)
 {
    memcpy((void*)(&input), (void*)(&sfinput), sizeof(const sf::Input));
    return *this;
 }*/

/*jlug::Input& jlug::Input::operator=(const jlug::Input& copy)
 {
     memcpy((void*)(&input), (void*)(&(copy.input)), sizeof(const sf::Input));
     return *this;
 }*/

/**
* \brief Check if a key is down or not.
* \param keycode : code of the key we're checking
* \return true if the key is down. false if the key is not down.
*
* Check if the key is down.
*/
bool jlug::Input::isDown(const jlug::KeyCode::Code& keycode)
 {
     if (keycode >= jlug::KeyCode::A && keycode <= jlug::KeyCode::Z) // Faster than a switch, A to Z have several values.
        return input.IsKeyDown(static_cast<sf::Key::Code>(static_cast<int>(sf::Key::A) + keycode - jlug::KeyCode::A)); // Same for the SFML A to Z values.
     else if (keycode >= jlug::KeyCode::Number0 && keycode <= jlug::KeyCode::Number9) // Faster than a switch, 0 to 9 have several values.
        return input.IsKeyDown(static_cast<sf::Key::Code>(static_cast<int>(sf::Key::Num0) + keycode - jlug::KeyCode::Number0)); // Same for the SFML 0 to 9 values.
     else
        switch(keycode)
        {
            case jlug::KeyCode::Ctrl: // Using OR to detect any Ctrl key : left Ctrl key or right Ctrl key or both.
                return input.IsKeyDown(sf::Key::LControl)||input.IsKeyDown(sf::Key::RControl);
            break;

            case jlug::KeyCode::Alt: // Using OR to detect any Alt key : left Alt key or right Alt key or both.
                return input.IsKeyDown(sf::Key::LAlt)||input.IsKeyDown(sf::Key::RAlt);
            break;

            case jlug::KeyCode::Shift: // Using OR to detect any Shift key : left Shift key or right Shift key or both.
                return input.IsKeyDown(sf::Key::LShift)||input.IsKeyDown(sf::Key::RShift);
            break;

            case jlug::KeyCode::Super: // Using OR to detect any Super key : left Super key or Super Ctrl key or both.
                return input.IsKeyDown(sf::Key::LSystem)||input.IsKeyDown(sf::Key::RSystem);
            break;

            case jlug::KeyCode::Tab: // Tab
                return input.IsKeyDown(sf::Key::Tab);
            break;

            case jlug::KeyCode::Escape: // Escape
                return input.IsKeyDown(sf::Key::Escape);
            break;

            case jlug::KeyCode::Space: // Space
                return input.IsKeyDown(sf::Key::Space);
            break;

            case jlug::KeyCode::Enter: // Enter
                return input.IsKeyDown(sf::Key::Return);
            break;

            case jlug::KeyCode::Pause: // Pause
                return input.IsKeyDown(sf::Key::Pause);
            break;

            case jlug::KeyCode::Left: // Left
                return input.IsKeyDown(sf::Key::Left);
            break;

            case jlug::KeyCode::Right: // Right
                return input.IsKeyDown(sf::Key::Right);
            break;

            case jlug::KeyCode::Up: // Up
                return input.IsKeyDown(sf::Key::Up);
            break;

            case jlug::KeyCode::Down: // Down
                return input.IsKeyDown(sf::Key::Down);
            break;



            default: // Nothing to do.
            break;
        }

     return false; // If the switch didn't catch known values, then, we consider the key isn't down.
 }

/**
* \brief get Mouse X-value
* \return Mouse X-value
*/
unsigned int jlug::Input::getMouseX(void)
 {
     return input.GetMouseX();
 }

/**
* \brief get Mouse Y-value
* \return Mouse Y-value
*/
unsigned int jlug::Input::getMouseY(void)
 {
     return input.GetMouseY();
 }

/**
* \brief get Mouse Position
* \return rect with
            x datafield as mouse X-value,
            y datafield as mouse Y-value,
            w as 1,
            h as 1,
*/
jlug::Rect jlug::Input::getMousePos(void)
 {
     jlug::Rect rect = {getMouseX(), getMouseY(), 1, 1};
     return rect;
 }
