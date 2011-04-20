#include "layer.hpp"


jlug::Layer::Layer(unsigned int paramWidth, unsigned int paramHeight, unsigned int paramTileWidth, unsigned int paramTileHeight):
                width(paramWidth), height(paramHeight), tileWidth(paramTileWidth), tileHeight(paramTileHeight),
                tilesets(), tilesetsSizes(), tiles(), collisions(), opacity(1.0), visible(true), name("")
{}

jlug::Layer::~Layer(void)
{}

bool jlug::Layer::setWidth(unsigned int paramWidth)
{
    if (paramWidth <= 0)
        return false;
    width = paramWidth;
    return true;
}

bool jlug::Layer::setHeight(unsigned int paramHeight)
{
    if (paramHeight <= 0)
        return false;
    height = paramHeight;
    return true;
}

bool jlug::Layer::setSize(unsigned int paramWidth, unsigned int paramHeight)
{
    if (paramWidth <= 0 || paramHeight <= 0)
        return 0;
    width = paramWidth;
    height = paramHeight;
    return true;
}

bool jlug::Layer::setSize(jlug::Rect size)
{
    if ((size.w <= 0 && size.x <= 0) || (size.h <= 0 && size.y <= 0))
        return false;
    width = (size.w <= 0) ? size.x : size.w;
    height = (size.h <= 0) ? size.y : size.h;
    return true;
}

bool jlug::Layer::setTileWidth(unsigned int paramTileWidth)
{
    if (paramTileWidth <= 0)
        return false;
    tileWidth = paramTileWidth;
    return true;
}

bool jlug::Layer::setTileHeight(unsigned int paramTileHeight)
{
    if (paramTileHeight <= 0)
        return false;
    tileHeight = paramTileHeight;
    return true;
}

bool jlug::Layer::setTileSize(unsigned int paramTileWidth, unsigned int paramTileHeight)
{
    if (paramTileWidth <= 0 || paramTileHeight <= 0)
        return false;
    tileWidth = paramTileWidth;
    tileHeight = paramTileHeight;
    return true;
}

bool jlug::Layer::setTileSize(jlug::Rect tileSize)
{
    if ((tileSize.x <= 0 && tileSize.w <= 0) || (tileSize.y <= 0 && tileSize.h <= 0))
        return false;
    tileWidth = (tileSize.w <= 0) ? tileSize.x : tileSize.w;
    tileHeight = (tileSize.h <= 0) ? tileSize.y : tileSize.h;
    return true;
}

bool jlug::Layer::setOpacity(double paramOpacity)
{
    if (paramOpacity < 0 || paramOpacity > 1)
        return false;
    opacity = paramOpacity;
    return true;
}

bool jlug::Layer::setVisible(bool paramVisible)
{
    visible = paramVisible;
    return true;
}

bool jlug::Layer::setName(const std::string& paramName)
{
    name = paramName;
    return true;
}




unsigned int jlug::Layer::getWidth(void)
{
    return width;
}

unsigned int jlug::Layer::getHeight(void)
{
    return height;
}

jlug::Rect jlug::Layer::getSize(void)
{
    jlug::Rect size;
    size.x = 0;
    size.y = 0;
    size.w = width;
    size.h = height;
    return size;
}

unsigned int jlug::Layer::getTileWidth(void)
{
    return tileWidth;
}

unsigned int jlug::Layer::getTileHeight(void)
{
    return tileHeight;
}

jlug::Rect jlug::Layer::getTileSize(void)
{
    jlug::Rect tileSize;
    tileSize.x = 0;
    tileSize.y = 0;
    tileSize.w = tileWidth;
    tileSize.h = tileHeight;
    return tileSize;
}

double jlug::Layer::getOpacity(void)
{
    return opacity;
}

bool jlug::Layer::isVisible(void)
{
    return visible;
}

std::string jlug::Layer::getName(void)
{
    return name;
}


unsigned int& jlug::Layer::tile(unsigned int x, unsigned int y)
{
    return tiles.at(x).at(y);
}

jlug::Collision& jlug::Layer::collision(unsigned int x, unsigned int y)
{
    return collisions.at(x).at(y);
}






std::ostream& jlug::operator<< (std::ostream& flux, jlug::Layer& layer)
{
     layer.getWidth();
     flux << "Layer \"" << layer.name << "\". " << std::endl;
     flux << "size = (" << layer.width << ", " << layer.height << "). " << std::endl;
     flux << "tileSize = (" << layer.tileWidth << ", " << layer.tileHeight << "). " << std::endl;
     flux << ((layer.visible) ? "Visible. " : "Not visible. ") << std::endl;
     flux << "Opacity = " << layer.opacity << std::endl;
     return flux;
}
