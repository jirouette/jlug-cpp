#ifndef OBJRENDERER_HPP_INCLUDED
#define OBJRENDERER_HPP_INCLUDED

/**
* \file renderer.hpp
* \author jirouette
*/

#include "models/renderer.hpp"
#include "utils/resourcemanager.hpp"
#include <string>
#include <fstream>

/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    /**
    * \class ObjRenderer
    * \brief Render a OBJ file
    */
    class ObjRenderer : public Renderer
    {
        public:
            struct FacePoint
            {
                size_t v, vt, vn;
            };

            struct Face
            {
                FacePoint a, b, c;
            };

            ObjRenderer(const std::string& file);
            virtual ~ObjRenderer();

            virtual void construct();

            void getFacePoint(jlug::ObjRenderer::FacePoint& fp, const std::string& pt);

        protected:
            std::vector<jlug::Point> v;
            std::vector<jlug::Point> vt;
            std::vector<jlug::Point> vn;

            std::vector<Face> faces;
    };
}



#endif // OBJRENDERER_HPP_INCLUDED
