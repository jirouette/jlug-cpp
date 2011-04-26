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
jlug::Image::Image(const sf::Image& img)
 {
     image.SetImage(img);
     blitRect.x = 0;
     blitRect.y = 0;
     blitRect.w = getWidth();
     blitRect.h = getHeight();
 }

/**
* \brief Default constructor
*
* Creates an empty Image with default blitRect.
*/
jlug::Image::Image(void)
            :image(), blitRect()
 {}

/**
* \brief Destructor
*
* Nothing to do.
*/
jlug::Image::~Image()
{}


/**
* \brief Operator = overloaded with graphic library's type variable
* \param img : Reference to a constant graphic library's type variable.
* \return Reference to the current Image instance.
*
* Changes or sets an image.
*/
jlug::Image& jlug::Image::operator=(const sf::Image& img)
 {
     image.SetSubRect(sf::IntRect(0, 0, img.GetWidth(), img.GetHeight()));
     // To avoid some problems, it is better to changes the SubRect before setting the image.
     image.SetImage(img);
     blitRect.x = 0;
     blitRect.y = 0;
     blitRect.w = getWidth();
     blitRect.h = getHeight();
     return *this;
 }

/**
* \brief Get the width.
* \return width (first inaccessible X-value)
*
* Gets the width of the image and returns it.
*/
unsigned int jlug::Image::getWidth(void)
 {
     sf::Vector2f size = image.GetSize();
     return size.x;
 }

/**
* \brief Get the height.
* \return height (first inaccessible Y-value)
*
* Gets the height of the image and returns it.
*/
unsigned int jlug::Image::getHeight(void)
 {
     sf::Vector2f size = image.GetSize();
     return size.y;
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
     sf::Vector2f size = image.GetSize();
     jlug::Rect rect = {0, 0, 0, 0};
     rect.w = size.x;
     rect.h = size.y;
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
     blitRect.x = (rect.x >= 0 && rect.x < getWidth()) ? rect.x : blitRect.x; // negative or superior to width rect.x is not allowed.
     blitRect.y = (rect.y >= 0 && rect.y < getHeight()) ? rect.y : blitRect.y; // negative or superior to height rect.y is not allowed.
     blitRect.w = (rect.w > 0 && rect.w <= getWidth()-blitRect.x) ? rect.w : blitRect.w; // negative or null or inferior to the left width rect.w is not allowed.
     blitRect.h = (rect.h > 0 && rect.h <= getHeight()-blitRect.y) ? rect.h : blitRect.h; // negative or null or inferior to the left height rect.h is not allowed.
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
     jlug::Rect rect = {x, y, w, h};
     setBlitRect(rect);
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
