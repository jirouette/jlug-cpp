#ifndef SCRIPTMAP_HPP_INCLUDED
#define SCRIPTMAP_HPP_INCLUDED

/**
* \file map.hpp
* \author jirouette
*/

#include <map>
#include <iostream>
#include <string>
#include "utils.hpp"
#include "loadable/map.hpp"
extern "C" 
{
  #include <lua5.2/lua.h>
  #include <lua5.2/lualib.h>
  #include <lua5.2/lauxlib.h>
}  

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug::scripts
{
      /**
      * \class Script
      * \brief Allowing scripting of the game
      */
    class Map
    {
        public:
            static int instantiate(lua_State* L);
            static int removeCharacter(lua_State* L);
    };
}

#endif // SCRIPTMAP_HPP_INCLUDED
