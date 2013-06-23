#ifndef SCRIPT_HPP_INCLUDED
#define SCRIPT_HPP_INCLUDED

/**
* \file script.hpp
* \author jirouette
*/

#include <list>
#include <iostream>
#include "utils.hpp"

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
      /**
      * \class Script
      * \brief Allowing scripting of the game
      */
    class Script
    {
        protected:
            static std::list<Script*> scripts;
            static std::list<Script*> initScripts();
        
        public:
            Script();
            ~Script();
    };
}

#endif // SCRIPT_HPP_INCLUDED
