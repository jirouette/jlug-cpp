#ifndef SCRIPT_HPP_INCLUDED
#define SCRIPT_HPP_INCLUDED

/**
* \file script.hpp
* \author jirouette
*/

#include <map>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdarg>
#include "utils.hpp"
#include "utils/window.hpp"
#include "utils/input.hpp"
#include "loadable/map.hpp"
#include "entities/character.hpp"
extern "C"
{
  #include <lua5.1/lua.h>
  #include <lua5.1/lualib.h>
  #include <lua5.1/lauxlib.h>
}
#include "lunar.hpp"

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
            static std::map<lua_State*, Script*> scripts;
            static std::map<lua_State*, Script*> initScripts();
            Script(const std::string& filename, bool special);
            static int createScript(lua_State *state);

            void init();

            lua_State *L;
            bool working;
            bool special;

            std::ostringstream out;
            std::ostringstream err;
            std::string name;

        public:
            static void end();
            Script(const std::string& filename);
            ~Script();
            void call(const std::string& function, int nbargs, const std::string& param, ...);
            void flush();
            std::ostringstream& error();
            std::ostringstream& print();
    };
}

#endif // SCRIPT_HPP_INCLUDED
