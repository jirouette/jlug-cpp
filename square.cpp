#include "square.hpp"

jlug::Square::Square(void):Shape()
{
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

jlug::Square::~Square(void)
{}

void jlug::Square::setVertex(bool rightSide, bool upSide, const jlug::Point& vertex)
{
    if (rightSide && upSide)
        upperRightCorner = vertex;
    else if (rightSide && !upSide)
        downerRightCorner = vertex;
    else if (!rightSide && upSide)
        upperLeftCorner = vertex;
    else if (!rightSide && !upSide)
        downerLeftCorner = vertex;
}

void jlug::Square::draw(void)
{
    double XPOS(static_cast<double>(textureSize.x+textureZone.x)/static_cast<double>(textureSize.w)),
           YPOS(static_cast<double>(textureSize.y+textureZone.y)/static_cast<double>(textureSize.h)),
           MAXXPOS(static_cast<double>(textureSize.x+textureZone.x+textureZone.w)/static_cast<double>(textureSize.w)),
           MAXYPOS(static_cast<double>(textureSize.y+textureZone.y+textureZone.h)/static_cast<double>(textureSize.h));
    
     glPushMatrix();

     jlug::Shape::applyTransformations();

     if (texture)
     {
         glBindTexture(GL_TEXTURE_2D, texture);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
         glEnable(GL_ALPHA_TEST);
         glAlphaFunc(GL_GREATER, 0.0f);
     }

     glBegin(GL_QUADS);
        glColor3f(color.x, color.y, color.z);
        if (texture) { glTexCoord2f(XPOS, MAXYPOS); }       glVertex3f(downerLeftCorner.x, downerLeftCorner.y, downerLeftCorner.z);
        if (texture) { glTexCoord2f(XPOS, YPOS); }          glVertex3f(upperLeftCorner.x, upperLeftCorner.y, upperLeftCorner.z);
        if (texture) { glTexCoord2f(MAXXPOS, YPOS); }       glVertex3f(upperRightCorner.x, upperRightCorner.y, upperRightCorner.z);
        if (texture) { glTexCoord2f(MAXXPOS, MAXYPOS); }    glVertex3f(downerRightCorner.x, downerRightCorner.y, downerRightCorner.z);
     glEnd();

     if (texture)
        glDisable(GL_ALPHA_TEST);
     glPopMatrix();
}
