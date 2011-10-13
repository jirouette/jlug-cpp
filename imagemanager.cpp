#include "imagemanager.hpp"

/**
* \file imagemanager.cpp
* \author JirialMovie
*/

/**
* \brief Default constructor
* Default and only constructor.
*/
jlug::ImageManager::ImageManager(void):
                        images()
{}


/**
* \brief get the only instance of the ImageManager class
*/

jlug::ImageManager& jlug::ImageManager::getInstance(void)
{
    static jlug::ImageManager* instance(new ImageManager());
    return *instance;
}

/**
* \brief Destructor
* Nothing to do.
*/
jlug::ImageManager::~ImageManager(void)
{}

/**
* \brief get an image by his file name.
* \param filename : file name of the images relative to the executable
* \return graphic library's type variable
*
* Core of the class. This method checks if an image with this filename is already stored.
* Then, returns it or, if it isn't, try to load it and returns it.
* Throw a std::runtime_error if the loading has failed.
*/
jlug::Image& jlug::ImageManager::getImage(const std::string& filename)
{
    jlug::Image image;
    std::map<std::string, jlug::Image>::iterator it(images.find(filename));

    if (it != images.end())
        return it->second; // An image with this filename is found, so, we return it

    image = filename;

    images.insert(std::pair<std::string, jlug::Image>(filename, image)); // We store the new image.
    return images[filename]; // Returns the new image.
}

GLuint& jlug::ImageManager::getTexture(const std::string& filename)
 {
     std::map<std::string, GLuint>::iterator it(textures.find(filename));

     if (it != textures.end())
        return it->second;

     textures.insert(std::pair<std::string, GLuint>(filename, 0));
     {
         GLuint& texture(getTexture(filename));
         jlug::Image& img(getImage(filename));
         glGenTextures(1, &texture);
         glBindTexture(GL_TEXTURE_2D, texture);
         std::cout << filename << " -> " << img.getRealWidth() << "/" << img.getRealHeight();
         std::cout << " VS " << img.getWidth() << "/" << img.getHeight() << std::endl;
         gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,img.getRealWidth(), img.getRealHeight(),GL_RGBA,GL_UNSIGNED_BYTE,img.getRaw().GetPixelsPtr());
         return texture;
     }
 }
/**
* \brief get an image by his file name.
* \param filename : file name of the images relative to the executable
* \return graphic library's type variable
*
* Operator [] overloaded. Calls getImage(const std::string& filename) method and returns it.
*/
jlug::Image& jlug::ImageManager::operator[](const std::string& filename)
{
    return getImage(filename);
}

/**
* \brief get an image by his file name.
* \param filename : file name of the images relative to the executable
* \return graphic library's type variable
*
* Operator () overloaded. Calls getImage(const std::string& filename) method and returns it.
*/
jlug::Image& jlug::ImageManager::operator()(const std::string& filename)
{
    return getImage(filename);
}

/**
* \brief set transparence mask.
* \param filename : file name of the image whose mask will be changed.
* \param r : Red value. Between 0 and 255.
* \param g : Green value. Between 0 and 255.
* \param b : Blue value. Between 0 and 255.
* \return true
* \deprecated
*
* Simply sets the transparence mask.
*/
bool jlug::ImageManager::setMask(const std::string& filename, unsigned int r, unsigned int g, unsigned int b)
{
    std::cerr << "ImageManager::setMask(" << filename << ", " << r << ", " << g << ", " << b << ") does not work. " << std::endl;
    //getImage(filename).CreateMaskFromColor(sf::Color(r, g, b));
    return true;
}

/**
* \brief set alpha transparence.
* \param filename : file name of the image whose alpha transparence will be changed.
* \param a : Alpha value. Between 0 and 255.
* \return true
* \bug This method does not work.
* \deprecated This method is to be removed.
*
* Simply sets the alpha transparence.
*/
bool jlug::ImageManager::setAlpha(const std::string& filename, unsigned int a)
{
    std::cerr << "ImageManager::setAlpha(" << filename << ", " << a << ") does not work. " << std::endl;
    //getImage(filename).SetColor(sf::Color(255, 255, 255, a));
    return true;
}

/**
* \brief delete an stored image.
* \param filename : file name of the stored image
* \return true if succeed, false if the image were never stored in the ImageManager instance.
*
* Looks for an image, and destroys it.
*/
bool jlug::ImageManager::deleteImage(const std::string& filename)
{
    std::map<std::string, jlug::Image>::iterator it(images.find(filename));
    if (it != images.end())
    {
        images.erase(it);
        return true;
    }
    return false;
}
