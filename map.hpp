#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include "utils.hpp"
#include "layer.hpp"


namespace jlug
{
    class Map
    {
        public:
            Map(void);
            Map(const std::string& filename);
            ~Map(void);

            bool loadMap(const std::string& filename);

            /*bool processEvents(void);
            bool display(void);*/





        private:
            /*bool displayLayers(const jlug::Layer& layer);
            bool displayCharacters(const jlug::Layer& layer);
            bool displayObjects(const jlug::Layer& layer);*/

            std::string mapFilename;
            std::vector<jlug::Layer> layers;
            jlug::Weather weather;



    };
}

#endif // MAP_HPP_INCLUDED
