#include "character.hpp"

/**
* \file character.cpp
* \author JirialMovie
*/




/**
* \brief Constructor
* \param imageM : reference to the ImageManager instance.
*
* Initialisize everything to default.
*/

jlug::Character::Character(jlug::ImageManager& imageM):
                        charset(0), name(""), x(0), y(0), z(0), IM(imageM)
{}

/**
* \brief Constructor
* \param cid : Charset ID
* \param name : Character's name. May be empty.
* \param imageM : reference to the ImageManager instance.
*
* Initialisize everything.
*/

jlug::Character::Character(unsigned int cid, const std::string& cname, jlug::ImageManager& imageM):
                        charset(cid), name(cname), x(0), y(0), z(0), IM(imageM)
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

jlug::Character::Character(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, jlug::ImageManager& imageM):
                        charset(cid), name(cname), x(posx), y(posy), z(0), IM(imageM)
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

jlug::Character::Character(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, unsigned int posz, jlug::ImageManager& imageM):
                        charset(cid), name(cname), x(posx), y(posy), z(posz), IM(imageM)
{}


/**
* \brief set manually an X-position
*/

void jlug::Character::setX(unsigned int posx)
  {
      x = posx;
  }

/**
* \brief set manually an Y-position
*/

void jlug::Character::setY(unsigned int posy)
 {
     y = posy;
 }

/**
* \brief set manually a Z-position
*/

void jlug::Character::setZ(unsigned int posz)
 {
     z = posz;
 }


/**
* \brief set manually a 2D position
*/
void jlug::Character::setPosition(unsigned int posx, unsigned int posy)
 {
     setX(posx);
     setY(posy);
 }

/**
* \brief set manually a 3D position
*/

void jlug::Character::setPosition(unsigned int posx, unsigned int posy, unsigned int posz)
 {
     setPosition(posx, posy);
     setZ(posz);
 }

/**
* \brief set manually a charset
*/

void jlug::Character::setCharset(unsigned int cid)
 {
     charset = cid;
 }

/**
* \brief set manually a name
*/

void jlug::Character::setName(const std::string& cname)
 {
     name = cname;
 }




/**
* \brief get character's X-position
* \return X-position
*/

unsigned int jlug::Character::getX(void)
 {
     return x;
 }

/**
* \brief get character's Y-position
* \return Y-position
*/

unsigned int jlug::Character::getY(void)
 {
     return y;
 }

/**
* \brief get character's Z-position
* \return Z-position
*/

unsigned int jlug::Character::getZ(void)
 {
     return z;
 }

/**
* \brief get character's 2D position
* \return 2D position in a Rect
*/

jlug::Rect jlug::Character::getPosition(void)
 {
     jlug::Rect position = {x, y, 0, 0};
     return position;
 }

/**
* \brief get character's charset
* \return charset's ID
*/

unsigned int jlug::Character::getCharset(void)
 {
     return charset;
 }

/**
* \brief get character's name
* \return name in a std::string
*/

const std::string& jlug::Character::getName(void)
 {
     return name;
 }
