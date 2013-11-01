#include "models/renderer.hpp"

jlug::Renderer::Renderer()
{}

jlug::Renderer::~Renderer()
{}

void jlug::Renderer::draw()
{
	for (std::list<jlug::Polygon>::iterator it(polygons.begin()) ; it != polygons.end() ; ++it)
		it->draw();
}

void jlug::Renderer::translate(const double& x, const double& y, const double& z)
{
	for (std::list<jlug::Polygon>::iterator it(polygons.begin()) ; it != polygons.end() ; ++it)
		it->translate(x, y, z);
}

void jlug::Renderer::rotate(const double& x, const double& y, const double& z)
{
	for (std::list<jlug::Polygon>::iterator it(polygons.begin()) ; it != polygons.end() ; ++it)
		it->rotate(x, y, z);
}

void jlug::Renderer::scale(const double& x, const double& y, const double& z)
{
	for (std::list<jlug::Polygon>::iterator it(polygons.begin()) ; it != polygons.end() ; ++it)
		it->scale(x, y, z);
}

void jlug::Renderer::cancelTransformations()
{
	for (std::list<jlug::Polygon>::iterator it(polygons.begin()) ; it != polygons.end() ; ++it)
		it->cancelTransformations();
}
