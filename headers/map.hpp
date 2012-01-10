#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

/**
* \file map.hpp
* \author JirialMovie
*/

#include "utils.hpp"
#include "utils/resourcemanager.hpp"
#include "window.hpp"
#include "shape.hpp"
#include "square.hpp"

#include "TmxParser/Tmx.h"


/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    /**
    * \class Map
    * \brief Orthogonal tiles format displaying
    */
    
    class Map
    {
        public:

            Map(void);
            Map(const std::string& filename);
            ~Map(void);

            void loadMap(const std::string& filename);
            unsigned int getTileWidth(void);
            unsigned int getTileHeight(void);
            unsigned int getWidth(void);
            unsigned int getHeight(void);
            unsigned int getDepth(void);
            jlug::Rect getScroll(void);
            const jlug::TileProp& getTile(unsigned int x, unsigned int y, unsigned int z);

            void setScroll(int x, int y);
            void setCamera(int x, int y);

            void createTile(unsigned int x, unsigned int y, unsigned int z, unsigned int gid);

            void initTile(TileProp& tile);
            void setTile(TileProp& tile, unsigned int gid);
            void setTransformations(unsigned int layer, const std::string& objectLayerName);
            void insertTile(unsigned int x, unsigned int y, unsigned int z, unsigned int gid, const std::string& objectLayerName);

            void setTransformation(unsigned int layer, const jlug::Rect& selectedTiles, const std::map<std::string, std::string>& properties);
            void setVertex(unsigned int layer, const jlug::Rect& selectedTiles, const std::map<std::string, std::string>& properties, bool add = true);

            void setPoint(jlug::Point& point, const std::string& values);
            void addToPoint(jlug::Point& point, const std::string& values);

            void setRotation(TileProp& tile, /*const jlug::Point& current, const jlug::Point& max,*/ const std::string& prop);

            bool displayLayer(jlug::Window& win, int index);


        protected:
            int xscroll; /*!< X-position of the camera on the map */
            int yscroll; /*!< Y-position of the camera on the map */

            std::string mapFilename; /*!< path to map file */
            jlug::Weather weather; /*!< weather */
            Tmx::Map map; /*!< Tmx-file parser */

            std::vector< std::vector< std::vector < jlug::TileProp > > > tiles; /*!< tiles */



    };
}

#endif // MAP_HPP_INCLUDED
