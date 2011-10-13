#include "square.hpp"

jlug::Square::Square(void):Shape()
{}

jlug::Square::~Square(void)
{}

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
        if (texture) { glTexCoord2f(XPOS, MAXYPOS); }       glVertex3f(0.f, 0.f, 0.f);
        if (texture) { glTexCoord2f(XPOS, YPOS); }          glVertex3f(0.f, 1.f, 0.f);
        if (texture) { glTexCoord2f(MAXXPOS, YPOS); }       glVertex3f(1.f, 1.f, 0.f);
        if (texture) { glTexCoord2f(MAXXPOS, MAXYPOS); }    glVertex3f(1.f, 0.f, 0.f);
     glEnd();

     if (texture)
        glDisable(GL_ALPHA_TEST);
     glPopMatrix();
}