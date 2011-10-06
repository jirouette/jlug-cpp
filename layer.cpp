#include "layer.hpp"

/**
* \brief Constructor
*/
jlug::Layer::Layer():
                tiles(), collisions(), opacity(1.0), visible(true), name("")
{}

/**
* \brief Destructor
* Nothing to do.
*/
jlug::Layer::~Layer(void)
{}

/**
* \brief set the opacity of the layer
* \param paramOpacity : opacity value. Between 0 and 1.
* \return return true if succeed, otherwise false.
*/
bool jlug::Layer::setOpacity(double paramOpacity)
{
    if (paramOpacity < 0.0 || paramOpacity > 1.0)
        return false;
    opacity = paramOpacity;
    return true;
}

/**
* \brief set the visible state of the layer.
* \param paramVisible : true = visible / false = not visible
* \return true
*/
bool jlug::Layer::setVisible(bool paramVisible)
{
    visible = paramVisible;
    return true;
}

/**
* \brief set the name of the layer
* \param paramName : new name
* \return true
*/
bool jlug::Layer::setName(const std::string& paramName)
{
    name = paramName;
    return true;
}

/**
* \brief clear the layer. All attributes returns to default values.
* \return true
*/
bool jlug::Layer::clear(void)
{
    tiles.clear();
    collisions.clear();
    opacity = 1.0;
    visible = true;
    name = "";
    return true;
}

/**
* \brief get the opacity of the layer
* \return opacity (between 0 and 1)
*/
double jlug::Layer::getOpacity(void)
{
    return opacity;
}

/**
* \brief say if the layer is visible
* \return true if visible, false if not visible
*/
bool jlug::Layer::isVisible(void)
{
    return visible;
}

/**
* \brief get the name of the layer
* \return name of the layer
*/
std::string jlug::Layer::getName(void)
{
    return name;
}

/**
* \brief get the GID of a tile
* \param x : X-position of the tile
* \param y : Y-position of the tile
* \return Value of the GID. If the tile does not exist or if the tile is forbidden, returns UINT_MAX or 0.
*/
unsigned int jlug::Layer::tile(unsigned int x, unsigned int y)
{
    unsigned int gid(UINT_MAX);
    try
    {
        gid = tiles.at(x).at(y);
    }
    catch (const std::exception& e)
    {
        // we don't care this exception.
        // but this means gid = UINT_MAX.
    }
    return gid;
}

/**
* \brief get the collision state of a tile
* \param x : X-position of the tile
* \param y : Y-position of the tile
* \return Value of the collision state.
* \bug This method does not work yet.
*/
jlug::Collision& jlug::Layer::collision(unsigned int x, unsigned int y)
{
    return collisions.at(x).at(y);
}


/**
* \brief set a GID to a tile
* \param x : X-position of the tile
* \param y : Y-position of the tile
* \param gid : new GID of the tile
* \return true
*
* Set a GID to a tile. If the tile does not exist, it is created.
*/
bool jlug::Layer::setTile(unsigned int x, unsigned int y, unsigned int gid)
{
    if (tiles.size() < (x+1)) // If row is not large enough, we resize it.
        tiles.resize(x+1);
    if (tiles[x].size() < (y+1)) // If column is not large enough, we resize it.
        tiles[x].resize(y+1, UINT_MAX); // We fill blank values created by resizing with UINT_MAX

    tiles[x][y] = gid;
    return true;
}

