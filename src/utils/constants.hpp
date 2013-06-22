#ifndef CONSTANTS_HPP_INCLUDED
#define CONSTANTS_HPP_INCLUDED

/**
* \file utils/Constants.hpp
* \author jirouette
*/

#include <map>
#include <string>
#include <sstream>

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
        public:
            bool set(const std::string& name, const std::string& value);
            bool set(const std::string& name, double value);

            bool exists(const std::string& name);

            double getNumeric(const std::string& name);
            std::string get(const std::string& name);

            static Constants& getInstance(void);

            ~Constants();
        protected:
            Constants();

            std::map<std::string, std::string> stringConstants;
            std::map<std::string, double> numericConstants;
    };

}


#endif // CONSTANTS_HPP_INCLUDED
