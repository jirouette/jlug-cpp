#ifndef ANIMATEDCHARACTER_HPP_INCLUDED
#define ANIMATEDCHARACTER_HPP_INCLUDED

/**
* \file animatedcharacter.hpp
* \author JirialMovie
*/

#include "entities/character.hpp"
#include "utils/input.hpp"

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    /**
    * \class AnimatedCharacter
    * \brief Animated Character.
    */
    class AnimatedCharacter : public virtual Character
    {
        public:
            AnimatedCharacter(void);
            AnimatedCharacter(unsigned int cid, const std::string& cname);
            AnimatedCharacter(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy);
            AnimatedCharacter(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, unsigned int posz);
            ~AnimatedCharacter(void);

            virtual void animate(void);
    };
}

#endif // ANIMATEDCHARACTER_HPP_INCLUDED
