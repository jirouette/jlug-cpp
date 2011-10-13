#include "map.hpp"

/**
* \brief Constructor
* \param imageM : reference to the ImageManager instance.
*
* Initialize everything to default.
*/
jlug::Map::Map(void):
                width(0), height(0), tileWidth(0), tileHeight(0),
                xscroll(0), yscroll(0), tilesets(), gidRects(), 
                gidTilesets(), mapFilename(""), layers(), weather(NORMAL)
{}

/**
* \brief Constructor
* \param filename : path to map file
* \param imageM : reference to the ImageManager instance.
*
* Initialize everything to default and then, load the map.
*/
jlug::Map::Map(const std::string& filename):
                width(0), height(0), tileWidth(0), tileHeight(0),
                xscroll(0), yscroll(0), tilesets(), gidRects(), 
                gidTilesets(), mapFilename(filename), layers(), weather(NORMAL)
{
    loadMap(mapFilename);
}

/**
* \brief Destructor
* Nothing to do.
*/
jlug::Map::~Map(void)
{}

/**
* \brief load a map
* \param filename : path to map file
* \return true
*/
bool jlug::Map::loadMap(const std::string& filename)
{
    TmxFile tmx(filename); // We use TmxFile to generate a map
    jlug::Rect mapSize = tmx.getMapSize();
    jlug::Rect tileSize = tmx.getTileSize();
    jlug::Tileset* tilesetSize;
    std::vector<jlug::Tileset>::iterator it;
    unsigned int i(0), max(0);

    width = mapSize.w;
    height = mapSize.h;
    tileWidth = tileSize.w;
    tileHeight = tileSize.h;

    layers = tmx.getLayers();
    tilesets = tmx.getTilesets();

    // Then, we fill our attributes with TmxFile datas.

    // Pre-calculate Rect in tileset for each GID value :

    gidRects.push_back(tileSize); // dummy value for GID=0 ( GID = 0 is unused because firstgid must be > 1 )

    for (it = tilesets.begin() ; it != tilesets.end() ; ++it)
    {
        max = it->firstgid + (it->width/tileWidth)*(it->height/tileHeight);
        for(i = it->firstgid ; i < max ; i++)
        {
            tilesetSize = getTilesetByGid(i);
            gidTilesets.push_back(tilesetSize);
            gidRects.push_back(getRectByGid(i, tilesetSize));

        }
    }
    return true;
}

/**
* \brief get layers of the map
* \return reference to layers
*/
std::vector<jlug::Layer>& jlug::Map::getLayers(void)
{
    return layers;
}

/**
* \brief get number of layers
* \return number of layers
*/
unsigned int jlug::Map::getLayersSize(void)
{
    return layers.size();
}

/**
* \brief set width of the map in tiles
* \param paramWidth : new width of the map in tiles
* \return true if paramWidth positive, false otherwise.
*/
bool jlug::Map::setWidth(unsigned int paramWidth)
{
    if (paramWidth <= 0)
        return false;
    width = paramWidth;
    return true;
}

/**
* \brief set height of the map in tiles
* \param paramHeight : new height of the map in tiles
* \return true if paramHeight positive, false otherwise.
*/
bool jlug::Map::setHeight(unsigned int paramHeight)
{
    if (paramHeight <= 0)
        return false;
    height = paramHeight;
    return true;
}

/**
* \brief set width and height of the map in tiles
* \param paramWidth : new width of the map in tiles
* \param paramHeight : new height of the map in tiles
* \return true if paramWidth and paramHeight positive, false otherwise.
*/
bool jlug::Map::setSize(unsigned int paramWidth, unsigned int paramHeight)
{
    if (paramWidth <= 0 || paramHeight <= 0)
        return 0;
    width = paramWidth;
    height = paramHeight;
    return true;
}

/**
* \brief set width and height of the map in tiles
* \param size : new width and new height of the map in tiles
* \return true if new width and new height positive, false otherwise.
*/
bool jlug::Map::setSize(jlug::Rect size)
{
    if ((size.w <= 0 && size.x <= 0) || (size.h <= 0 && size.y <= 0))
        return false;
    width = (size.w <= 0) ? size.x : size.w;
    height = (size.h <= 0) ? size.y : size.h;
    return true;
}

/**
* \brief set width of tiles in pixels
* \param paramTileWidth : new width of tiles in pixels
* \return true if paramTileWidth positive, false otherwise.
*/
bool jlug::Map::setTileWidth(unsigned int paramTileWidth)
{
    if (paramTileWidth <= 0)
        return false;
    tileWidth = paramTileWidth;
    return true;
}

/**
* \brief set height of tiles in pixels
* \param paramTileHeight : new height of tiles in pixels
* \return true if paramTileHeight positive, false otherwise.
*/
bool jlug::Map::setTileHeight(unsigned int paramTileHeight)
{
    if (paramTileHeight <= 0)
        return false;
    tileHeight = paramTileHeight;
    return true;
}

/**
* \brief set width and height of tiles in pixels
* \param paramTileWidth : new width of tiles in pixels
* \param paramTileHeight : new height of tiles in pixels
* \return true if paramTileWidth and paramTileHeight positive, false otherwise.
*/
bool jlug::Map::setTileSize(unsigned int paramTileWidth, unsigned int paramTileHeight)
{
    if (paramTileWidth <= 0 || paramTileHeight <= 0)
        return false;
    tileWidth = paramTileWidth;
    tileHeight = paramTileHeight;
    return true;
}

/**
* \brief set width and height of tiles in pixels
* \param tileSize : new width and new height of tiles in pixels
* \return true if new width and new height positive, false otherwise.
*/
bool jlug::Map::setTileSize(jlug::Rect tileSize)
{
    if ((tileSize.x <= 0 && tileSize.w <= 0) || (tileSize.y <= 0 && tileSize.h <= 0))
        return false;
    tileWidth = (tileSize.w <= 0) ? tileSize.x : tileSize.w;
    tileHeight = (tileSize.h <= 0) ? tileSize.y : tileSize.h;
    return true;
}

/**
* \brief set X-position and Y-position of the scroll
* \param x : new X-position scroll
* \param y : new Y-position scroll
* \return boolean
*/

bool jlug::Map::setScroll(int x, int y)
 {
    xscroll = x;//(x > 0) ? x : 0;
    yscroll = y;//(y > 0) ? y : 0;
     return true;
 }


bool jlug::Map::setCamera(int x, int y)
{
    gluLookAt(x-5, y+2, 5, x-5, y, 0, 0, 1, 0);
     return true;
}


/**
* \brief get width of the map in tiles
* \return width of the map in tiles
*/
unsigned int jlug::Map::getWidth(void)
{
    return width;
}

/**
* \brief get height of the map in tiles
* \return height of the map in tiles
*/
unsigned int jlug::Map::getHeight(void)
{
    return height;
}

/**
* \brief get width and height of the map in tiles
* \return width and height of the map in tiles
*/
jlug::Rect jlug::Map::getSize(void)
{
    jlug::Rect size;
    size.x = 0;
    size.y = 0;
    size.w = width;
    size.h = height;
    return size;
}

/**
* \brief get width of tiles in pixels
* \return width of tiles in pixels
*/
unsigned int jlug::Map::getTileWidth(void)
{
    return tileWidth;
}

/**
* \brief get height of tiles in pixels
* \return height of tiles in pixels
*/
unsigned int jlug::Map::getTileHeight(void)
{
    return tileHeight;
}

/**
* \brief get width and height of tiles in pixels
* \return width and height of tiles in pixels
*/
jlug::Rect jlug::Map::getTileSize(void)
{
    jlug::Rect tileSize;
    tileSize.x = 0;
    tileSize.y = 0;
    tileSize.w = tileWidth;
    tileSize.h = tileHeight;
    return tileSize;
}

/**
* \brief get the current position of the scroll
* \return position of the scroll in a rect
*/

jlug::Rect jlug::Map::getScroll(void)
 {
     jlug::Rect scroll;
     scroll.x = xscroll;
     scroll.y = yscroll;
     scroll.w = 0;
     scroll.h = 0;
     return scroll;
 }

/**
* \brief get pointer to tileset by GID
* \param gid : gid of tile in the tileset we're looking for
* \return pointer to tileset
*/
jlug::Tileset* jlug::Map::getTilesetByGid(unsigned int gid)
 {
     std::vector<jlug::Tileset>::iterator it;
     jlug::Tileset* tileset = &(tilesets[0]);
     for(it = tilesets.begin() ; it != tilesets.end() ; ++it)
     {
        if (it->firstgid <= static_cast<int>(gid))
            tileset = &(*it);
        else if (it->firstgid > static_cast<int>(gid))
            return tileset;
     }
     return tileset;
 }

/**
* \brief calculate position of tile by gid and tileset
* \param gid : gid of a tile
* \param tileset : tileset of the same tile
* \return position of the tile
*/
jlug::Rect jlug::Map::getRectByGid(unsigned int gid, const jlug::Tileset* tileset)
{
    jlug::Rect rect = {0, 0, tileWidth, tileHeight};
    unsigned int realGid = gid - tileset->firstgid;

    rect.x = realGid%(tileset->width/tileWidth);
    rect.y = realGid/(tileset->width/tileWidth);

    return rect;
}

/**
* \brief display tiles from a layer to the screen
* \param win : window where we will draw
* \param index : index of the layer whose tiles will be displayed
* \return true
*/
bool jlug::Map::displayLayer(jlug::Window& win, int index)
{
    //jlug::Image tile;
    jlug::Tileset* tileset;
    std::string previousFilename("");
    jlug::Square square;

    const int MAXW((xscroll+win.getWidth())/tileWidth);
    const int MAXH((yscroll+win.getHeight())/tileHeight);
    unsigned int gid(0);
    //tile.setAlpha(layers[index].getOpacity());

    square.setPixelTranslation(tileWidth, tileHeight);


    for (int j(yscroll/tileHeight);j<MAXH;++j)
        for(int i(xscroll/tileWidth);i<MAXW;++i)
        {
            if (i < 0 || j < 0) // there is no negative tiles
                gid = 0;
            else
                gid = layers[index].tile(i, j);

            if (gid != UINT_MAX && gid != 0) // UINT_MAX and 0 mean that the tile does not exist or must not be displayed.
            {
                jlug::Image& tile(jlug::ImageManager::getInstance()[gidTilesets[gid]->filename]);
                tileset = gidTilesets[gid];

                square.setPosition(i, j, index*0.011);
                //square.setColor(255, 0, 0);

                square.setTexture(jlug::ImageManager::getInstance().getTexture(tileset->filename));
                square.setTextureSize(0, 0, tile.getRealWidth(), tile.getRealHeight());
                square.setTextureZone(gidRects[gid].x*tileWidth, gidRects[gid].y*tileHeight, tileWidth, tileHeight);

                square.draw();
            }
        }

    return true;
}
