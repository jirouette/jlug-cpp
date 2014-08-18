#include "loadable/map.hpp"
#include "entities/animatedcharacter.hpp"
#include "entities/player.hpp"

/**
* \file map.cpp
* \author jirouette
*/

const char jlug::Map::className[] = "Map";
Lunar<jlug::Map>::RegType jlug::Map::methods[] = {
    LUNAR_DECLARE_METHOD(jlug::Map, displayCharacters),
    LUNAR_DECLARE_METHOD(jlug::Map, moveCharacters),
    LUNAR_DECLARE_METHOD(jlug::Map, displayLayers),
    LUNAR_DECLARE_METHOD(jlug::Map, addCharacter),
  {0,0}
};

/**
* \brief default constructor
*/
jlug::Map::Map(void):xscroll(0), yscroll(0), depth(0), mapFilename(""), weather(jlug::NORMAL), map()
{}

/**
* \brief constructor which loads a map
* \param filename : path to the map.tmx (relative to executable)
*/
jlug::Map::Map(const std::string& filename, jlug::Window& win, jlug::Input& input):xscroll(0), yscroll(0), depth(0), mapFilename(filename), weather(jlug::NORMAL), map()
{
    loadMap(mapFilename, win, input);
}

jlug::Map::Map(lua_State* L):xscroll(0), yscroll(0), depth(0), mapFilename(""), weather(jlug::NORMAL), map()
{
    loadMap(L);
}

/**
* \brief destructor
*/
jlug::Map::~Map(void)
{}

/**
* \brief loads a map
* \param filename : path to the map.tmx (relative to executable)
*/
void jlug::Map::loadMap(const std::string& filename, jlug::Window& win, jlug::Input& input)
{
    mapFilename = jlug::Constants::getInstance().get("path")+
                  filename;
    map.ParseFile(mapFilename); // Getting a usable data structure of the map

    for (int z(0) ; z < map.GetNumLayers() ; ++z)
    {
        const Tmx::Layer *layer(map.GetLayer(z));
        if (layer && layer->IsVisible()) // layer exists and is visible
        {
            for (int x(0) ; x < layer->GetWidth() ; ++x)
                for (int y(0) ; y < layer->GetHeight() ; ++y)
                        createTile(x,y,depth, layer->GetTileGid(x, y)); // graphics settings

            // Is the tile layer associated with a transformations layer ?
            if (!layer->GetProperties().Empty())
            {
                setTransformations(depth, layer->GetProperties().GetLiteralProperty("transformations"));
                setVertex(depth, jlug::Rect(0, 0, getWidth(), getHeight()), layer->GetProperties().GetList(), true);

                setCollisions(depth, layer->GetProperties().GetLiteralProperty("collisions"));
                setObjects(depth, layer->GetProperties().GetLiteralProperty("objects"), win, input);
            }
            else
                gaps.push_back(std::pair<unsigned int, unsigned int>(1, 1));

            ++depth;
        }
    }
}

int jlug::Map::loadMap(lua_State* L)
{
    loadMap(luaL_checkstring(L, 1), *Lunar<jlug::Window>::check(L, 2), *Lunar<jlug::Input>::check(L, 3));
    return 0;
}

/**
* \brief get the width of a tile
* \return tilewidth
*/
unsigned int jlug::Map::getTileWidth(void)
{
    return map.GetTileWidth();
}

/**
* \brief get the height of a tile
* \return tileheight
*/
unsigned int jlug::Map::getTileHeight(void)
{
    return map.GetTileHeight();
}

/**
* \brief get the width of the map
* \return width of the map
*/
unsigned int jlug::Map::getWidth(void)
{
    return map.GetWidth();
}

/**
* \brief get the height of the map
* \return height of the map
*/
unsigned int jlug::Map::getHeight(void)
{
    return map.GetHeight();
}

/**
* \brief get the depth of the map
* \return depth of the map
*/
unsigned int jlug::Map::getDepth(void)
{
    return depth;
}

/**
* \brief get the current scrolling
* \return Rect
*/
jlug::Rect jlug::Map::getScroll(void)
{
    return jlug::Rect(xscroll, yscroll, xscroll, yscroll);
}

/**
* \brief get the gap between the current layer and the next
* \param z : current layer
*/
unsigned int jlug::Map::getNextGap(unsigned int z)
{
    if (z >= gaps.size())
        return 0;
    return gaps[z].second;
}

/**
* \brief get the gap between the current layer and the previous
* \param z : current layer
*/
unsigned int jlug::Map::getPreviousGap(unsigned int z)
{
    if (z >= gaps.size())
        return 0;
    return gaps[z].first;
}

/**
* \brief creates a tile in the current map
* \param x : X-coordinates of the tile
* \param y : Y-coordinates of the tile
* \param z : Z-coordinates of the tile
* \param gid : GID of the tile
*/
void jlug::Map::createTile(unsigned int x, unsigned int y, unsigned int z, unsigned int gid)
{
    jlug::TileProp tile;

    setTile(tile, gid); // graphics settings

    // Creating dimensions which does not exist yet

    if (tiles.size() <= x)
        tiles.resize(x+1);

    if (tiles[x].size() <= y)
        tiles[x].resize(y+1);

    if (tiles[x][y].size() <= z)
        tiles[x][y].resize(z+1);

    // Our tile is now created !

    tiles[x][y][z] = tile;
}


/**
* \brief get properties of a tile
* \param x : X-coordinates
* \param y : Y-coordinates
* \param z : Z-coordinates
* \return constant reference to the tile properties (TileProp)
*/
const jlug::TileProp& jlug::Map::getTile(unsigned int x, unsigned int y, unsigned int z)
{
    if (tiles.empty())
    {
        createTile(0,0,0,1);
        return tiles[0][0][0];
    }
    else if (tiles.size() <= x)
        return getTile(0,0,0);
    else if (tiles[x].size() <= y)
        return getTile(x,0,0);
    else if (tiles[x][y].size() <= z)
        return getTile(x,y,0);
    return tiles[x][y][z];
}
/**
* \brief set X-position and Y-position of the scroll
* \param x : new X-position scroll
* \param y : new Y-position scroll
*/
void jlug::Map::setScroll(int x, int y)
 {
    xscroll = (x > 0) ? x : 0;
    yscroll = (y > 0) ? y : 0;
 }

/**
* \brief set the camera
* \param x : X-coordinates
* \param y : Y-coordinates
*/
void jlug::Map::setCamera(double x, double y)
{
    gluLookAt(x-5, y+2, 5, x-5, y, 0, 0, 1, 0);
}

/**
* \brief initializes a tile
* \param tile : tile to initialize
*/
void jlug::Map::initTile(TileProp& tile)
{
    // Initializes a TileProp

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

/**
* \brief settings data to a tile by his GID
* \param tile : reference to the tile
* \param gid : GID
*/
void jlug::Map::setTile(TileProp& tile, unsigned int gid)
{
    initTile(tile);
    tile.gid = gid;
    for (int i(0) ; i < map.GetNumTilesets() ; ++i)
    {
        const Tmx::Tileset *tileset(map.GetTileset(i));
        if (tileset) // tileset exists
        {
            if (tileset->GetFirstGid() <= static_cast<int>(tile.gid)) // the tileset may match with our GID
            {

                // Since we're in a "for", the following lines repeated until
                // the current tileset does not match.

                const Tmx::Image *img(tileset->GetImage());
                if (img) // The tileset has an image
                {
                    tile.image = &(ImageManager::getInstance()
                                [
                                    jlug::getDir(mapFilename)+
                                    img->GetSource()
                                ]); // Calling ImageManager instance
                    tile.texture = tile.image->getTexture();

                    // Coordinates of the tile in the tileset

                    tile.limit.x = (static_cast<int>(tile.gid) - tileset->GetFirstGid()) % (tile.image->getWidth() / tileset->GetTileWidth());
                    tile.limit.y = (static_cast<int>(tile.gid) - tileset->GetFirstGid()) / (tile.image->getWidth() / tileset->GetTileWidth());
                    tile.limit.w = tileset->GetTileWidth();
                    tile.limit.h = tileset->GetTileHeight();

                    // Coordinates are in tiles, not in pixels

                    tile.limit.x *= tile.limit.w;
                    tile.limit.y *= tile.limit.h;
                }
            }
        }
    }
}

/**
* \brief applies objects by a object layer name
* \param index of the receiver layer
* \param object layer name which gets objects data
* \param window
*/
void jlug::Map::setObjects(unsigned int z, const std::string& layerName, jlug::Window& win, jlug::Input& input)
{
    const Tmx::ObjectGroup* layer(0);
    for (int i(0) ; i < map.GetNumObjectGroups() ; ++i)
    {
        const Tmx::ObjectGroup *currentLayer = map.GetObjectGroup(i);
        if (currentLayer)
            if (currentLayer->GetName() == layerName) // match
            {
                layer = currentLayer;
                break;
            }
    }

    if (!layer)
        return;

    for (int i(0) ; i < layer->GetNumObjects() ; ++i)
    {
        const Tmx::Object *object = layer->GetObject(i);
        if (object)
        {
            if (object->GetType() == "character")
            {
                Character* c = new Character(object->GetProperties().GetNumericProperty("charset"), object->GetName());
                c->setCoord(object->GetX()/map.GetTileWidth(), object->GetY()/map.GetTileHeight());
                addCharacter(c);
            }
            else if (object->GetType() == "animatedcharacter")
            {
                Character* c = new AnimatedCharacter(object->GetProperties().GetNumericProperty("charset"), object->GetName());
                c->setCoord(object->GetX()/map.GetTileWidth(), object->GetY()/map.GetTileHeight());
                addCharacter(c);
            }
            else if (object->GetType() == "player")
            {
                Character* c = new Player(object->GetProperties().GetNumericProperty("charset"), object->GetName(), input, win);
                c->setCoord(object->GetX()/map.GetTileWidth(), object->GetY()/map.GetTileHeight());
                addCharacter(c);
            }
        }
    }
}

/**
* \brief applies collisions by a tile layer name
* \param z : index of the receiver layer
* \param layerName : tile layer name which gets collisions data
*/
void jlug::Map::setCollisions(unsigned int z, const std::string& layerName)
{
    const Tmx::Layer* layer(0);
    const unsigned int WLL(11), WTR(12), LUP(13), LDWN(14);

    for (int i(0) ; i < map.GetNumLayers() ; ++i)
    {
        const Tmx::Layer *currentLayer = map.GetLayer(i);
        if (currentLayer) // the layer exists
            if (currentLayer->GetName() == layerName) // and matches !
            {
                layer = currentLayer;
                break;
            }
    }

    if (layer && !layer->GetProperties().Empty())
        gaps.push_back(std::pair<unsigned int, unsigned int>(layer->GetProperties().GetNumericProperty("previousGap"),
                                                             layer->GetProperties().GetNumericProperty("nextGap")
                                                            ));
    else
        gaps.push_back(std::pair<unsigned int, unsigned int>(1, 1));

    if (!layer)
        return;

    for (unsigned int i(0) ; i < getWidth() ; ++i)
        for (unsigned int j(0) ; j < getHeight() ; ++j)
        {
            unsigned int gid(layer->GetTileGid(i, j)), localGid(0);
            for (int k(0) ; k < map.GetNumTilesets() ; ++k)
            {
                const Tmx::Tileset *tileset(map.GetTileset(k));
                if (tileset) // tileset exists
                    if (tileset->GetFirstGid() <= static_cast<int>(gid)) // the tileset may match with our GID
                        localGid = gid - tileset->GetFirstGid();
            }

            if (!localGid)
                continue;

            switch (localGid)
            {
                case WLL:
                    tiles[i][j][z].collision = jlug::WALL;
                    break;

                case WTR:
                    tiles[i][j][z].collision = jlug::SURF;
                    break;

                case LUP:
                    tiles[i][j][z].collision = jlug::LAYERUP;
                    break;

                case LDWN:
                    tiles[i][j][z].collision = jlug::LAYERDOWN;
                    break;

                default:
                    break;
            }
        }
}

/**
* \brief applies transformations by a layer name
* \param layer : index of the receiver layer
* \param layerName : layer name which gets transformations data
*/
void jlug::Map::setTransformations(unsigned int index, const std::string& layerName)
{
    const char DELIM(';');
    size_t begin(0);
    for (size_t end(layerName.find(DELIM)) ; begin != std::string::npos ; end = layerName.find(DELIM, begin))
    {
        const Tmx::ObjectGroup *objectLayer(0);
        const Tmx::Layer *layer(0);
        const std::string name(layerName.substr(begin, end-begin));
        if(end != std::string::npos)
            begin = end+1;
        else
            begin = end;

        /*
        * This method looks for an object layer which matches
        * to the associated object/tile layer that the tile layer
        * provided.
        * If there is one, so, check every object/tile the layer contains
        * in order to apply transformations or vertex settings.
        */



        for (int i(0); i < map.GetNumObjectGroups(); ++i)
        {
            const Tmx::ObjectGroup *currentObjectLayer = map.GetObjectGroup(i);
            if (currentObjectLayer) // the object layer exists
                if(currentObjectLayer->GetName() == name) // and matches !
                {
                    objectLayer = currentObjectLayer;
                    break; // we don't need to continue since we found our object layer
                }
        }

        if (objectLayer) // An object layer is found !
            for (int i(0); i < objectLayer->GetNumObjects() ; ++i)
            {
                const Tmx::Object *object = objectLayer->GetObject(i);
                const Tmx::Tileset *tileset(map.GetTileset(0));
                if (object && tileset) // both object and tileset exist
                    if(!object->GetProperties().Empty())
                    {
                        jlug::Rect selectedTiles(object->GetX()/tileset->GetTileWidth(),
                                                 object->GetY()/tileset->GetTileHeight(),
                                                 (object->GetX()+object->GetWidth())/tileset->GetTileWidth(),
                                                 (object->GetY()+object->GetHeight())/tileset->GetTileHeight());

                        if (object->GetType() == "transform")
                            setTransformation(index, selectedTiles, object->GetProperties().GetList());
                        else if (object->GetType() == "modifyVertex")
                            setVertex(index, selectedTiles, object->GetProperties().GetList(), false);
                        else if (object->GetType() == "addVertex")
                            setVertex(index, selectedTiles, object->GetProperties().GetList(), true);
                    }
            }
        else // Let's check tile layers...
        {
            for (int i(0) ; i < map.GetNumLayers() ; ++i)
            {
                const Tmx::Layer *currentLayer = map.GetLayer(i);
                if (currentLayer) // the layer exists
                    if (currentLayer->GetName() == name) // and matches !
                    {
                        layer = currentLayer;
                        break;
                    }
            }

            if (layer) // A tile layer is found !
            {
                for (int i(0) ; i < layer->GetWidth() ; ++i)
                    for (int j(0) ; j < layer->GetHeight() ; ++j)
                    {
                        if (setVertex(index, i, j, layer->GetTileGid(i, j)))
                            if (!layer->GetProperties().Empty())
                                setVertex(index, jlug::Rect(i, j, i+1, j+1), layer->GetProperties().GetList(), true);
                    }
            }
        }
    }
}

/**
* \brief parses and applies transformations data
* \param layer : index of the receiver layer
* \param selectedTiles : Rect of tiles-coordinates
* \param properties : transformations data raw
*/
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

    if (it != properties.end()) // object has "rotate" or "rotation" property
    {
        for (int i(selectedTiles.x) ; i < selectedTiles.w ; ++i)
            for (int j(selectedTiles.y) ; j < selectedTiles.h ; ++j)
                setRotation(tiles[i][j][layer],
                            /*jlug::Point(i, j, layer),
                            jlug::Point(selectedTiles.x+selectedTiles.w,
                                        selectedTiles.y+selectedTiles.h,
                                        layer),*/
                            it->second);
                                // Applies transformation
    }

    it = properties.find("translation");

    if (it == properties.end())
        it = properties.find("translate");

    if (it != properties.end()) // object has "translate" or "translation" property
    {
        for (int i(selectedTiles.x) ; i < selectedTiles.w ; ++i)
            for (int j(selectedTiles.y) ; j < selectedTiles.h ; ++j)
                addToPoint(tiles[i][j][layer].translation, it->second);
                    // Applies transformation
    }

    it = properties.find("scaling");

    if (it == properties.end())
        it = properties.find("scale");

    if (it != properties.end()) // object has "scale" or "scaling" property
    {
        for (int i(selectedTiles.x) ; i < selectedTiles.w ; ++i)
            for (int j(selectedTiles.y) ; j < selectedTiles.h ; ++j)
                addToPoint(tiles[i][j][layer].scaling, it->second);
                    // Applies transformations
    }

}

/**
* \brief parses and applies vertex data
* \param layer : index of the receiver layer
* \param selectedTiles : Rect of tiles-coordinates
* \param properties : vertex data raw
*/
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

    if (it != properties.end()) // modify every vertex in a while !
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

    if (it != properties.end()) // vertex of the upper left corner of the square
        for (int i(selectedTiles.x); i < selectedTiles.w ; ++i)
            for (int j(selectedTiles.y) ; j < selectedTiles.h ; ++j)
                if (add)
                    addToPoint(tiles[i][j][layer].upperLeftCorner, it->second);
                else
                    setPoint(tiles[i][j][layer].upperLeftCorner, it->second);


    it = properties.find("upperRight");

    if (it == properties.end())
        it = properties.find("UR");

    if (it != properties.end()) // vertex of the upper right corner of the square
        for (int i(selectedTiles.x); i < selectedTiles.w ; ++i)
            for (int j(selectedTiles.y) ; j < selectedTiles.h ; ++j)
                if (add)
                    addToPoint(tiles[i][j][layer].upperRightCorner, it->second);
                else
                    setPoint(tiles[i][j][layer].upperRightCorner, it->second);


    it = properties.find("downerLeft");

    if (it == properties.end())
        it = properties.find("DL");

    if (it != properties.end()) // vertex of the downer left corner of the square
        for (int i(selectedTiles.x); i < selectedTiles.w ; ++i)
            for (int j(selectedTiles.y) ; j < selectedTiles.h ; ++j)
                if (add)
                    addToPoint(tiles[i][j][layer].downerLeftCorner, it->second);
                else
                    setPoint(tiles[i][j][layer].downerLeftCorner, it->second);


    it = properties.find("downerRight");

    if (it == properties.end())
        it = properties.find("DR");

    if (it != properties.end()) // vertex of the downer right corner of the square
        for (int i(selectedTiles.x); i < selectedTiles.w ; ++i)
            for (int j(selectedTiles.y) ; j < selectedTiles.h ; ++j)
                if (add)
                    addToPoint(tiles[i][j][layer].downerRightCorner, it->second);
                else
                    setPoint(tiles[i][j][layer].downerRightCorner, it->second);
}

/**
* \brief applies vertex data
* \param layer : index of the receiver layer
* \param x : the X coordinate of the tile
* \param y : the Y coordinate of the tile
* \param gid : data
*/
bool jlug::Map::setVertex(unsigned int layer, int x, int y, unsigned int gid)
{
    unsigned int localGid(0);
    jlug::TileProp& tile(tiles[x][y][layer]);
    const std::string data("0 0 0.5");
    const unsigned int DR(50), DOWN(51), DL(52),
                       RGT(60), CENTER(61), LFT(62),
                       UR(70), UP(71), UL(72),

                       DaR(54), DaL(55),
                       UaR(64), UaL(65),

                       HLFUP(57);

    for (int i(0) ; i < map.GetNumTilesets() ; ++i)
    {
        const Tmx::Tileset *tileset(map.GetTileset(i));
        if (tileset) // tileset exists
            if (tileset->GetFirstGid() <= static_cast<int>(gid)) // the tileset may match with our GID
                localGid = gid - tileset->GetFirstGid();
    }

    if (!localGid)
        return false;

    switch(localGid)
    {
        case DR:
            addToPoint(tile.downerRightCorner, data);
            break;

        case DOWN:
            addToPoint(tile.downerRightCorner, data);
            addToPoint(tile.downerLeftCorner, data);
            break;

        case DL:
            addToPoint(tile.downerLeftCorner, data);
            break;

        case RGT:
            addToPoint(tile.downerRightCorner, data);
            addToPoint(tile.upperRightCorner, data);
            break;

        case CENTER:
            addToPoint(tile.downerRightCorner, data);
            addToPoint(tile.downerLeftCorner, data);
            addToPoint(tile.upperLeftCorner, data);
            addToPoint(tile.upperRightCorner, data);
            break;

        case LFT:
            addToPoint(tile.downerLeftCorner, data);
            addToPoint(tile.upperLeftCorner, data);
            break;

        case UR:
            addToPoint(tile.upperRightCorner, data);
            break;

        case UP:
            addToPoint(tile.upperRightCorner, data);
            addToPoint(tile.upperLeftCorner, data);
            break;

        case UL:
            addToPoint(tile.upperLeftCorner, data);
            break;


        case DaR:
            addToPoint(tile.downerRightCorner, data);
            addToPoint(tile.downerLeftCorner, data);
            addToPoint(tile.upperRightCorner, data);
            break;

        case DaL:
            addToPoint(tile.downerRightCorner, data);
            addToPoint(tile.downerLeftCorner, data);
            addToPoint(tile.upperLeftCorner, data);
            break;

        case UaR:
            addToPoint(tile.upperRightCorner, data);
            addToPoint(tile.upperLeftCorner, data);
            addToPoint(tile.downerRightCorner, data);
            break;

        case UaL:
            addToPoint(tile.upperRightCorner, data);
            addToPoint(tile.upperLeftCorner, data);
            addToPoint(tile.downerLeftCorner, data);
            break;

        case HLFUP:
            addToPoint(tile.upperRightCorner, "0 0 0.25");
            addToPoint(tile.upperLeftCorner, "0 0 0.25");
            break;

        default:
            return false;
            break;
    }
    return true;
}

/**
* \brief parse a string to extract numeric datas and fill a Point with it
* \param point : receiver Point
* \param values : data to extract
*/
void jlug::Map::setPoint(jlug::Point& point, const std::string& values)
{
    std::istringstream iss(values);
    std::string buffer;
    jlug::Axis::AxisName axis(jlug::Axis::X);

    while ( iss >> buffer ) // splitting data with usual separators such as spaces
        switch(axis)
        {
            // modify vertex axis by axis

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

/**
* \brief parse a string to extract numeric datas and add it to a Point
* \param point : receiver Point
* \param values : data to extract
*/
void jlug::Map::addToPoint(jlug::Point& point, const std::string& values)
{
    std::istringstream iss(values);
    std::string buffer;
    jlug::Axis::AxisName axis(jlug::Axis::X);

    while ( iss >> buffer ) // splitting data with usual separators such as spaces
        switch(axis)
        {
            // modify vertex axis by axis

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

/**
* \brief Coming soon !
*/
void jlug::Map::setRotation(TileProp& tile, /*const jlug::Point& current, const jlug::Point& max,*/ const std::string& prop)
{
    std::istringstream iss(prop);
    std::string buffer;
    jlug::Axis::AxisName axis(jlug::Axis::X);

    while( iss >> buffer ) // splitting data with usual separators such as spaces
    {
        switch(axis)
        {
            // modify axis by axis

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

/**
* \brief display every tiles in a layer with their applied transformations
* \param win : Window where we will display
* \param index : index of the layer to display
*/
bool jlug::Map::displayLayer(jlug::Window& win, int index)
{
    jlug::Square square;

    const int MAXW((xscroll+win.getWidth())/getTileWidth()); // Max of the current scrolling frame
    const int MAXH((yscroll+win.getHeight())/getTileHeight());
    const int MAP_MAXW(static_cast<int>(getWidth())); // Max of the map (avoiding overflow)
    const int MAP_MAXH(static_cast<int>(getHeight()));

    const unsigned int tileWidth(getTileWidth());
    const unsigned int tileHeight(getTileHeight());

    if (index >= depth || index < 0)
        return false;

    square.setPixelTranslation(tileWidth, tileHeight);

    for (int j(yscroll/tileHeight);j<MAXH && j<MAP_MAXH;++j)
        for (int i(xscroll/tileWidth);i<MAXW && i<MAP_MAXW;++i)
            if (i >= 0 && j >= 0)
            {
                const jlug::TileProp& tile(tiles[i][j][index]);
                if (tile.gid != UINT_MAX && tile.gid != 0 && tile.image) // tile exists and is not empty
                {
                    square.setPosition(i, j, index*0.011); // Initial position

                    // Usual transformations

                    square.translate(tile.translation);
                    square.rotate(tile.rotation);
                    square.scale(tile.scaling);
                    square.translate(tile.translationAfterRotation);

                    // Texturing

                    square.setTexture(tile.texture);
                    square.setTextureSize(0, 0, tile.image->getRealWidth(), tile.image->getRealHeight());
                    square.setTextureZone(tile.limit.x, tile.limit.y, tile.limit.w, tile.limit.h);

                    // Setting Vertex

                    square.setVertex(false, false, tile.downerLeftCorner);
                    square.setVertex(false, true, tile.upperLeftCorner);
                    square.setVertex(true, false, tile.downerRightCorner);
                    square.setVertex(true, true, tile.upperRightCorner);

                    square.draw(); // finally !
                }
            }

    return true;
}

int jlug::Map::displayLayers(lua_State* L)
{
    jlug::Window& win = *Lunar<jlug::Window>::check(L, 1);
    for (unsigned int k(0);k<depth;++k)
            displayLayer(win, k);
    return 0;
}


/**
* \brief add a character to the map
* \param new character
*/
void jlug::Map::addCharacter(jlug::Character* c)
{
    characters.push_back(c);
}

int jlug::Map::addCharacter(lua_State* L)
{
    addCharacter(Lunar<jlug::Character>::check(L, 1));
    //Lunar<jlug::Character>::check(L, 1)->setMove(*this, jlug::Move::LEFT, 5);
    return 0;
}

/**
* \brief remove a character from the map
* \param name of the character
*/
void jlug::Map::removeCharacter(const std::string& name)
{
    for(std::list<jlug::Character*>::iterator character(characters.begin()) ; character != characters.end() ; ++character)
        if ((*character)->getName() == name)
        {
            characters.erase(character);
            return;
        }
}

/**
* \brief process characters moving
*/
void jlug::Map::moveCharacters()
{
    for(std::list<jlug::Character*>::iterator character(characters.begin()) ; character != characters.end() ; ++character)
        (*character)->move(*this);
}

int jlug::Map::moveCharacters(lua_State* L)
{
    moveCharacters();
    return 0;
}

/**
* \brief display every characters
* \param window
*/
void jlug::Map::displayCharacters(jlug::Window& win)
{
    for(std::list<jlug::Character*>::iterator character(characters.begin()) ; character != characters.end() ; ++character)
        (*character)->display(*this, win);
}

int jlug::Map::displayCharacters(lua_State* L)
{
    displayCharacters(*Lunar<jlug::Window>::check(L, 1));
    return 0;
}


/**
* \brief check whether a character is in a tile
*/
bool jlug::Map::characterIn(unsigned x, unsigned y, unsigned z, jlug::Character* except)
{
    for(std::list<jlug::Character*>::iterator character(characters.begin()) ; character != characters.end() ; ++character)
        if ((*character) != except && z == (*character)->getZ())
            if(((*character)->getPixX() >= x*map.GetTileWidth() && (*character)->getPixX() < ((x+1)*map.GetTileWidth())) || (((*character)->getPixX()+map.GetTileWidth()-1) >= x*map.GetTileWidth() && ((*character)->getPixX()+map.GetTileWidth()-1) < ((x+1)*map.GetTileWidth())))
            if(((*character)->getPixY() >= y*map.GetTileHeight() && (*character)->getPixY() < ((y+1)*map.GetTileHeight())) || (((*character)->getPixY()+map.GetTileHeight()-1) >= y*map.GetTileHeight() && ((*character)->getPixY()+map.GetTileHeight()-1) < ((y+1)*map.GetTileHeight())))
                return true;
    return false;
}
