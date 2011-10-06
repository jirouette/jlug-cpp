#ifndef IMAGEMANAGER_HPP_INCLUDED
#define IMAGEMANAGER_HPP_INCLUDED

/**
* \file imagemanager.hpp
* \author JirialMovie
*/

#include <SFML/Graphics.hpp>
#include <map>
#include <exception>
#include <stdexcept>
#include <iostream>

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    /**
    * \class ImageManager
    * \brief Manages the external images.
    *
    * Stores any image used to give it if re-used.
    * This class avoids loading of several same images.
    */
    class ImageManager
    {
        public:
            static ImageManager& getInstance(void);
            ~ImageManager(void);
            sf::Image& getImage(const std::string& filename);
            sf::Image& operator[](const std::string& filename);
            sf::Image& operator()(const std::string& filename);
            GLuint& getTexture(const std::string& filename);
            bool setMask(const std::string& filename, unsigned int r, unsigned int g, unsigned int b);
            bool setAlpha(const std::string& filename, unsigned int a);
            bool deleteImage(const std::string& filename);

        protected:
            ImageManager(void);
            //ImageManager(const ImageManager&);

            std::map<std::string, sf::Image> images; /*!< Images stored by filename */
            std::map<std::string, GLuint> textures; /*!< Textures stored by filename */
    };
}

#endif // IMAGEMANAGER_HPP_INCLUDED
