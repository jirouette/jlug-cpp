#include "shape.hpp"

/**
* \file shape.cpp
* \author JirialMovie
*/

/**
* \brief Default constructor
* Default and only constructor
*/
jlug::Shape::Shape(void):texture(0)
{
    centerAxes.x = centerAxes.y = centerAxes.z = 0; // (0,0,0)
    color.x = color.y = color.z = 1; // white

    textureSize.x = textureSize.y = 0;
    textureSize.w = textureSize.h = 1;

    textureZone.x = textureZone.y = 0;
    textureZone.w = textureZone.h = 0;

    pixelTranslation.x = pixelTranslation.y = pixelTranslation.z = 1; // 1 vertex = 1 pixel
}

/**
* \brief Destructor
*/
jlug::Shape::~Shape(void)
{}

/**
* \brief saves a translation
* \param tAxes : translation in 3D
*/
void jlug::Shape::translate(const jlug::Point& tAxes)
{
    translate(tAxes.x, tAxes.y, tAxes.z);
}

/**
* \brief saves a rotation
* \param rAxes : rotation in 3D
*/
void jlug::Shape::rotate(const jlug::Point& rAxes)
{
    rotate(rAxes.x, rAxes.y, rAxes.z);
}

/**
* \brief saves a scaling
* \param sAxes : scaling in 3D
*/
void jlug::Shape::scale(const jlug::Point& sAxes)
{
    scale(sAxes.x, sAxes.y, sAxes.z);
}

/**
* \brief saves a translation
* \param x : X direction
* \param y : Y direction
* \param z : Z direction
*/
void jlug::Shape::translate(const double& x, const double& y, const double& z)
{
    jlug::Point tAxes;

    tAxes.x = x*pixelTranslation.x;
    tAxes.y = -y*pixelTranslation.y; // Y-axis is reversed
    tAxes.z = z*pixelTranslation.z;

    if (tAxes.x != 0 || tAxes.y != 0 || tAxes.z != 0) // saving
        transformations.push(std::pair<jlug::Shape::Transformation, jlug::Point>(jlug::Shape::TRANSLATION, tAxes));
}

/**
* \brief saves a rotation
* \param x : X direction
* \param y : Y direction
* \param z : Z direction
*/
void jlug::Shape::rotate(const double& x, const double& y, const double& z)
{
    jlug::Point rAxes;

    // We don't need pixelTranslation here. Rotation is... particular. 
    rAxes.x = x;
    rAxes.y = -y; // Y-axis is reversed
    rAxes.z = z;

    if (rAxes.x != 0 || rAxes.y != 0 || rAxes.z != 0)  // saving
        transformations.push(std::pair<jlug::Shape::Transformation, jlug::Point>(jlug::Shape::ROTATION, rAxes));
}

/**
* \brief saves a scaling
* \param x : X direction
* \param y : Y direction
* \param z : Z direction
*/
void jlug::Shape::scale(const double& x, const double& y, const double& z)
{
    jlug::Point sAxes;

    sAxes.x = x*pixelTranslation.x;
    sAxes.y = y*pixelTranslation.y; // We don't care if the Y-axis is reversed or not. 
    sAxes.z = z*pixelTranslation.z;

    if (sAxes.x != 0 || sAxes.y != 0 || sAxes.z != 0) // saving
        transformations.push(std::pair<jlug::Shape::Transformation, jlug::Point>(jlug::Shape::SCALING, sAxes));
}

/**
* \brief cancels and erases every stored transformation
*/
void jlug::Shape::cancelTransformations(void)
{
    while(!transformations.empty())
        transformations.pop();
}

/**
* \brief applies every stored transformations
*/
void jlug::Shape::applyTransformations(void)
{
    // At the beginning, we go to the center of the shape
     glTranslatef(centerAxes.x, centerAxes.y, centerAxes.z);

     // Then, we applies every transformations
     while(!transformations.empty())
     {
        std::pair<jlug::Shape::Transformation, jlug::Point> transformation(transformations.front()); // Getting the next value

        if (transformation.first == jlug::Shape::TRANSLATION)
            glTranslatef(transformation.second.x, transformation.second.y, transformation.second.z);
        else if (transformation.first == jlug::Shape::ROTATION)
        {
            // Even in the applying, Rotation is particular... 
            glRotatef(transformation.second.x, 1, 0, 0);
            glRotatef(transformation.second.y, 0, 1, 0);
            glRotatef(transformation.second.z, 0, 0, 1);
        }
        else if (transformation.first == jlug::Shape::SCALING)
            glScalef(transformation.second.x, transformation.second.y, transformation.second.z);

        transformations.pop(); // the applied transformation is erased
     }
}

/**
* \brief sets the initial position
* \param pAxes : 3D coordinates
*/
void jlug::Shape::setPosition(const jlug::Point& pAxes)
{
    setPosition(pAxes.x, pAxes.y, pAxes.z);
}

/**
* \brief sets the initial position
* \param x : X-coordinate
* \param y : Y-coordinate
* \param z : Z-coordinate
*/
void jlug::Shape::setPosition(const double& x, const double& y, const double& z)
{
    centerAxes.x = x;
    centerAxes.y = -y; // Y-Axis is reversed ! 
    centerAxes.z = z;
}

/**
* \brief get the initial position
* \return initial position in a Rect
*/
jlug::Point jlug::Shape::getPosition(void)
{
    return centerAxes;
}

/**
* \brief sets color
* \param colors : color
*/
void jlug::Shape::setColor(const jlug::Point& colors)
{
    setColor(colors.x, colors.y, colors.z);
}

/**
* \brief sets color
* \param r : red-color
* \param g : green-color
* \param b : blue-color
*/
void jlug::Shape::setColor(const double& r, const double& g, const double& b)
{
    color.x = r/255.0;
    color.y = g/255.0;
    color.z = b/255.0;
}

/**
* \brief get the color
* \return color in a Point (x is r, y is g, z is b)
*/
jlug::Point jlug::Shape::getColor(void)
{
    return color;
}

/**
* \brief sets the OpenGL's texture ID
* \param id : OpenGL's texture
*/
void jlug::Shape::setTexture(GLuint id)
{
    texture = id;
}

/**
* \brief get the OpenGL's texture ID
* \return OpenGL's texture ID
*/
GLuint jlug::Shape::getTexture(void)
{
    return texture;
}

/**
* \brief sets the size of the texture source
* \param size : well... Y U NO UNDERSTAND "SIZE" ? 
*/
void jlug::Shape::setTextureSize(const jlug::Rectangle<double>& size)
{
    setTextureSize(size.x, size.y, size.w, size.h);
}

/**
* \brief sets the size of the texture source
* \param x : X-coordinates (usually 0)
* \param y : Y-coordinates (usually 0)
* \param w : width
* \param h : height
*/
void jlug::Shape::setTextureSize(const double& x, const double& y, const double& w, const double& h)
{
    textureSize.x = x;
    textureSize.y = y;
    textureSize.w = w;
    textureSize.h = h;
}

/**
* \brief get the size of the texture source
* \return texture size
*/
jlug::Rectangle<double> jlug::Shape::getTextureSize(void)
{
    return textureSize;
}

/**
* \brief sets the zone of the wanted texture
* \param zone : size and coordinates in the texture source
*/
void jlug::Shape::setTextureZone(const jlug::Rectangle<double>& zone)
{
    setTextureSize(zone.x, zone.y, zone.w, zone.h);
}

/**
* \brief sets the zone of the wanted texture
* \param x : X-coordinates in the texture source
* \param y : Y-coordinates in the texture source
* \param w : Width
* \param h : Height
*/
void jlug::Shape::setTextureZone(const double& x, const double& y, const double& w, const double& h)
{
    textureZone.x = x;
    textureZone.y = y;
    textureZone.w = w;
    textureZone.h = h;
}

/**
* \brief get the zone of the wanted texture
* \return texture zone
*/
jlug::Rectangle<double> jlug::Shape::getTextureZone(void)
{
    return textureZone;
}

/**
* \brief sets the translations between pixels and vertex
* \param x : X-translation
* \param y : Y-translation
*/
void jlug::Shape::setPixelTranslation(double x, double y)
{
    pixelTranslation.x = 1.0/x;
    pixelTranslation.y = 1.0/y;
    pixelTranslation.z = 1.0/((x+y)/2.0);
}

/**
* \brief get the pixel/vertex translation
* \return Point
*/
jlug::Point jlug::Shape::getPixelTranslation(void)
{
    return pixelTranslation;
}
