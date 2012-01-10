#ifndef RESOURCEMANAGER_CPP_INCLUDED
#define RESOURCEMANAGER_CPP_INCLUDED
#include "utils/resourcemanager.hpp"

/**
* \file resourcemanager.cpp
* \author JirialMovie
*/

/**
* \brief get the only instance of the ImageManager class
*/
template<typename T>
jlug::ResourceManager<T>& jlug::ResourceManager<T>::getInstance(void)
{
    static jlug::ResourceManager<T>* instance(new jlug::ResourceManager<T>());
    return *instance;
}

/**
* \brief Default constructor
* Default and only constructor.
*/
template<typename T>
jlug::ResourceManager<T>::ResourceManager(void):
                        files()
{}

/**
* \brief Destructor
* Nothing to do.
*/
template<typename T>
jlug::ResourceManager<T>::~ResourceManager(void)
{}

/**
* \brief get a file by his file name.
* \param filename : file name of the file relative to the executable
* \return file instance
*
* Operator [] overloaded. Calls getFile(const std::string& filename) method and returns it.
*/
template<typename T>
T& jlug::ResourceManager<T>::operator[](const std::string& filename)
{
    return getFile(filename);
}

/**
* \brief get a file by his file name.
* \param filename : file name of the file relative to the executable
* \return file instance
*
* Operator () overloaded. Calls getFile(const std::string& filename) method and returns it.
*/
template<typename T>
T& jlug::ResourceManager<T>::operator()(const std::string& filename)
{
    return getFile(filename);
}

/**
* \brief get a file by his file name.
* \param filename : file name of the files relative to the executable
* \return file type instance
*
* Core of the class. This method checks if a file with this filename is already stored.
* Then, returns it or, if it isn't, try to load it and returns it.
* Throw a std::runtime_error if the loading has failed.
*/
template<typename T>
T& jlug::ResourceManager<T>::getFile(const std::string& filename)
{
    typename std::map<std::string, T>::iterator it(files.find(filename));

    if (it != files.end())
        return it->second; // A file with this filename is found, so, we return it

    files.insert(std::pair<std::string, T>(filename, T(filename))); // We store the new file.
    return getFile(filename); // Returns the new file.
}


/**
* \brief delete a stored file.
* \param filename : file name of the stored file
* \return true if succeed, false if the image were never stored in the ResourceManager instance.
*
* Looks for a file, and destroys it.
*/
template<typename T>
bool jlug::ResourceManager<T>::deleteFile(const std::string& filename)
{
    typename std::map<std::string, T>::iterator it(files.find(filename));
    if (it != files.end())
    {
        files.erase(it);
        return true;
    }
    return false;
}

#endif // RESOURCEMANAGER_CPP_INCLUDED