#include "entities/animatedplayer.hpp"

/**
* \file animatedplayer.cpp
* \author jirouette
*/


/**
* \brief Constructor
* \param imageM : reference to the ImageManager instance.
*
* Initialisize everything to default.
*/
jlug::AnimatedPlayer::AnimatedPlayer(jlug::Input& in, jlug::Window& win):
                                jlug::Character::Character(),
                                jlug::Player::Player(in, win),
                                jlug::AnimatedCharacter::AnimatedCharacter()
{}


/**
* \brief Constructor
* \param cid : Charset ID
* \param name : Character's name. May be empty.
* \param imageM : reference to the ImageManager instance.
*
* Initialisize everything.
*/
jlug::AnimatedPlayer::AnimatedPlayer(unsigned int cid, const std::string& cname, jlug::Input& in, jlug::Window& win):
                                jlug::Character::Character(cid, cname),
                                jlug::Player::Player(cid, cname, in, win),
                                jlug::AnimatedCharacter::AnimatedCharacter(cid, cname)
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

jlug::AnimatedPlayer::AnimatedPlayer(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, jlug::Input& in, jlug::Window& win):
                                jlug::Character::Character(cid, cname, posx, posy),
                                jlug::Player::Player(cid, cname, posx, posy, in, win),
                                jlug::AnimatedCharacter::AnimatedCharacter(cid, cname, posx, posy)
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

jlug::AnimatedPlayer::AnimatedPlayer(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, unsigned int posz, jlug::Input& in, jlug::Window& win):
                                jlug::Character::Character(cid, cname, posx, posy, posz),
                                jlug::Player::Player(cid, cname, posx, posy, posz, in, win),
                                jlug::AnimatedCharacter::AnimatedCharacter(cid, cname, posx, posy, posz)
{}


/**
* \brief Destructor
*/
jlug::AnimatedPlayer::~AnimatedPlayer(void)
{}
