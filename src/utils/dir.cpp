#include "utils/dir.hpp"

/**
* \brief obtains directory from a filepath
* \return directory of a file
*/
std::string jlug::getDir(const std::string& file)
{
    size_t filePos(file.find_last_of("/\\"));
    if (filePos == std::string::npos)
        return "./";
    else
        return file.substr(0, filePos) + '/';
}
