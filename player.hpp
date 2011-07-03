#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

/**
* \file player.hpp
* \author JirialMovie
*/

#include "character.hpp"
#include "input.hpp"

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    /**
    * \class Player
    * \brief Playable Character.
    */
    class Player : public virtual Character
    {
        public:
            Player(jlug::ImageManager& imageM, jlug::Input& in);
            Player(unsigned int cid, const std::string& cname, jlug::ImageManager& imageM, jlug::Input& in);
            Player(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, jlug::ImageManager& imageM, jlug::Input& in);
            Player(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, unsigned int posz, jlug::ImageManager& imageM, jlug::Input& in);
            ~Player(void);

            virtual void move(jlug::Map& map);

        protected:
            jlug::Input& input;
            int velocity;
    };
}

#endif // PLAYER_HPP_INCLUDED
