#include "map.hpp"

jlug::Map::Map(void):
                mapFilename(""), layers(), weather(NORMAL)
{}

jlug::Map::Map(const std::string& filename):
                mapFilename(filename), layers(), weather(NORMAL)
{
    loadMap(mapFilename);
}

jlug::Map::~Map(void)
{}

bool jlug::Map::loadMap(const std::string& filename)
{


    return true;
}
