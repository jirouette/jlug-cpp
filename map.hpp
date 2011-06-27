#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

/**
* \file map.hpp
* \author JirialMovie
*/

#include <SFML/Graphics.hpp>

#include "utils.hpp"
#include "layer.hpp"
#include "tmxfile.hpp"
#include "imagemanager.hpp"
#include "window.hpp"


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

            int xscroll, yscroll; // To be changed

            Map(jlug::ImageManager& imageM);
            Map(const std::string& filename, jlug::ImageManager& imageM);
            ~Map(void);

            bool loadMap(const std::string& filename);
            bool setWidth(unsigned int paramWidth);
            bool setHeight(unsigned int paramHeight);
            bool setSize(unsigned int paramWidth, unsigned int paramHeight);
            bool setSize(jlug::Rect size);
            bool setTileWidth(unsigned int paramTileWidth);
            bool setTileHeight(unsigned int paramTileHeight);
            bool setTileSize(unsigned int paramTileWidth, unsigned int paramTileHeight);
            bool setTileSize(jlug::Rect tileSize);


            unsigned int getWidth(void);
            unsigned int getHeight(void);
            jlug::Rect getSize(void);
            unsigned int getTileWidth(void);
            unsigned int getTileHeight(void);
            jlug::Rect getTileSize(void);
            std::vector<jlug::Layer>& getLayers(void);
            unsigned int getLayersSize(void);
            jlug::Tileset* getTilesetByGid(unsigned int gid);
            jlug::Rect getRectByGid(unsigned int gid, const jlug::Tileset* tileset);

            bool displayLayer(jlug::Window& win, int index);


        private:
            unsigned int width; /*!< width in tiles */
            unsigned int height; /*!< height in tiles */
            unsigned int tileWidth; /*!< width of tiles in px */
            unsigned int tileHeight; /*!< height of tiles in px */

            //int xscroll; /*!< X-position of the camera on the map */
            //int yscroll; /*!< Y-position of the camera on the map */

            std::vector<jlug::Tileset> tilesets; /*!< tilesets */
            std::vector<jlug::Rect> gidRects; /*!< rect for each GID in their tileset. */
            std::vector<jlug::Tileset*> gidTilesets;/*!< tileset for each GID */

            std::string mapFilename; /*!< path to map file */
            std::vector<jlug::Layer> layers; /*!< layers of tiles */
            jlug::Weather weather; /*!< weather */
            jlug::ImageManager& IM; /*!< image manager */



    };
}

#endif // MAP_HPP_INCLUDED
