#ifndef CHARACTER_HPP_INCLUDED
#define CHARACTER_HPP_INCLUDED

/**
* \file character.hpp
* \author JirialMovie
*/

#include "imagemanager.hpp"


/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    /**
    * \class Character
    * \brief Interactive and movable objects on the map
    */

    class Character
    {

        public:
            Character(jlug::ImageManager& imageM);
            Character(unsigned int cid, const std::string& cname, jlug::ImageManager& imageM);
            Character(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, jlug::ImageManager& imageM);
            Character(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, unsigned int posz, jlug::ImageManager& imageM);
            ~Character(void);


        private:
            unsigned int charset; /*!< ID of the character's charset */
            std::string name; /*!< Name of the character. May be empty, displayed otherwise. */


            unsigned int x; /*!< X-position */
            unsigned int y; /*!< Y-position */
            unsigned int z; /*!< Z-position */


            jlug::ImageManager& IM; /*!< image manager */
    };



}

#endif // CHARACTER_HPP_INCLUDED
