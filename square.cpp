#include "square.hpp"

/**
* \file square.cpp
* \author JirialMovie
*/

/**
* \brief Default constructor
* Default and only constructor. 
*/

jlug::Square::Square(void):Shape()
{
    // Default vertex

    downerLeftCorner.x = 0.f;
    downerLeftCorner.y = 0.f;
    downerLeftCorner.z = 0.f;

    downerRightCorner.x = 1.f;
    downerRightCorner.y = 0.f;
    downerRightCorner.z = 0.f;

    upperLeftCorner.x = 0.f;
    upperLeftCorner.y = 1.f;
    upperLeftCorner.z = 0.f;

    upperRightCorner.x = 1.f;
    upperRightCorner.y = 1.f;
    upperRightCorner.z = 0.f;
}

/**
* \brief Destructor
* Nothing to do. 
*/
jlug::Square::~Square(void)
{}

/**
* \brief setting vertex of a corner
* \param rightSide : true for the right side, false for the left side
* \param upSide : true for the up side, false for the down side
* \param vertex : data
*
* setting vertex by the position of the selected corner
*/
void jlug::Square::setVertex(bool rightSide, bool upSide, const jlug::Point& vertex)
{
    // setting vertex by the position of the selected corner
    if (rightSide && upSide)
        upperRightCorner = vertex;
    else if (rightSide && !upSide)
        downerRightCorner = vertex;
    else if (!rightSide && upSide)
        upperLeftCorner = vertex;
    else if (!rightSide && !upSide)
        downerLeftCorner = vertex;
}

/**
* \brief draws the square
*
* draws the rect-shape with its color and its texture
*/
void jlug::Square::draw(void)
{
    // texture positions constants
    double XPOS(static_cast<double>(textureSize.x+textureZone.x)/static_cast<double>(textureSize.w)),
           YPOS(static_cast<double>(textureSize.y+textureZone.y)/static_cast<double>(textureSize.h)),
           MAXXPOS(static_cast<double>(textureSize.x+textureZone.x+textureZone.w)/static_cast<double>(textureSize.w)),
           MAXYPOS(static_cast<double>(textureSize.y+textureZone.y+textureZone.h)/static_cast<double>(textureSize.h));
    
     glPushMatrix(); // saving the current matrix

     jlug::Shape::applyTransformations();

     if (texture) // setting a texture if it exists
     {
         glBindTexture(GL_TEXTURE_2D, texture);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
         glEnable(GL_ALPHA_TEST);
         glAlphaFunc(GL_GREATER, 0.0f);
     }

     glBegin(GL_QUADS); // Drawing the rect-shape
        glColor3f(color.x, color.y, color.z);
        if (texture) { glTexCoord2f(XPOS, MAXYPOS); }       glVertex3f(downerLeftCorner.x, downerLeftCorner.y, downerLeftCorner.z);
        if (texture) { glTexCoord2f(XPOS, YPOS); }          glVertex3f(upperLeftCorner.x, upperLeftCorner.y, upperLeftCorner.z);
        if (texture) { glTexCoord2f(MAXXPOS, YPOS); }       glVertex3f(upperRightCorner.x, upperRightCorner.y, upperRightCorner.z);
        if (texture) { glTexCoord2f(MAXXPOS, MAXYPOS); }    glVertex3f(downerRightCorner.x, downerRightCorner.y, downerRightCorner.z);
     glEnd();

     if (texture)
        glDisable(GL_ALPHA_TEST);
     glPopMatrix(); // restoring the previous matrix
}
