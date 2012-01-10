#include "map.hpp"

/**
* \file map.cpp
* \author JirialMovie
*/

/**
* \brief default constructor
*/
jlug::Map::Map(void):xscroll(0), yscroll(0), mapFilename(""), weather(jlug::NORMAL), map()
{}

/**
* \brief constructor which loads a map
* \param filename : path to the map.tmx (relative to executable)
*/
jlug::Map::Map(const std::string& filename):xscroll(0), yscroll(0), mapFilename(filename), weather(jlug::NORMAL), map()
{
    loadMap(mapFilename);
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
void jlug::Map::loadMap(const std::string& filename)
{
    mapFilename = filename;
    map.ParseFile(filename); // Getting a usable data structure of the map

    for (int z(0) ; z < map.GetNumLayers() ; ++z)
    {
        const Tmx::Layer *layer(map.GetLayer(z));
        if (layer) // layer exists
        {
            for (int x(0) ; x < layer->GetWidth() ; ++x)
                for (int y(0) ; y < layer->GetHeight() ; ++y)
                {
                        createTile(x,y,z, layer->GetTileGid(x, y)); // graphics settings
                }
            
            // Is the tile layer associated with a transformations layer ? 
            if (!layer->GetProperties().Empty()) 
                setTransformations(z, layer->GetProperties().GetLiteralProperty("transformations"));
        }
    }
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
    return map.GetNumLayers();
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
void jlug::Map::setCamera(int x, int y)
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
                    tile.image = &(ImageManager::getInstance()[img->GetSource()]); // Calling ImageManager instance
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
* \brief applies transformations by a object layer name
* \param layer : index of the receiver layer
* \param objectLayerName : object layer name which gets transformations data
*/
void jlug::Map::setTransformations(unsigned int layer, const std::string& objectLayerName)
{
    const Tmx::ObjectGroup *objectLayer(0);

    /*
    * This method looks for an object layer which matches
    * to the associated object layer that the tile layer
    * provided. 
    * If there is one, so, check every object the layer contains
    * in order to apply transformations or vertex settings. 
    */

    for (int i(0); i < map.GetNumObjectGroups(); ++i)
    {
        const Tmx::ObjectGroup *currentObjectLayer = map.GetObjectGroup(i);
        if (currentObjectLayer) // the object layer exists
            if(currentObjectLayer->GetName() == objectLayerName) // and matches ! 
            {
                objectLayer = currentObjectLayer;
                break; // we don't need to continue since we found our object layer
            }
    }

    if (!objectLayer) // the loop has ended without having found our object layer...
        return; // let's go back to the map loading
    
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
                    setTransformation(layer, selectedTiles, object->GetProperties().GetList());
                else if (object->GetType() == "modifyVertex")
                    setVertex(layer, selectedTiles, object->GetProperties().GetList(), false);
                else if (object->GetType() == "addVertex")
                    setVertex(layer, selectedTiles, object->GetProperties().GetList(), true);
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