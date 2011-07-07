#include "animatedcharacter.hpp"

/**
* \file animatedcharacter.cpp
* \author JirialMovie
*/


/**
* \brief Constructor
* \param imageM : reference to the ImageManager instance.
*
* Initialisize everything to default.
*/
jlug::AnimatedCharacter::AnimatedCharacter(jlug::ImageManager& imageM):
                                jlug::Character::Character(imageM)
{}


/**
* \brief Constructor
* \param cid : Charset ID
* \param name : Character's name. May be empty.
* \param imageM : reference to the ImageManager instance.
*
* Initialisize everything.
*/
jlug::AnimatedCharacter::AnimatedCharacter(unsigned int cid, const std::string& cname, jlug::ImageManager& imageM):
                                jlug::Character::Character(cid, cname, imageM)
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

jlug::AnimatedCharacter::AnimatedCharacter(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, jlug::ImageManager& imageM):
                                jlug::Character::Character(cid, cname, posx, posy, imageM)
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

jlug::AnimatedCharacter::AnimatedCharacter(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, unsigned int posz, jlug::ImageManager& imageM):
                                jlug::Character::Character(cid, cname, posx, posy, posz, imageM)
{}


/**
* \brief Destructor
*/
jlug::AnimatedCharacter::~AnimatedCharacter(void)
{}


/**
* \brief animate the character
*/

void jlug::AnimatedCharacter::animate(void)
 {
     bool moving(isMoving);

     isMoving = true;
     jlug::Character::animate();
     isMoving = moving;
 }