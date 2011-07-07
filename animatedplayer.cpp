#include "animatedplayer.hpp"

/**
* \file animatedplayer.cpp
* \author JirialMovie
*/


/**
* \brief Constructor
* \param imageM : reference to the ImageManager instance.
*
* Initialisize everything to default.
*/
jlug::AnimatedPlayer::AnimatedPlayer(jlug::ImageManager& imageM, jlug::Input& in, jlug::Window& win):
                                jlug::Character::Character(imageM),
                                jlug::Player::Player(imageM, in, win),
                                jlug::AnimatedCharacter::AnimatedCharacter(imageM)
{}


/**
* \brief Constructor
* \param cid : Charset ID
* \param name : Character's name. May be empty.
* \param imageM : reference to the ImageManager instance.
*
* Initialisize everything.
*/
jlug::AnimatedPlayer::AnimatedPlayer(unsigned int cid, const std::string& cname, jlug::ImageManager& imageM, jlug::Input& in, jlug::Window& win):
                                jlug::Character::Character(cid, cname, imageM),
                                jlug::Player::Player(cid, cname, imageM, in, win),
                                jlug::AnimatedCharacter::AnimatedCharacter(cid, cname, imageM)
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

jlug::AnimatedPlayer::AnimatedPlayer(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, jlug::ImageManager& imageM, jlug::Input& in, jlug::Window& win):
                                jlug::Character::Character(cid, cname, posx, posy, imageM),
                                jlug::Player::Player(cid, cname, posx, posy, imageM, in, win),
                                jlug::AnimatedCharacter::AnimatedCharacter(cid, cname, posx, posy, imageM)
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

jlug::AnimatedPlayer::AnimatedPlayer(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, unsigned int posz, jlug::ImageManager& imageM, jlug::Input& in, jlug::Window& win):
                                jlug::Character::Character(cid, cname, posx, posy, posz, imageM),
                                jlug::Player::Player(cid, cname, posx, posy, posz, imageM, in, win),
                                jlug::AnimatedCharacter::AnimatedCharacter(cid, cname, posx, posy, posz, imageM)
{}


/**
* \brief Destructor
*/
jlug::AnimatedPlayer::~AnimatedPlayer(void)
{}
