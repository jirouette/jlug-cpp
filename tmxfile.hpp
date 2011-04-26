#ifndef TMXFILE_HPP_INCLUDED
#define TMXFILE_HPP_INCLUDED

/**
* \file tmxfile.hpp
* \author JirialMovie
*/

#include <cstdlib>
#include "utils.hpp"
#include "layer.hpp"
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    /**
    * \class TmxFile
    * \brief Read and parse a *.tmx file.
    *
    * This class can read a *.tmx file and parse it.
    * Then, we can extract datas with accessors.
    */
    class TmxFile
    {
        public:
            TmxFile(const std::string& filename);
            ~TmxFile(void);
            std::string getMapProperty(const std::string& property);
            std::vector<jlug::Layer>& getLayers(void);
            std::vector<jlug::Tileset>& getTilesets(void);
            jlug::Rect getMapSize(void);
            jlug::Rect getTileSize(void);
            unsigned int getMapWidth(void);
            unsigned int getMapHeight(void);

        private:
            bool getBase64Tiles(TiXmlElement* child, jlug::Layer& layer);
            bool getTiles(TiXmlElement* child, jlug::Layer& layer);


            TiXmlDocument doc; /*!< XML Tree of the TMX file. */
            std::vector<jlug::Tileset> tilesets; /*!< List of every tileset used */
            std::vector<jlug::Layer> layers; /*!< List of every layers generated */
            //std::map<std::string, std::string> properties;
            bool running; /*!< Boolean used to disabled most of methods if loading file has failed. To be changed. */

    };
}

#endif // TMXFILE_HPP_INCLUDED
