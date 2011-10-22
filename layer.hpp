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
            struct TileProp
            {
                unsigned int gid;
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

            Layer();
            ~Layer(void);

            bool setOpacity(double paramOpacity);
            bool setVisible(bool paramVisible);
            bool setTile(unsigned int x, unsigned int y, const jlug::Layer::TileProp& tileprop);
            bool setName(const std::string& paramName);
            bool clear(void);

            double getOpacity(void);
            bool isVisible(void);
            std::string getName(void);

            jlug::Layer::TileProp& tile(unsigned int x, unsigned int y);


        protected:
            std::vector< std::vector<jlug::Layer::TileProp> > tiles; /*!< propeties (such as GID, collisions...) of tiles in multidimensionnal vector. */

            double opacity; /*!< Opacity of the layer */
            bool visible; /*!< If layer is visible or not */
            std::string name;/*!< Name of the layer */
    };
}

#endif // LAYER_HPP_INCLUDED
