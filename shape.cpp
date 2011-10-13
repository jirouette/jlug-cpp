#include "shape.hpp"

jlug::Shape::Shape(void):texture(0)
{
    centerAxes.x = centerAxes.y = centerAxes.z = 0;
    color.x = color.y = color.z = 1;

    textureSize.x = textureSize.y = 0;
    textureSize.w = textureSize.h = 1;

    textureZone.x = textureZone.y = 0;
    textureZone.w = textureZone.h = 0;

    pixelTranslation.x = pixelTranslation.y = pixelTranslation.z = 1;
}

jlug::Shape::~Shape(void)
{}

void jlug::Shape::translate(const jlug::Point& tAxes)
{
    translate(tAxes.x, tAxes.y, tAxes.z);
}

void jlug::Shape::rotate(const jlug::Point& rAxes)
{
    rotate(rAxes.x, rAxes.y, rAxes.z);
}

void jlug::Shape::scale(const jlug::Point& sAxes)
{
    scale(sAxes.x, sAxes.y, sAxes.z);
}

void jlug::Shape::translate(const double& x, const double& y, const double& z)
{
    jlug::Point tAxes;

    tAxes.x = x*pixelTranslation.x;
    tAxes.y = -y*pixelTranslation.y;
    tAxes.z = z*pixelTranslation.z;

    transformations.push(std::pair<jlug::Shape::Transformation, jlug::Point>(jlug::Shape::TRANSLATION, tAxes));
}

void jlug::Shape::rotate(const double& x, const double& y, const double& z)
{
    jlug::Point rAxes;

    rAxes.x = x;//*pixelTranslation.x;
    rAxes.y = -y;//*pixelTranslation.y;
    rAxes.z = z;//*pixelTranslation.z;

    transformations.push(std::pair<jlug::Shape::Transformation, jlug::Point>(jlug::Shape::ROTATION, rAxes));
}

void jlug::Shape::scale(const double& x, const double& y, const double& z)
{
    jlug::Point sAxes;

    sAxes.x = x*pixelTranslation.x;
    sAxes.y = y*pixelTranslation.y;
    sAxes.z = z*pixelTranslation.z;

    transformations.push(std::pair<jlug::Shape::Transformation, jlug::Point>(jlug::Shape::SCALING, sAxes));
}

void jlug::Shape::cancelTransformations(void)
{
    while(!transformations.empty())
        transformations.pop();
}

void jlug::Shape::applyTransformations(void)
{
     glTranslatef(centerAxes.x, centerAxes.y, centerAxes.z);

     while(!transformations.empty())
     {
        std::pair<jlug::Shape::Transformation, jlug::Point> transformation(transformations.front()); // Getting the next value

        if (transformation.first == jlug::Shape::TRANSLATION)
            glTranslatef(transformation.second.x, transformation.second.y, transformation.second.z);
        else if (transformation.first == jlug::Shape::ROTATION)
        {
            glRotatef(transformation.second.x, 1, 0, 0);
            glRotatef(transformation.second.y, 0, 1, 0);
            glRotatef(transformation.second.z, 0, 0, 1);
        }
        else if (transformation.first == jlug::Shape::SCALING)
            glScalef(transformation.second.x, transformation.second.y, transformation.second.z);

        transformations.pop();
     }
}

void jlug::Shape::setPosition(const jlug::Point& pAxes)
{
    setPosition(pAxes.x, pAxes.y, pAxes.z);
}

void jlug::Shape::setPosition(const double& x, const double& y, const double& z)
{
    centerAxes.x = x;//*pixelTranslation.x;
    centerAxes.y = -y;//*pixelTranslation.y;
    centerAxes.z = z;//*pixelTranslation.z;
}

jlug::Point jlug::Shape::getPosition(void)
{
    return centerAxes;
}

void jlug::Shape::setColor(const jlug::Point& colors)
{
    setColor(colors.x, colors.y, colors.z);
}

void jlug::Shape::setColor(const double& r, const double& g, const double& b)
{
    color.x = r/255.0;
    color.y = g/255.0;
    color.z = b/255.0;
}

jlug::Point jlug::Shape::getColor(void)
{
    return color;
}

void jlug::Shape::setTexture(GLuint id)
{
    texture = id;
}

GLuint jlug::Shape::getTexture(void)
{
    return texture;
}

void jlug::Shape::setTextureSize(const jlug::Rectangle<double>& size)
{
    setTextureSize(size.x, size.y, size.w, size.h);
}

void jlug::Shape::setTextureSize(const double& x, const double& y, const double& w, const double& h)
{
    textureSize.x = x;
    textureSize.y = y;
    textureSize.w = w;
    textureSize.h = h;
}

jlug::Rectangle<double> jlug::Shape::getTextureSize(void)
{
    return textureSize;
}

void jlug::Shape::setTextureZone(const jlug::Rectangle<double>& zone)
{
    setTextureSize(zone.x, zone.y, zone.w, zone.h);
}

void jlug::Shape::setTextureZone(const double& x, const double& y, const double& w, const double& h)
{
    textureZone.x = x;
    textureZone.y = y;
    textureZone.w = w;
    textureZone.h = h;
}

jlug::Rectangle<double> jlug::Shape::getTextureZone(void)
{
    return textureZone;
}

void jlug::Shape::setPixelTranslation(double x, double y)
{
    pixelTranslation.x = 1.0/x;
    pixelTranslation.y = 1.0/y;
    pixelTranslation.z = 1.0/((x+y)/2.0);
}

jlug::Point jlug::Shape::getPixelTranslation(void)
{
    return pixelTranslation;
}
