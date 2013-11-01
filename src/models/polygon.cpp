#include "polygon.hpp"

jlug::Polygon::Polygon():mode(GL_POLYGON), faces(0)
{}

jlug::Polygon::Polygon(GLenum m, size_t n):mode(m), faces(n)
{}

jlug::Polygon::~Polygon()
{}

void jlug::Polygon::setVertex(size_t index, const jlug::Point& vertex)
{
	if (index >= faces && faces > 0)
		return;
	if (index >= vertices.size())
		vertices.resize(index+1);
	vertices[index] = vertex;
}

void jlug::Polygon::setVertex(size_t index, const jlug::Point& vertex, const jlug::Point& texturePoint)
{
	setVertex(index, vertex);
	setTexturePoint(index, texturePoint);
}

void jlug::Polygon::setTexturePoint(size_t index, const jlug::Point& texturePoint)
{
	if (index >= faces && faces > 0)
		return;
	if (index >= texturePoints.size())
		texturePoints.resize(index+1);
	texturePoints[index] = texturePoint;
}

void jlug::Polygon::addVertex(const jlug::Point& vertex)
{
	setVertex(vertices.size(), vertex);
}

void jlug::Polygon::addVertex(const jlug::Point& vertex, const jlug::Point& texturePoint)
{
	addVertex(vertex);
	addTexturePoint(texturePoint);
}

void jlug::Polygon::addTexturePoint(const jlug::Point& texturePoint)
{
	setTexturePoint(texturePoints.size(), texturePoint);
}


void jlug::Polygon::draw()
{
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

	glBegin(mode); // Drawing the shape
		glColor3f(color.x, color.y, color.z);
		for (size_t i(0) ; i < vertices.size() ; ++i)
		{
			jlug::Point& pt(vertices[i]);
			if (texture && texturePoints.size() > i)
				glTexCoord2f((textureSize.x+texturePoints[i].x)/textureSize.w, (textureSize.y+texturePoints[i].y)/textureSize.h);
			glVertex3f(pt.x, pt.y, pt.z);
		}
	glEnd();

	if (texture)
		glDisable(GL_ALPHA_TEST);
	glPopMatrix(); // restoring the previous matrix
}
