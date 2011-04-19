#include <iostream>
#include "example.hpp"
#include "layer.hpp"

int main(void)
{
    jlug::Layer layer;
    layer.setOpacity(0.521);
    layer.setName("My first layer");
    int dummy;
    std::cout << layer;
    return 0;
}
