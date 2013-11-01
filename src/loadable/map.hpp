#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

/**
* \file map.hpp
* \author jirouette
*/

#include "utils.hpp"
#include "utils/resourcemanager.hpp"
#include "utils/constants.hpp"
#include "utils/dir.hpp"
#include "utils/window.hpp"
#include "models/shape.hpp"
#include "models/square.hpp"
#include "entities/character.hpp"

#include "TmxParser/Tmx.h"

#include <list>

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    class Character;

    /**
    * \class Map
    * \brief Orthogonal tiles format displaying
    */
    
    class Map
    {
        public:

            Map(void);
            Map(const std::string& filename, jlug::Window& win, jlug::Input& input);
            ~Map(void);

            void loadMap(const std::string& filename, jlug::Window& win, jlug::Input& input);
            unsigned int getTileWidth(void);
            unsigned int getTileHeight(void);
            unsigned int getWidth(void);
            unsigned int getHeight(void);
            unsigned int getDepth(void);
            unsigned int getNextGap(unsigned int z);
            unsigned int getPreviousGap(unsigned int z);
            jlug::Rect getScroll(void);
            const jlug::TileProp& getTile(unsigned int x, unsigned int y, unsigned int z);

            void setScroll(int x, int y);
            void setCamera(double x, double y);

            void createTile(unsigned int x, unsigned int y, unsigned int z, unsigned int gid);

            void initTile(TileProp& tile);
            void setTile(TileProp& tile, unsigned int gid);
            void setTransformations(unsigned int layer, const std::string& layerName);
            void setCollisions(unsigned int z, const std::string& layerName);
            void setObjects(unsigned int z, const std::string& layerName, jlug::Window& win, jlug::Input& input);
            void insertTile(unsigned int x, unsigned int y, unsigned int z, unsigned int gid, const std::string& objectLayerName);

            void setTransformation(unsigned int layer, const jlug::Rect& selectedTiles, const std::map<std::string, std::string>& properties);
            void setVertex(unsigned int layer, const jlug::Rect& selectedTiles, const std::map<std::string, std::string>& properties, bool add = true);
            bool setVertex(unsigned int layer, int x, int y, unsigned int gid);

            void setPoint(jlug::Point& point, const std::string& values);
            void addToPoint(jlug::Point& point, const std::string& values);

            void setRotation(TileProp& tile, /*const jlug::Point& current, const jlug::Point& max,*/ const std::string& prop);

            bool displayLayer(jlug::Window& win, int index);

            void addCharacter(jlug::Character* c);
            void moveCharacters();
            void displayCharacters(jlug::Window& win);
            bool characterIn(unsigned x, unsigned y, unsigned z, jlug::Character* except);



        protected:
            int xscroll; /*!< X-position of the camera on the map */
            int yscroll; /*!< Y-position of the camera on the map */

            int depth; /*!< Depth of the map */

            std::string mapFilename; /*!< path to map file */
            jlug::Weather weather; /*!< weather */
            Tmx::Map map; /*!< Tmx-file parser */

            std::vector< std::vector< std::vector < jlug::TileProp > > > tiles; /*!< tiles */
            std::list<jlug::Character*> characters;
            std::vector< std::pair<unsigned int, unsigned int> > gaps; // <== SEGFAULT



    };
}

#endif // MAP_HPP_INCLUDED
