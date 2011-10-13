#include "tmxfile.hpp"

/**
* \brief Constructor
* \param filename : path to the *.tmx file.
*
* If the file couldn't be loaded, the running attribute is set to false.
*/
jlug::TmxFile::TmxFile(const std::string& filename):
                        doc(filename.c_str()), tilesets(), layers()
{
    if (!doc.LoadFile())
        running = false;
    else
        running = true;
}

/**
* \brief Destructor
* Nothing to do.
*/
jlug::TmxFile::~TmxFile(void)
{}

/**
* \brief Get a global map property by his name.
* \param property : name of the property
* \return value of the property if it exists, otherwise, "(null)"-string.
*
* Looks for a property in the global map properties and returns it if it exists.
*/
std::string jlug::TmxFile::getMapProperty(const std::string& property)
{
    if (running)
    {
        TiXmlHandle hdl(&doc);
        TiXmlElement* elem = hdl.FirstChildElement().FirstChildElement().FirstChildElement().Element();
        while(elem)
        {
            if (elem->Attribute("name") == property)
                return elem->Attribute("value");
            elem = elem->NextSiblingElement();
        }
    }
    return "(null)";
}

/**
* \brief get layers from the *.tmx file
* \return reference to layers
*
* This generates layers from the XML Tree and then, returns them.
*/
std::vector<jlug::Layer>& jlug::TmxFile::getLayers(void)
{
    TiXmlHandle hdl(&doc);
    TiXmlElement* elem, *child;
    jlug::Layer layer;
    if (running)
    {
        if (!layers.empty())
            layers.clear();
        elem = hdl.FirstChildElement().FirstChildElement().Element();
        while(elem)
        {
            if (elem->Value() == std::string("layer"))
            {
                layer.clear();
                if (elem->Attribute("name") != NULL)
                    layer.setName(elem->Attribute("name"));
                else
                    layer.setName("Untitled Layer");

                if (elem->Attribute("visible") != NULL) // visible attribute must be 0 or 1. So, 0 <=> false, 1 <=> true.
                    layer.setVisible((elem->Attribute("visible") == std::string("0")) ? false : true);
                else
                    layer.setVisible(true); // Visible default value is true.

                if (elem->Attribute("opacity") != NULL)
                    layer.setOpacity(atof(elem->Attribute("opacity")));
                else
                    layer.setOpacity(1.0); // Opacity default value is 1.0

                child = elem->FirstChildElement();
                if (child)
                    if(child->Value() == std::string("data")) // searching for "data"-node which contains node.
                    {
                        if(child->Attribute("encoding") != NULL)
                        {
                            if (child->Attribute("encoding") == std::string("base64"))
                                getBase64Tiles(child, layer); // Base 64 Tiles
                            else
                                getTiles(child, layer); // XML Tiles // We only supports base64 encoded format and XML format.
                        }
                        else
                            getTiles(child, layer); // XML Tiles
                    }
                layers.push_back(layer);
            }
            else if (elem->Value() == std::string("objectgroup")) // Objectgroup will be used for collisions and something else.
            {
                //child = hdlChild.FirstChildElement().Element();
                /*if (child)
                    getCollisions(child, layers[layers.size()-1]);*/
            }
            elem = elem->NextSiblingElement();
        }
    }
    return layers;
}

/**
* \brief get the map size in tiles
* \return rect with w datafield as width of the map in tiles and h datafield as height of the map in tiles
*/
jlug::Rect jlug::TmxFile::getMapSize(void)
{
    int width(0), height(0);
    jlug::Rect rect = {0, 0, 0, 0};
    if (running)
    {
        TiXmlHandle hdl(&doc);
        TiXmlElement* elem = hdl.FirstChildElement().Element();
        width = atoi(elem->Attribute("width"));
        height = atoi(elem->Attribute("height"));
        rect.w = width;
        rect.h = height;
    }
    return rect;
}

/**
* \brief get tile size in pixels
* \return rect with w datafield as width of the tile in pixels and h datafield as height of the tile in pixels
*/
jlug::Rect jlug::TmxFile::getTileSize(void)
{
    int tileWidth(0), tileHeight(0);
    jlug::Rect rect = {0, 0, 0, 0};
    if (running)
    {
        TiXmlHandle hdl(&doc);
        TiXmlElement* elem = hdl.FirstChildElement().Element();
        tileWidth = atoi(elem->Attribute("tilewidth"));
        tileHeight = atoi(elem->Attribute("tileheight"));
        rect.w = tileWidth;
        rect.h = tileHeight;
    }
    return rect;
}

/**
* \brief get map width in tiles
* \return map width in tiles
*/
unsigned int jlug::TmxFile::getMapWidth(void)
{
    if (running)
    {
        TiXmlHandle hdl(&doc);
        TiXmlElement* elem = hdl.FirstChildElement().Element();
        return atoi(elem->Attribute("width"));
    }
    return 0;
}

/**
* \brief get map height in tiles
* \return map height in tiles
*/
unsigned int jlug::TmxFile::getMapHeight(void)
{
    if (running)
    {
        TiXmlHandle hdl(&doc);
        TiXmlElement* elem = hdl.FirstChildElement().Element();
        return atoi(elem->Attribute("height"));
    }
    return 0;
}

/**
* \brief get tilesets from the *.tmx file
* \return reference to tilesets
*
* This generates tilesets from the XML Tree and returns them.
*/
std::vector<jlug::Tileset>& jlug::TmxFile::getTilesets(void)
{
    TiXmlHandle hdl(&doc);
    TiXmlElement* elem;
    jlug::Tileset tileset = {0, 0, 0, "", 0, 0, 0};
    unsigned int color(0);
    if (running)
    {
        if (!tilesets.empty())
            tilesets.clear();
        elem = hdl.FirstChildElement().FirstChildElement().Element();
        while(elem)
        {
            if (elem->Value() == std::string("tileset"))
                if (elem->FirstChildElement() != NULL)
                    if (elem->FirstChildElement()->Value() == std::string("image"))
                    {
                        tileset.firstgid = atoi(elem->Attribute("firstgid"));
                        tileset.width = atoi(elem->FirstChildElement()->Attribute("width"));
                        tileset.height = atoi(elem->FirstChildElement()->Attribute("height"));
                        color = strtol(elem->FirstChildElement()->Attribute("trans"), NULL, 16); // convert base16-format string to unsigned int
                        tileset.r = (color>>16)&0xFF; // Get the only red component of color : 0xXX0000
                        tileset.g = (color>>8)&0xFF; // Get the only green component of color : 0x00XX00
                        tileset.b = color&0xFF; // Get the only blue component of color : 0x0000XX
                        tileset.filename = elem->FirstChildElement()->Attribute("source");
                        tilesets.push_back(tileset);
                    }
            elem = elem->NextSiblingElement();
        }
    }
    return tilesets;
}

/**
* \brief get tiles from base64 encoded format
* \return true
*
* This gets tiles from base64 encoded format in the node XML and affects them to the reference to the layer.
*/
bool jlug::TmxFile::getBase64Tiles(TiXmlElement* child, jlug::Layer& layer)
{
    unsigned char* data = new unsigned char[strlen(child->GetText())+1]; // allocate because decode64 is a C-function which does not accept std::string
    jlug::Rect mapSize = getMapSize();
    unsigned int gid(0);
    int x(0), y(0), i(0), max(0);

    sprintf(reinterpret_cast<char*>(data), "%s", child->GetText()); // place the text in our allocated variable
    max = decode64(data); // decoding 64 it. max is the length of decoded characters directly modified in data.
    for (i = 3 ; i < max ; i+=4)
    {
        gid = data[i-3] | data[i-2] << 8 | data[i-1] << 16 | data[i] << 24;
        // see http://sourceforge.net/apps/mediawiki/tiled/index.php?title=Examining_the_map_format
        if (x == mapSize.w)
        {
            ++y;
            x = 0;
            // managing rows and columns
        }

        if (x < mapSize.w && y < mapSize.h)
            layer.setTile(x, y, gid);
        ++x;
    }
    delete[] data; // desallocating :D
    return true;
}

/**
* \brief get tiles from XML format
* \return true
*
* This gets tiles from XML format in the node XML and affects them to the reference to the layer.
*/
bool jlug::TmxFile::getTiles(TiXmlElement* child, jlug::Layer& layer)
{
    TiXmlElement* node = child->FirstChildElement();
    jlug::Rect mapSize = getMapSize();
    int x(0), y(0);
    while(node)
    {
        if (x == mapSize.w)
        {
            ++y;
            x = 0;
            // managing rows and columns.
        }

        if (x < mapSize.w && y < mapSize.h)
            layer.setTile(x, y, atoi(node->Attribute("gid"))); // XML Tiles format is far more simply than base64 ;o


        ++x;
        node = node->NextSiblingElement();
    }
    return true;
}
