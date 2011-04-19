#include <iostream>
#include "example.hpp"
#include "layer.hpp"

int main(void)
{
    jlug::Layer layer;
    jlug::Rect rect = {0, 0, 32, 16};
    layer.setTileSize(rect);
    layer.setOpacity(0.521);
    int dummy;
    std::cout << "Layer(" << layer.getTileWidth() << ", " << layer.getTileHeight() << ")" << std::endl;
    std::cout << layer.getOpacity() << std::endl;
    std::cin >> dummy;
    return 0;
}
