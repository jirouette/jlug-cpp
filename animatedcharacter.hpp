#ifndef ANIMATEDCHARACTER_HPP_INCLUDED
#define ANIMATEDCHARACTER_HPP_INCLUDED

/**
* \file animatedcharacter.hpp
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
    * \class AnimatedCharacter
    * \brief Animated Character.
    */
    class AnimatedCharacter : public virtual Character
    {
        public:
            AnimatedCharacter(jlug::ImageManager& imageM);
            AnimatedCharacter(unsigned int cid, const std::string& cname, jlug::ImageManager& imageM);
            AnimatedCharacter(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, jlug::ImageManager& imageM);
            AnimatedCharacter(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, unsigned int posz, jlug::ImageManager& imageM);
            ~AnimatedCharacter(void);

            virtual void animate(void);
    };
}

#endif // ANIMATEDCHARACTER_HPP_INCLUDED
