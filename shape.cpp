#include "shape.hpp"

jlug::Shape::Shape(void)
{}

jlug::Shape::~Shape(void)
{}

void jlug::Shape::square(const jlug::Point& center, double size, const jlug::Rect& textureSize, const jlug::Rect& rawSize, GLuint* texture)
{
    double HORIZONTAL(static_cast<double>(rawSize.w)/static_cast<double>(textureSize.w)), 
           VERTICAL(static_cast<double>(rawSize.h)/static_cast<double>(textureSize.h)),
           XPOS(static_cast<double>(rawSize.x+textureSize.x)/static_cast<double>(textureSize.w)),
           YPOS(static_cast<double>(rawSize.y+textureSize.y)/static_cast<double>(textureSize.h)),
           MAXXPOS(static_cast<double>(rawSize.x+textureSize.w)/static_cast<double>(textureSize.w)),
           MAXYPOS(static_cast<double>(rawSize.y+textureSize.h)/static_cast<double>(textureSize.h));
    
     glPushMatrix();
     glTranslatef(center.x*1.f, center.y*1.f, center.z*1.f);
     glScalef(size, size, size);
     if (texture)
     {
         glBindTexture(GL_TEXTURE_2D, *texture);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
         glEnable(GL_ALPHA_TEST);
         glAlphaFunc(GL_GREATER, 0.0f);
     }


     glBegin(GL_QUADS);
        glColor3f(1.f, 1.f, 1.f);
        if (texture) { glTexCoord2f(XPOS/HORIZONTAL, MAXYPOS/VERTICAL); }       glVertex3f(0.f, 0.f, 0.f);
        if (texture) { glTexCoord2f(XPOS/HORIZONTAL, YPOS/VERTICAL); }          glVertex3f(0.f, 1.f, 0.f);
        if (texture) { glTexCoord2f(MAXXPOS/HORIZONTAL, YPOS/VERTICAL); }       glVertex3f(1.f, 1.f, 0.f);
        if (texture) { glTexCoord2f(MAXXPOS/HORIZONTAL, MAXYPOS/VERTICAL); }    glVertex3f(1.f, 0.f, 0.f);
     glEnd();

     if (texture)
        glDisable(GL_ALPHA_TEST);
     glPopMatrix();
}