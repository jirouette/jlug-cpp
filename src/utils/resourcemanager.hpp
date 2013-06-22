#ifndef RESOURCEMANAGER_HPP_INCLUDED
#define RESOURCEMANAGER_HPP_INCLUDED

/**
* \file resourcemanager.hpp
* \author jirouette
*/

#include <map>
#include <exception>
#include <stdexcept>
#include <iostream>
#include "loadable/image.hpp"

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    /**
    * \class ResourceManager
    * \brief Manages the external files.
    *
    * Stores any file used to give it if re-used.
    * This class avoids loading of several same files.
    */
    template<typename T>
    class ResourceManager
    {
        public:
            static ResourceManager& getInstance(void);
            ~ResourceManager(void);
            T& getFile(const std::string& filename);
            T& operator[](const std::string& filename);
            T& operator()(const std::string& filename);
            bool deleteFile(const std::string& filename);

        protected:
            ResourceManager(void);
            //ResourceManager(const ResourceManager&);

            std::map<std::string, T> files; /*!< Files stored by filename */
    };

    typedef ResourceManager<jlug::Image> ImageManager;
}

#include "utils/resourcemanager.cpp"
#endif // RESOURCEMANAGER_HPP_INCLUDED
