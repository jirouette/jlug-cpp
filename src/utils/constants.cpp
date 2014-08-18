#include "utils/constants.hpp"

/**
* \file utils/constants.cpp
* \author jirouette
*/

const char jlug::Constants::className[] = "Constants";
Lunar<jlug::Constants>::RegType jlug::Constants::methods[] = {
    LUNAR_DECLARE_METHOD(jlug::Constants, get),
    {0,0}
};

luaL_reg jlug::Constants::functions[] = {
    LUNAR_DECLARE_METHOD(jlug::Constants, getInstance),
    {0,0}
};

/**
* \brief Default and only constructor. Does nothing.
*/
jlug::Constants::Constants()
                    :stringConstants(), numericConstants()
{}

jlug::Constants::Constants(lua_State* L):stringConstants(), numericConstants()
{
    (void) L;
}

/**
* \brief Destructor. Does nothing.
*/
jlug::Constants::~Constants()
{}

/**
* \brief get the only instance of the Constants class
*/
jlug::Constants& jlug::Constants::getInstance(void)
{
    static jlug::Constants* instance(new jlug::Constants());
    return *instance;
}

int jlug::Constants::getInstance(lua_State *L)
{
    Lunar<Constants>::push(L, &getInstance());

    return 1;
}

/**
* \brief get a numeric constant
*/
double jlug::Constants::getNumeric(const std::string& name)
{
    std::map<std::string, double>::iterator
    it(numericConstants.find(name));

    if (it != numericConstants.end()) // Found it !
        return it->second;

    // Nothing ? Let's check stringConstants...

    std::map<std::string, std::string>::iterator
    strIt(stringConstants.find(name));

    if (strIt != stringConstants.end()) // Found one
    {
        double i(0);
        std::istringstream iss;

        iss.str(strIt->second);
        iss >> i; // Converted string to numeric
        return i;
    }

    // Well, there is no constant.

    return 0;
}

/**
* \brief get a string constant
*/
int jlug::Constants::get(lua_State* L)
{
    const std::string name(luaL_checkstring(L, 1));
    std::string value(this->get(name));
    lua_pushstring(L, value.c_str());

    return 1;
}

std::string jlug::Constants::get(const std::string& name)
{
    std::map<std::string, std::string>::iterator
    it(stringConstants.find(name));

    if (it != stringConstants.end()) // Found it !
        return it->second;

    // Nothing ? Let's check numericConstants...

    std::map<std::string, double>::iterator
    numIt(numericConstants.find(name));

    if (numIt != numericConstants.end()) // Found one
    {
        std::ostringstream oss;

        oss << numIt->second;
        return oss.str();
    }

    // Well, there is no constant.

    return "";
}

/**
* \brief check if a constant exists
* \return boolean
*/
bool jlug::Constants::exists(const std::string& name)
{
    std::map<std::string, double>::iterator
    numIt(numericConstants.find(name));
    std::map<std::string, std::string>::iterator
    strIt(stringConstants.find(name));

    return numIt != numericConstants.end() ||
           strIt != stringConstants.end();
}

/**
* \brief submit a numeric constant
* \return true if there is no constant named "name", false otherwise
*/
bool jlug::Constants::set(const std::string& name, double value)
{
    if (exists(name))
        return false; // We don't over define a constant
    numericConstants.insert(std::pair<std::string,double>(name, value));
    return true; // Inserted
}

/**
* \brief submit a string constant
* \return true if there is no constant named "name", false otherwise
*/
bool jlug::Constants::set(const std::string& name, const std::string& value)
{
    if (exists(name))
        return false; // We don't over define a constant
    stringConstants.insert(std::pair<std::string,std::string>(name, value));
    return true; // Inserted
}
