#include <iostream>
#include "example.hpp"
#include "layer.hpp"
#include "tmxfile.hpp"

int main(void)
{
    jlug::Layer layer;
    layer.setOpacity(0.521);
    layer.setName("My first layer");
    std::cout << layer;

    jlug::TmxFile map("D:\\projets\\sans-titre.tmx");
    std::cout << "Weather = " << map.getMapProperty("weather") << std::endl;
    return 0;
}
