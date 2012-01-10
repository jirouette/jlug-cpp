#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

/**
* \file utils.hpp
* \author JirialMovie
*/

#include <istream>
#include <ostream>
#include <string>
#include <sstream> // What ? SS ? GTFO !
#include <vector>
#include <climits>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "utils/base64.h" // <- base64 functions by Bernard Chardonneau
#define ABS(x) ((x<0)?(-(x)):(x)) // define in C++ :( ... 

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    /**
    * \class Rectangle
    * \brief Rectangle with upper-left corner and downer-right corner defined.
    * May be used as a vector.
    */
    template <typename T>
    class Rectangle
    {
        public:
        T
        x, /*!< X-value */
        y, /*!< Y-value */
        w, /*!< Width of the rectangle. */
        h;  /*!< Height of the rectangle. */

        Rectangle(T pX, T pY, T pW, T pH);
        Rectangle(T pX, T pY, T pW);
        Rectangle(T pX, T pY);
        Rectangle(T pX);
        Rectangle(void);
    };

    typedef Rectangle<int> Rect;

    /**
    * \class Point3D
    * \brief 3D-Point
    */

    template <typename T>
    class Point3D
    {
        public:
        T
        x, /*!< X-value */
        y, /*!< Y-value */
        z; /*!< Z-value */

        Point3D(T pX, T pY, T pZ);
        Point3D(T pX, T pY);
        Point3D(T pX);
        Point3D(void);
    };

    typedef Point3D<double> Point;

    /**
    * \enum Collision
    * \brief Type of collision on each tiles
    */
    enum Collision
    {
        WALKABLE, /*!< character can walk on the tile */
        WALL, /*!< character cannot walk on the tile */
        SURF, /*!< character have to surf to walk on the tile */
        LAYERUP, /*!< character which walks on this tile goes to the upper layer */
        LAYERDOWN /*!< character which walks on this tile goes to the downer layer */
    };

    class Image; // predeclaration
    struct TileProp
    {
      unsigned int gid;
      jlug::Image* image;
      GLuint texture;
      jlug::Rectangle<double> limit;
      
      jlug::Collision collision;
      jlug::Point scaling;
      jlug::Point rotation;
      jlug::Point translation;
      jlug::Point translationAfterRotation;

      jlug::Point upperLeftCorner;
      jlug::Point upperRightCorner;
      jlug::Point downerLeftCorner;
      jlug::Point downerRightCorner;
    };

    /**
    * \enum Weather
    * \brief weather of the map
    */
    enum Weather
    {
        NORMAL, /*!< No special weather */
        RAIN, /*!< Raining on the map */
        STORM, /*!< Raining on the map and thunder */
        SNOW, /*!< Snowing on the map */
        FOG, /*!< Fog on the map */
        SUNSHINE /*!< Anormal sunshine on the map */
    };

    /**
    * \struct Tileset
    * \brief Properties of a tileset
    */
    struct Tileset
    {
        int firstgid; /*!< First gid used on the tileset at (0, 0) tile. */
        int width; /*!< Width of the tileset in pixels. */
        int height; /*!< Height of the tileset in pixels. */
        std::string filename; /*!< File name of the tileset. */
        unsigned int
        r, /*!< red component of the transparence of the tileset. Between 0 and 255. */
        g, /*!< green components of the transparence of the tileset. Between 0 and 255. */
        b; /*!< blue components of the transparence of the tileset. Between 0 and 255. */
    };

    namespace Axis
    {
        enum AxisName
        {
            X,
            Y,
            Z
        };
    }

    /**
    * \namespace jlug::KeyCode
    * \brief Contains key codes.
    */
    namespace KeyCode
    {
        /**
        * \enum Code
        * \brief Events key codes.
        */
        enum Code
        {
            A,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,
            Number0,
            Number1,
            Number2,
            Number3,
            Number4,
            Number5,
            Number6,
            Number7,
            Number8,
            Number9,
            Ctrl,
            Alt,
            Shift,
            Super,
            Tab,
            Escape,
            Space,
            Enter,
            Pause,
            Left,
            Right,
            Up,
            Down,

            Count
        };
    }


    /**
    * \namespace jlug::Move
    * \brief Contains directions.
    */
    namespace Move
    {
        /**
        * \enum Direction
        * \brief Character's directions.
        */
        enum Direction
        {
            UP,
            DOWN,
            LEFT,
            RIGHT,
            NONE,

            Count
        };



    }
}

#include "utils.cpp" // needed by template-classes
#endif // UTILS_HPP_INCLUDED
