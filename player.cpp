#include "player.hpp"

/**
* \file player.cpp
* \author JirialMovie
*/

/**
* \brief Constructor
* \param imageM : reference to the ImageManager instance.
*
* Initialisize everything to default.
*/
jlug::Player::Player(jlug::ImageManager& imageM, jlug::Input& in):
                                jlug::Character::Character(imageM), input(in), velocity(5)
{}


/**
* \brief Constructor
* \param cid : Charset ID
* \param name : Character's name. May be empty.
* \param imageM : reference to the ImageManager instance.
*
* Initialisize everything.
*/
jlug::Player::Player(unsigned int cid, const std::string& cname, jlug::ImageManager& imageM, jlug::Input& in):
                                jlug::Character::Character(cid, cname, imageM), input(in), velocity(5)
{}

/**
* \brief Constructor
* \param cid : Charset ID
* \param name : Character's name. May be empty.
* \param x : X-position of the character.
* \param y : Y-position of the character.
* \param imageM : reference to the ImageManager instance.
*
* Initialisize everything.
*/

jlug::Player::Player(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, jlug::ImageManager& imageM, jlug::Input& in):
                                jlug::Character::Character(cid, cname, posx, posy, imageM), input(in), velocity(5)
{}

/**
* \brief Constructor
* \param cid : Charset ID
* \param name : Character's name. May be empty.
* \param x : X-position of the character.
* \param y : Y-position of the character.
* \param imageM : reference to the ImageManager instance.
*
* Initialisize everything.
*/

jlug::Player::Player(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, unsigned int posz, jlug::ImageManager& imageM, jlug::Input& in):
                                jlug::Character::Character(cid, cname, posx, posy, posz, imageM), input(in), velocity(5)
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
     if (input[jlug::KeyCode::Ctrl])
        velocity = 8;
     else
        velocity = 5;


     if (input[jlug::KeyCode::Left])
     {
        if ((pixX%tileWidth == 0 && pixY%tileHeight == 0)||(isMoving && direction == jlug::Move::LEFT))
            setMove(jlug::Move::LEFT, velocity);
        else
            setMove(jlug::Move::NONE);
     }
     else if (input[jlug::KeyCode::Right])
     {
        if ((pixX%tileWidth == 0 && pixY%tileHeight == 0)||(isMoving && direction == jlug::Move::RIGHT))
            setMove(jlug::Move::RIGHT, velocity);
        else
            setMove(jlug::Move::NONE);
     }
     else if (input[jlug::KeyCode::Up])
     {
        if ((pixX%tileWidth == 0 && pixY%tileHeight == 0)||(isMoving && direction == jlug::Move::UP))
            setMove(jlug::Move::UP, velocity);
        else
            setMove(jlug::Move::NONE);
     }
     else if (input[jlug::KeyCode::Down])
     {
        if ((pixX%tileWidth == 0 && pixY%tileHeight == 0)||(isMoving && direction == jlug::Move::DOWN))
            setMove(jlug::Move::DOWN, velocity);
        else
            setMove(jlug::Move::NONE);
     }
     else
        setMove(jlug::Move::NONE);

     jlug::Character::move(map);
 }
