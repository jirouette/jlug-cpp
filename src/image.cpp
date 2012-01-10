#include "image.hpp"

/**
* \file image.cpp
* \author JirialMovie
*/

/**
* \brief Constructor
* \param img : Reference to a constant graphic library's type variable.
*
* Creates an Image predefined with the parameter img.
* Sets also the blitRect as default (Min X, Max Width, Min Y, Max Height).
*/
jlug::Image::Image(const std::string& filename)
               :texture(0), image(), raw(), blitRect(), width(0), height(0)
 {
     jlug::Image::operator=(filename);
 }

/**
* \brief Default constructor
*
* Creates an empty Image with default blitRect.
*/
jlug::Image::Image(void)
            :texture(0), image(), raw(), blitRect(), width(0), height(0)
 {}

/**
* \brief Destructor
*
* Nothing to do.
*/
jlug::Image::~Image()
{}


/**
* \brief Operator = overloaded with filename
* \param filename : path to file
* \return Reference to the current Image instance.
*
* Changes or sets an image.
*/
jlug::Image& jlug::Image::operator=(const std::string& filename)
 {
     if (!raw.LoadFromFile(filename.c_str()))
        throw std::runtime_error("could not open image"); // Loading failure

     raw.SetSmooth(false); // SFML set smooth default to true which leads to problems.

     width = raw.GetWidth();
     height = raw.GetHeight();


     {
          sf::Image tempImage(getTextureSize(raw.GetWidth()), 
                              getTextureSize(raw.GetHeight()),
                              sf::Color(0, 255, 0)
                              );
          tempImage.Copy(raw, 0, 0);
          tempImage.SetSmooth(false);
          raw = tempImage;
     }

     raw.CreateMaskFromColor(sf::Color(0, 255, 0)); // Color #00FF00 is used as transparence color.

     image.SetImage(raw);
     blitRect.x = 0;
     blitRect.y = 0;
     blitRect.w = getWidth();
     blitRect.h = getHeight();

         glGenTextures(1, &texture);
         glBindTexture(GL_TEXTURE_2D, texture);
         gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,
                           getRealWidth(), 
                           getRealHeight(),
                           GL_RGBA,GL_UNSIGNED_BYTE,
                           raw.GetPixelsPtr());
     return *this;
 }

/**
* \brief Operator () overloaded with filename
* \param filename : path to file
* \return Reference to the current Image instance.
*
* Changes or sets an image.
*/
jlug::Image& jlug::Image::operator()(const std::string& filename)
 {
     jlug::Image::operator=(filename);
     return *this;
 }

/**
* \brief Get the real width.
* \return width (first real inaccessible X-value)
*
* Gets the real width of the image and returns it.
*/
unsigned int jlug::Image::getRealWidth(void)
 {
     sf::Vector2f size = image.GetSize();
     return size.x;
 }

/**
* \brief Get the real height.
* \return height (first real inaccessible Y-value)
*
* Gets the real height of the image and returns it.
*/
unsigned int jlug::Image::getRealHeight(void)
 {
     sf::Vector2f size = image.GetSize();
     return size.y;
 }

/**
* \brief Get the real size.
* \return Rect with
*        w datafield as real width (first real inaccessible X-value)
*        h datafield as real height (first real inacessible Y-value)
*
* Gets the real size (real width, real height) of the image and returns it.
*/
jlug::Rect jlug::Image::getRealSize(void)
 {
     sf::Vector2f size = image.GetSize();
     jlug::Rect rect(0,0,0,0);
     rect.w = size.x;
     rect.h = size.y;
     return rect;
 }

/**
* \brief Get the width.
* \return width (first inaccessible X-value)
*
* Gets the width of the image and returns it.
*/
unsigned int jlug::Image::getWidth(void)
 {
     return width;
 }

/**
* \brief Get the height.
* \return height (first inaccessible Y-value)
*
* Gets the height of the image and returns it.
*/
unsigned int jlug::Image::getHeight(void)
 {
     return height;
 }

/**
* \brief Get the size.
* \return Rect with
*        w datafield as width (first inaccessible X-value)
*        h datafield as height (first inacessible Y-value)
*
* Gets the size (width, height) of the image and returns it.
*/
jlug::Rect jlug::Image::getSize(void)
 {
     jlug::Rect rect(0, 0, 0, 0);
     rect.w = width;
     rect.h = height;
     return rect;
 }

/**
* \brief Get the Blit Rect
* \return Rect containing the Blit Rect
*
* Returns the current Blit Rect which delimits the blit process.
*/
jlug::Rect jlug::Image::getBlitRect(void)
 {
     return blitRect;
 }

/**
* \brief Set the Blit Rect
* \param rect : new rect which will delimits the blit process.
*
* The methods checks if each datafield is correct and then affects them to the current blitRect or lets the current values.
*/
void jlug::Image::setBlitRect(const jlug::Rect& rect)
 {
     blitRect.x = (rect.x >= 0 && rect.x < static_cast<int>(getWidth())) ? rect.x : blitRect.x; // negative or superior to width rect.x is not allowed.
     blitRect.y = (rect.y >= 0 && rect.y < static_cast<int>(getHeight())) ? rect.y : blitRect.y; // negative or superior to height rect.y is not allowed.
     blitRect.w = (rect.w > 0 && rect.w <= static_cast<int>(getWidth())-blitRect.x) ? rect.w : blitRect.w; // negative or null or inferior to the left width rect.w is not allowed.
     blitRect.h = (rect.h > 0 && rect.h <= static_cast<int>(getHeight())-blitRect.y) ? rect.h : blitRect.h; // negative or null or inferior to the left height rect.h is not allowed.
 }

/**
* \brief Set the Blit Rect
* \param x : X position
* \param y : Y position
* \param w : width of the blit rect
* \param h : height of the blit rect
*
* Creates a jlug::Rect and calls setBlitRect(const jlug::Rect& rect);
*/
void jlug::Image::setBlitRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h)
 {
     jlug::Rect rect(x, y, w, h);
     setBlitRect(rect);
 }

GLuint& jlug::Image::getTexture(void)
{
     return texture;
}

/**
* \brief Set the alpha transparence
* \param alpha : alpha value. Must be between 0 and 1 as max possible values.
*
* Sets the alpha transparence.
*/
void jlug::Image::setAlpha(float alpha)
 {
    if (alpha >= 0.0 && alpha <= 1.0)
        image.SetColor(sf::Color(255, 255, 255, alpha*255));
 }


unsigned int jlug::Image::getTextureSize(unsigned int size)
 {
     unsigned int i(1);
     for (i = 1 ; i < size ; i <<= 1);
     return i;
 }
