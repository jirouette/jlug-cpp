#include "models/objrenderer.hpp"

jlug::ObjRenderer::ObjRenderer(const std::string& file)
{
	std::ifstream f(file.c_str());
	if (f.is_open())
	{
		for(; f.good() ;)
		{
			std::string command;
			f >> command;
			if (command == "v")
			{
				// Vertex : x, y, z
				double x, y, z;
				f >> x >> y >> z;
				v.push_back(jlug::Point(x, y, z));
			}
			else if (command == "vt")
			{
				// Vertex texture : x, y
				double x, y;
				f >> x >> y;
				vt.push_back(jlug::Point(x, y, 0.0));
			}
			else if (command == "vn")
			{
				// Vertex normal : x, y, z
				double x, y, z;
				f >> x >> y >> z;
				vn.push_back(jlug::Point(x, y, z));
			}
			else if (command == "usemtl")
			{
				// URL of the texture
				std::string url;
				f >> url;
				std::cout << "usemtl " << url << std::endl;
				texture = jlug::ImageManager::getInstance()[url].getTexture();
			}
			else if (command == "f")
			{
				// Face : pt1, pt2, pt3
				jlug::ObjRenderer::Face face;
				std::string pt1, pt2, pt3;
				f >> pt1 >> pt2 >> pt3;
				getFacePoint(face.a, pt1);
				getFacePoint(face.b, pt2);
				getFacePoint(face.c, pt3);

				jlug::Polygon p(GL_TRIANGLES, 3);
				p.addVertex(v[face.a.v], vt[face.a.vt]);
				p.addVertex(v[face.b.v], vt[face.b.vt]);
				p.addVertex(v[face.c.v], vt[face.c.vt]);
				p.setTexture(texture);
				polygons.push_back(p);
				faces.push_back(face);
			}
		}
		construct();
	}
}

jlug::ObjRenderer::~ObjRenderer()
{}

void jlug::ObjRenderer::construct()
{
	/*for (std::vector<jlug::ObjRenderer::Face>::iterator it(faces.begin()) ; it != faces.end() ; ++it)
	{
		jlug::Polygon p(GL_TRIANGLES, 3);
		p.addVertex(v[it->a.v], vt[it->a.vt]);
		p.addVertex(v[it->b.v], vt[it->b.vt]);
		p.addVertex(v[it->c.v], vt[it->c.vt]);

		std::cout << "=== POLYGON ===" << std::endl;
		std::cout << '[' << v[it->a.v].x << ';' << v[it->a.v].y << ';' << v[it->a.v].z << "] (" << it->a.v << ") - " << std::endl;
		std::cout << '[' << v[it->b.v].x << ';' << v[it->b.v].y << ';' << v[it->b.v].z << "] (" << it->b.v << ") - " << std::endl;
		std::cout << '[' << v[it->c.v].x << ';' << v[it->c.v].y << ';' << v[it->c.v].z << "] (" << it->c.v << ") - " << std::endl;
		std::cout << "================" << std::endl;
		p.setTexture(texture);
		polygons.push_back(p);
	}*/
	v.clear();
	vt.clear();
	vn.clear();
	faces.clear();
}

void jlug::ObjRenderer::getFacePoint(jlug::ObjRenderer::FacePoint& fp, const std::string& pt)
{
	fp.v = atoi(pt.substr(0, pt.find('/')).c_str()) - 1;
	fp.vt = atoi(pt.substr(pt.find('/')+1).c_str()) - 1;

}
