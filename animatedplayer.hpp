#ifndef ANIMATEDPLAYER_HPP_INCLUDED
#define ANIMATEDPLAYER_HPP_INCLUDED

/**
* \file animatedplayer.hpp
* \author JirialMovie
*/

#include "character.hpp"
#include "player.hpp"
#include "animatedcharacter.hpp"
#include "input.hpp"

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    /**
    * \class AnimatedPlayer
    * \brief Animated playable Character.
    */
    class AnimatedPlayer : public Player, public AnimatedCharacter
    {
        public:
            AnimatedPlayer(jlug::ImageManager& imageM, jlug::Input& in, jlug::Window& win);
            AnimatedPlayer(unsigned int cid, const std::string& cname, jlug::ImageManager& imageM, jlug::Input& in, jlug::Window& win);
            AnimatedPlayer(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, jlug::ImageManager& imageM, jlug::Input& in, jlug::Window& win);
            AnimatedPlayer(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, unsigned int posz, jlug::ImageManager& imageM, jlug::Input& in, jlug::Window& win);
            ~AnimatedPlayer(void);
    };
}

#endif // ANIMATEDPLAYER_HPP_INCLUDED
