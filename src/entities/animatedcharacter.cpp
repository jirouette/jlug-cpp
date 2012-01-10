#include "entities/animatedcharacter.hpp"

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
jlug::AnimatedCharacter::AnimatedCharacter(void):
                                jlug::Character::Character()
{}


/**
* \brief Constructor
* \param cid : Charset ID
* \param name : Character's name. May be empty.
* \param imageM : reference to the ImageManager instance.
*
* Initialisize everything.
*/
jlug::AnimatedCharacter::AnimatedCharacter(unsigned int cid, const std::string& cname):
                                jlug::Character::Character(cid, cname)
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

jlug::AnimatedCharacter::AnimatedCharacter(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy):
                                jlug::Character::Character(cid, cname, posx, posy)
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

jlug::AnimatedCharacter::AnimatedCharacter(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, unsigned int posz):
                                jlug::Character::Character(cid, cname, posx, posy, posz)
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
