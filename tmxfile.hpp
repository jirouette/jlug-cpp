#ifndef TMXFILE_HPP_INCLUDED
#define TMXFILE_HPP_INCLUDED

#include "utils.hpp"
#include "layer.hpp"
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"

namespace jlug
{
    class TmxFile
    {
        public:
            TmxFile(const std::string& filename);
            ~TmxFile();
            std::string getMapProperty(const std::string& property);
            std::vector<jlug::Layer>& getLayers();

        private:
            TiXmlDocument doc;

    };
}

#endif // TMXFILE_HPP_INCLUDED
