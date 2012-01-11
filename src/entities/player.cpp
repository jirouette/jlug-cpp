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
     if (input[jlug::KeyCode::Ctrl])
        velocity = 8;
     else
        velocity = 5;

     if (input[jlug::KeyCode::Left])
            setMove(map, jlug::Move::LEFT, velocity);
     else if (input[jlug::KeyCode::Right])
            setMove(map, jlug::Move::RIGHT, velocity);
     else if (input[jlug::KeyCode::Up])
            setMove(map, jlug::Move::UP, velocity);
     else if (input[jlug::KeyCode::Down])
            setMove(map, jlug::Move::DOWN, velocity);
     else
            setMove(map, jlug::Move::NONE);

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
     //jlug::Image& sprite(jlug::ImageManager::getInstance()[charsetFilename]);

     xpos = pixX-map.getTileWidth()/2-window.getWidth()/2;
     ypos = pixY-map.getTileHeight()-window.getHeight()/2;

     /*map.setScroll(xpos, ypos);

     map.setCamera( static_cast<int>(pixX/map.getTileWidth()-(sprite.getWidth()/2/2)*1.0/map.getTileWidth()),
                    -static_cast<int>(pixY/map.getTileHeight()-sprite.getHeight()/6*1.0/map.getTileHeight()+1)
                    );*/
 }
