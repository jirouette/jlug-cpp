#ifndef CONSTANTS_HPP_INCLUDED
#define CONSTANTS_HPP_INCLUDED

/**
* \file utils/Constants.hpp
* \author jirouette
*/

#include <map>
#include <string>
#include <sstream>
#include "scripts/lunar.hpp"

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    /**
    * \class Constants
    * \brief Constants storage
    */

    class Constants
    {
        private:
            friend class Lunar<Constants>;
            static const char className[];
            static Lunar<Constants>::RegType methods[];
            static luaL_reg functions[];
        public:
            bool set(const std::string& name, const std::string& value);
            bool set(const std::string& name, double value);

            bool exists(const std::string& name);

            double getNumeric(const std::string& name);
            std::string get(const std::string& name);
            int get(lua_State* L);

            static Constants& getInstance(void);
            static int getInstance(lua_State* L);

            ~Constants();
        protected:
            Constants();
            Constants(lua_State* L);

            std::map<std::string, std::string> stringConstants;
            std::map<std::string, double> numericConstants;
    };

}


#endif // CONSTANTS_HPP_INCLUDED
