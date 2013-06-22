#ifndef ANIMATEDPLAYER_HPP_INCLUDED
#define ANIMATEDPLAYER_HPP_INCLUDED

/**
* \file animatedplayer.hpp
* \author jirouette
*/

#include "entities/character.hpp"
#include "entities/player.hpp"
#include "entities/animatedcharacter.hpp"
#include "utils/input.hpp"

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
            AnimatedPlayer(jlug::Input& in, jlug::Window& win);
            AnimatedPlayer(unsigned int cid, const std::string& cname, jlug::Input& in, jlug::Window& win);
            AnimatedPlayer(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, jlug::Input& in, jlug::Window& win);
            AnimatedPlayer(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, unsigned int posz, jlug::Input& in, jlug::Window& win);
            ~AnimatedPlayer(void);
    };
}

#endif // ANIMATEDPLAYER_HPP_INCLUDED
