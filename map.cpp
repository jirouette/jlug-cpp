#include "map.hpp"

jlug::Map::Map(void):xscroll(0), yscroll(0), tileWidth(16), tileHeight(16), mapFilename(""), weather(jlug::NORMAL), map()
{}

jlug::Map::Map(const std::string& filename):xscroll(0), yscroll(0), tileWidth(16), tileHeight(16), mapFilename(filename), weather(jlug::NORMAL), map()
{
    loadMap(mapFilename);
}

jlug::Map::~Map(void)
{}

void jlug::Map::loadMap(const std::string& filename)
{
    mapFilename = filename;
    map.ParseFile(filename);

    for (int z(0) ; z < map.GetNumLayers() ; ++z)
    {
        const Tmx::Layer *layer(map.GetLayer(z));
        if (layer)
        {
            for (int x(0) ; x < layer->GetWidth() ; ++x)
                for (int y(0) ; y < layer->GetHeight() ; ++y)
                {
                        createTile(x,y,z, layer->GetTileGid(x, y));
                }
            
            if (!layer->GetProperties().Empty())
                setTransformations(z, layer->GetProperties().GetLiteralProperty("transformations"));
        }
    }
}

unsigned int jlug::Map::getTileWidth(void)
{
    return map.GetTileWidth();
}

unsigned int jlug::Map::getTileHeight(void)
{
    return map.GetTileHeight();
}

unsigned int jlug::Map::getWidth(void)
{
    return map.GetWidth();
}

unsigned int jlug::Map::getHeight(void)
{
    return map.GetHeight();
}

unsigned int jlug::Map::getDepth(void)
{
    return map.GetNumLayers();
}

jlug::Rect jlug::Map::getScroll(void)
{
    return jlug::Rect(xscroll, yscroll, xscroll, yscroll);
}

void jlug::Map::createTile(unsigned int x, unsigned int y, unsigned int z, unsigned int gid)
{
    jlug::TileProp tile;

    setTile(tile, gid);

    if (tiles.size() <= x)
        tiles.resize(x+1);
    
    if (tiles[x].size() <= y)
        tiles[x].resize(y+1);
    
    if (tiles[x][y].size() <= z)
        tiles[x][y].resize(z+1);
    
    tiles[x][y][z] = tile;
}

/**
* \brief set X-position and Y-position of the scroll
* \param x : new X-position scroll
* \param y : new Y-position scroll
* \return boolean
*/

void jlug::Map::setScroll(int x, int y)
 {
    xscroll = (x > 0) ? x : 0;
    yscroll = (y > 0) ? y : 0;
 }


void jlug::Map::setCamera(int x, int y)
{
    gluLookAt(x-5, y+2, 5, x-5, y, 0, 0, 1, 0);
}

void jlug::Map::initTile(TileProp& tile)
{
    tile.gid = 0;
    tile.image = 0;
    tile.texture = 0;
    tile.limit = jlug::Rectangle<double>();

    tile.collision = jlug::WALKABLE;
    tile.scaling = jlug::Point();
    tile.rotation = jlug::Point();
    tile.translation = jlug::Point();
    tile.translationAfterRotation = jlug::Point();

    tile.upperLeftCorner = jlug::Point(0.0, 1.0, 0.0);
    tile.upperRightCorner = jlug::Point(1.0, 1.0, 0.0);
    tile.downerLeftCorner = jlug::Point(0.0, 0.0, 0.0);
    tile.downerRightCorner = jlug::Point(1.0, 0.0, 0.0);
}

void jlug::Map::setTile(TileProp& tile, unsigned int gid)
{
    initTile(tile);
    tile.gid = gid;
    for (int i(0) ; i < map.GetNumTilesets() ; ++i)
    {
        const Tmx::Tileset *tileset(map.GetTileset(i));
        if (tileset)
        {
            if (tileset->GetFirstGid() <= static_cast<int>(tile.gid))
            {
                const Tmx::Image *img(tileset->GetImage());
                if (img)
                {
                    tile.image = &(ImageManager::getInstance()[img->GetSource()]);
                    tile.texture = ImageManager::getInstance().getTexture(img->GetSource());
                    tile.limit.x = (static_cast<int>(tile.gid) - tileset->GetFirstGid()) % (tile.image->getWidth() / tileset->GetTileWidth());
                    tile.limit.y = (static_cast<int>(tile.gid) - tileset->GetFirstGid()) / (tile.image->getWidth() / tileset->GetTileWidth());
                    tile.limit.w = tileset->GetTileWidth();
                    tile.limit.h = tileset->GetTileHeight();

                    tile.limit.x *= tile.limit.w;
                    tile.limit.y *= tile.limit.h;
                }
            }
        }
    }
}

void jlug::Map::setTransformations(unsigned int layer, const std::string& objectLayerName)
{
    const Tmx::ObjectGroup *objectLayer(0);

    for (int i(0); i < map.GetNumObjectGroups(); ++i)
    {
        const Tmx::ObjectGroup *currentObjectLayer = map.GetObjectGroup(i);
        if (currentObjectLayer)
            if(currentObjectLayer->GetName() == objectLayerName)
            {
                objectLayer = currentObjectLayer;
                break;
            }
    }

    if (!objectLayer)
        return;
    
    for (int i(0); i < objectLayer->GetNumObjects() ; ++i)
    {
        const Tmx::Object *object = objectLayer->GetObject(i);
        const Tmx::Tileset *tileset(map.GetTileset(0));
        if (object && tileset)
            if(!object->GetProperties().Empty())
            {
                jlug::Rect selectedTiles(object->GetX()/tileset->GetTileWidth(),
                                         object->GetY()/tileset->GetTileHeight(),
                                         (object->GetX()+object->GetWidth())/tileset->GetTileWidth(),
                                         (object->GetY()+object->GetHeight())/tileset->GetTileHeight());
                if (object->GetType() == "transform")
                    setTransformation(layer, selectedTiles, object->GetProperties().GetList());
                else if (object->GetType() == "modifyVertex")
                    setVertex(layer, selectedTiles, object->GetProperties().GetList(), false);
                else if (object->GetType() == "addVertex")
                    setVertex(layer, selectedTiles, object->GetProperties().GetList(), true);
            }
    }
}

void jlug::Map::setTransformation(unsigned int layer, const jlug::Rect& selectedTiles, const std::map<std::string, std::string>& properties)
{
    std::map<std::string, std::string>::const_iterator it;

    /* Disclaimer : 
    *  I know that the following lines are absolutely ugly
    *  However, I do not think that using only 2 "for"
    *  and then, call std::map.find is a really better idea... 
    *  Don't forget that properties can have so many values
    *  even if I don't use all of them... 
    */

    it = properties.find("rotation");

    if (it == properties.end())
        it = properties.find("rotate");

    if (it != properties.end())
    {
        for (int i(selectedTiles.x) ; i < selectedTiles.w ; ++i)
            for (int j(selectedTiles.y) ; j < selectedTiles.h ; ++j)
                setRotation(tiles[i][j][layer], 
                            /*jlug::Point(i, j, layer), 
                            jlug::Point(selectedTiles.x+selectedTiles.w,
                                        selectedTiles.y+selectedTiles.h,
                                        layer),*/
                            it->second);
    }

    it = properties.find("translation");

    if (it == properties.end())
        it = properties.find("translate");
    
    if (it != properties.end())
    {
        for (int i(selectedTiles.x) ; i < selectedTiles.w ; ++i)
            for (int j(selectedTiles.y) ; j < selectedTiles.h ; ++j)
                addToPoint(tiles[i][j][layer].translation, it->second);
    }

    it = properties.find("scaling");

    if (it == properties.end())
        it = properties.find("scale");
    
    if (it != properties.end())
    {
        for (int i(selectedTiles.x) ; i < selectedTiles.w ; ++i)
            for (int j(selectedTiles.y) ; j < selectedTiles.h ; ++j)
                addToPoint(tiles[i][j][layer].scaling, it->second);
    }

}


void jlug::Map::setVertex(unsigned int layer, const jlug::Rect& selectedTiles, const std::map<std::string, std::string>& properties, bool add)
{
    std::map<std::string, std::string>::const_iterator it;

    /* Disclaimer : 
    *  I know that the following lines are absolutely ugly
    *  However, I do not think that using only 2 "for"
    *  and then, call std::map.find is a really better idea... 
    *  Don't forget that properties can have so many values
    *  even if I don't use all of them... 
    */

    it = properties.find("all");

    if (it != properties.end())
        for (int i(selectedTiles.x); i < selectedTiles.w ; ++i)
            for (int j(selectedTiles.y) ; j < selectedTiles.h ; ++j)
                if (add)
                {
                    addToPoint(tiles[i][j][layer].upperLeftCorner, it->second);
                    addToPoint(tiles[i][j][layer].upperRightCorner, it->second);
                    addToPoint(tiles[i][j][layer].downerLeftCorner, it->second);
                    addToPoint(tiles[i][j][layer].downerRightCorner, it->second);
                }
                else
                {
                    setPoint(tiles[i][j][layer].upperLeftCorner, it->second);
                    setPoint(tiles[i][j][layer].upperRightCorner, it->second);
                    setPoint(tiles[i][j][layer].downerLeftCorner, it->second);
                    setPoint(tiles[i][j][layer].downerRightCorner, it->second);
                }

    it = properties.find("upperLeft");

    if (it == properties.end())
        it = properties.find("UL");

    if (it != properties.end())
        for (int i(selectedTiles.x); i < selectedTiles.w ; ++i)
            for (int j(selectedTiles.y) ; j < selectedTiles.h ; ++j)
                if (add)
                    addToPoint(tiles[i][j][layer].upperLeftCorner, it->second);
                else
                    setPoint(tiles[i][j][layer].upperLeftCorner, it->second);


    it = properties.find("upperRight");

    if (it == properties.end())
        it = properties.find("UR");
    
    if (it != properties.end())
        for (int i(selectedTiles.x); i < selectedTiles.w ; ++i)
            for (int j(selectedTiles.y) ; j < selectedTiles.h ; ++j)
                if (add)
                    addToPoint(tiles[i][j][layer].upperRightCorner, it->second);
                else
                    setPoint(tiles[i][j][layer].upperRightCorner, it->second);


    it = properties.find("downerLeft");

    if (it == properties.end())
        it = properties.find("DL");
    
    if (it != properties.end())
        for (int i(selectedTiles.x); i < selectedTiles.w ; ++i)
            for (int j(selectedTiles.y) ; j < selectedTiles.h ; ++j)
                if (add)
                    addToPoint(tiles[i][j][layer].downerLeftCorner, it->second);
                else
                    setPoint(tiles[i][j][layer].downerLeftCorner, it->second);


    it = properties.find("downerRight");

    if (it == properties.end())
        it = properties.find("DR");
    
    if (it != properties.end())
        for (int i(selectedTiles.x); i < selectedTiles.w ; ++i)
            for (int j(selectedTiles.y) ; j < selectedTiles.h ; ++j)
                if (add)
                    addToPoint(tiles[i][j][layer].downerRightCorner, it->second);
                else
                    setPoint(tiles[i][j][layer].downerRightCorner, it->second);
}

void jlug::Map::setPoint(jlug::Point& point, const std::string& values)
{
    std::istringstream iss(values);
    std::string buffer;
    jlug::Axis::AxisName axis(jlug::Axis::X);

    while ( iss >> buffer )
        switch(axis)
        {
            case jlug::Axis::X:
                point.x = atof(buffer.c_str());
                axis = jlug::Axis::Y;
                break;
            
            case jlug::Axis::Y:
                point.y = atof(buffer.c_str());
                axis = jlug::Axis::Z;
                break;

            case jlug::Axis::Z:
                point.z = atof(buffer.c_str());
                break;
            
            default:
                break;
        }
}

void jlug::Map::addToPoint(jlug::Point& point, const std::string& values)
{
    std::istringstream iss(values);
    std::string buffer;
    jlug::Axis::AxisName axis(jlug::Axis::X);

    while ( iss >> buffer )
        switch(axis)
        {
            case jlug::Axis::X:
                point.x += atof(buffer.c_str());
                axis = jlug::Axis::Y;
                break;
            
            case jlug::Axis::Y:
                point.y += atof(buffer.c_str());
                axis = jlug::Axis::Z;
                break;

            case jlug::Axis::Z:
                point.z += atof(buffer.c_str());
                break;
            
            default:
                break;
        }
}

void jlug::Map::setRotation(TileProp& tile, /*const jlug::Point& current, const jlug::Point& max,*/ const std::string& prop)
{
    std::istringstream iss(prop);
    std::string buffer;
    jlug::Axis::AxisName axis(jlug::Axis::X);

    while( iss >> buffer )
    {
        switch(axis)
        {
            case jlug::Axis::X:
                tile.rotation.x += atof(buffer.c_str());
                axis = jlug::Axis::Y;
                break;
            
            case jlug::Axis::Y:
                tile.rotation.y += atof(buffer.c_str());
                axis = jlug::Axis::Z;
                break;
            
            case jlug::Axis::Z:
                tile.rotation.z += atof(buffer.c_str());
                break;

            default:
                break;
        }
    }
}

bool jlug::Map::displayLayer(jlug::Window& win, int index)
{
    jlug::Square square;

    const int MAXW((xscroll+win.getWidth())/getTileWidth());
    const int MAXH((yscroll+win.getHeight())/getTileHeight());
    const int MAP_MAXW(static_cast<int>(getWidth()));
    const int MAP_MAXH(static_cast<int>(getHeight()));

    square.setPixelTranslation(getTileWidth(), getTileHeight());

    for (int j(yscroll/tileHeight);j<MAXH && j<MAP_MAXH;++j)
        for (int i(xscroll/tileWidth);i<MAXW && i<MAP_MAXW;++i)
            if (i >= 0 && j >= 0)
            {
                const jlug::TileProp& tile(tiles[i][j][index]);
                if (tile.gid != UINT_MAX && tile.gid != 0)
                {
                    square.setPosition(i, j, index*0.011);

                    square.translate(tile.translation);
                    square.rotate(tile.rotation);
                    square.scale(tile.scaling);
                    square.translate(tile.translationAfterRotation);

                    if (tile.image)
                    {
                        square.setTexture(tile.texture);
                        square.setTextureSize(0, 0, tile.image->getRealWidth(), tile.image->getRealHeight());
                        square.setTextureZone(tile.limit.x, tile.limit.y, tile.limit.w, tile.limit.h);
                    }

                    square.setVertex(false, false, tile.downerLeftCorner);
                    square.setVertex(false, true, tile.upperLeftCorner);
                    square.setVertex(true, false, tile.downerRightCorner);
                    square.setVertex(true, true, tile.upperRightCorner);

                    square.draw();
                }
            }
            
    return true;
}