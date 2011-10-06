#ifndef LAYER_HPP_INCLUDED
#define LAYER_HPP_INCLUDED

/**
* \file layer.hpp
* \author JirialMovie
*/

#include <iostream>
#include "utils.hpp"

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    /**
    * \class Layer
    * \brief layer of tiles
    *
    * Contains tiles of a layer, and their collisions states.
    */
    class Layer
    {
        public:
            Layer();
            ~Layer(void);

            bool setOpacity(double paramOpacity);
            bool setVisible(bool paramVisible);
            bool setTile(unsigned int x, unsigned int y, unsigned int gid);
            bool setName(const std::string& paramName);
            bool clear(void);

            double getOpacity(void);
            bool isVisible(void);
            std::string getName(void);

            unsigned int tile(unsigned int x, unsigned int y);
            jlug::Collision& collision(unsigned int x, unsigned int y);


        protected:
            std::vector< std::vector<unsigned int> > tiles; /*!< GID of tiles in multidimensionnal vector. */
            std::vector< std::vector<jlug::Collision> > collisions; /*!< Collisions states of tiles in multidimensionnal vector. */

            double opacity; /*!< Opacity of the layer */
            bool visible; /*!< If layer is visible or not */
            std::string name;/*!< Name of the layer */
    };
}

#endif // LAYER_HPP_INCLUDED
