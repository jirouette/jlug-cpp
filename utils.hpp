#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <string>
#include <vector>

namespace jlug
{
    struct Rect
    {
        int x, y, w, h;
    };

    enum Collision
    {
        VOID, WALL, SURF, LAYERUP, LAYERDOWN
    };

    enum Weather
    {
        NORMAL, RAIN, STORM, SNOW, FOG, SUNSHINE
    };






}


#endif // UTILS_HPP_INCLUDED
