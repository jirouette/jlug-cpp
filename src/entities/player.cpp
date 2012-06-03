#include "entities/player.hpp"

/**
* \file player.cpp
* \author JirialMovie
*/

/**
* \brief Constructor
* \param imageM : reference to the ImageManager instance.
* \param in : reference to the Input instance
*
* Initialisize everything to default.
*/
jlug::Player::Player(jlug::Input& in, jlug::Window& win):
                                jlug::Character::Character(), input(in), window(win), velocity(5)
{}


/**
* \brief Constructor
* \param cid : Charset ID
* \param name : Character's name. May be empty.
* \param imageM : reference to the ImageManager instance.
* \param in : reference to the Input instance
*
* Initialisize everything.
*/
jlug::Player::Player(unsigned int cid, const std::string& cname, jlug::Input& in, jlug::Window& win):
                                jlug::Character::Character(cid, cname), input(in), window(win), velocity(5)
{}

/**
* \brief Constructor
* \param cid : Charset ID
* \param name : Character's name. May be empty.
* \param x : X-position of the character.
* \param y : Y-position of the character.
* \param imageM : reference to the ImageManager instance.
* \param in : reference to the Input instance
*
* Initialisize everything.
*/

jlug::Player::Player(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, jlug::Input& in, jlug::Window& win):
                                jlug::Character::Character(cid, cname, posx, posy), input(in), window(win), velocity(5)
{}

/**
* \brief Constructor
* \param cid : Charset ID
* \param name : Character's name. May be empty.
* \param x : X-position of the character.
* \param y : Y-position of the character.
* \param imageM : reference to the ImageManager instance.
* \param in : reference to the Input instance
*
* Initialisize everything.
*/

jlug::Player::Player(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, unsigned int posz, jlug::Input& in, jlug::Window& win):
                                jlug::Character::Character(cid, cname, posx, posy, posz), input(in), window(win), velocity(5)
{}


/**
* \brief Destructor
*/
jlug::Player::~Player()
{}


/**
* \brief move the character
* \param map : reference to the current map
*/

void jlug::Player::move(jlug::Map& map)
 {
     int tileWidth(map.getTileWidth()), tileHeight(map.getTileHeight());
     jlug::Move::Direction dir(direction);
     if (input[jlug::KeyCode::Ctrl])
        velocity = 16;
     else
        velocity = 12;

     setMove(jlug::Move::NONE);

     if (input[jlug::KeyCode::Left])
     {
        if ((pixX%tileWidth == 0 && pixY%tileHeight == 0)||(isMoving && dir == jlug::Move::LEFT))
            setMove(jlug::Move::LEFT, velocity);
     }
     else if (input[jlug::KeyCode::Right])
     {
        if ((pixX%tileWidth == 0 && pixY%tileHeight == 0)||(isMoving && dir == jlug::Move::RIGHT))
            setMove(jlug::Move::RIGHT, velocity);
     }
     else if (input[jlug::KeyCode::Up])
     {
        if ((pixX%tileWidth == 0 && pixY%tileHeight == 0)||(isMoving && dir == jlug::Move::UP))
            setMove(jlug::Move::UP, velocity);
     }
     else if (input[jlug::KeyCode::Down])
     {
        if ((pixX%tileWidth == 0 && pixY%tileHeight == 0)||(isMoving && dir == jlug::Move::DOWN))
            setMove(jlug::Move::DOWN, velocity);
     }

     jlug::Character::move(map);
     scroll(map);
 }


/**
* \brief scroll the window
* \param map : reference to the current map
*/

void jlug::Player::scroll(jlug::Map& map)
 {
     int xpos(0), ypos(0);
     jlug::Image& sprite(jlug::ImageManager::getInstance()[charsetFilename]);

     xpos = pixX-map.getTileWidth()/2-window.getWidth()/2;
     ypos = pixY-map.getTileHeight()-window.getHeight()/2;

     map.setScroll(xpos, ypos);

     map.setCamera( pixX/static_cast<double>(map.getTileWidth()),
                    -pixY/static_cast<double>(map.getTileHeight())
                    );
 }
