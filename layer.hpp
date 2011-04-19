#ifndef LAYER_HPP_INCLUDED
#define LAYER_HPP_INCLUDED

#include "utils.hpp"

namespace jlug
{
    class Layer
    {
        public:
            Layer(unsigned int paramWidth = 10, unsigned int paramHeight = 10, unsigned int paramTileWidth = 16, unsigned int paramTileHeight = 16);
            ~Layer(void);

            bool setWidth(unsigned int paramWidth);
            bool setHeight(unsigned int paramHeight);
            bool setSize(unsigned int paramWidth, unsigned int paramHeight);
            bool setSize(jlug::Rect size);
            bool setTileWidth(unsigned int paramTileWidth);
            bool setTileHeight(unsigned int paramTileHeight);
            bool setTileSize(unsigned int paramTileWidth, unsigned int paramTileHeight);
            bool setTileSize(jlug::Rect tileSize);
            bool setOpacity(double paramOpacity);
            bool setVisible(bool paramVisible);
            bool setName(std::string paramName);

            /*bool addTileset(std::string tileset, unsigned int tilesetWidth, unsigned int tilesetHeight);
            bool addTileset(std::string tileset, jlug::Rect tilesetSize);
            bool removeTileset(std::string tileset);
            bool replaceTileset(std::string oldTileset, std::string newTileset);*/

            unsigned int getWidth(void);
            unsigned int getHeight(void);
            jlug::Rect getSize(void);
            unsigned int getTileWidth(void);
            unsigned int getTileHeight(void);
            jlug::Rect getTileSize(void);
            double getOpacity(void);
            bool isVisible(void);
            std::string getName(void);

            unsigned int& tile(unsigned int x, unsigned int y);
            jlug::Collision& collision(unsigned int x, unsigned int y);


        private:
            unsigned int width; // in tiles
            unsigned int height; // in tiles
            unsigned int tileWidth; // in px
            unsigned int tileHeight; // in px
            std::vector<std::string> tilesets;
            std::vector<jlug::Rect> tilesetsSizes; // in tiles
            std::vector< std::vector<unsigned int> > tiles;
            std::vector< std::vector<jlug::Collision> > collisions;

            double opacity;
            bool visible;
            std::string name;
    };
}


#endif // LAYER_HPP_INCLUDED
