#include "tmxfile.hpp"

jlug::TmxFile::TmxFile(const std::string& filename):
                        doc(filename.c_str())
{
    doc.LoadFile();
}

jlug::TmxFile::~TmxFile()
{}

std::string jlug::TmxFile::getMapProperty(const std::string& property)
{
    TiXmlHandle hdl(&doc);
    TiXmlElement* elem = hdl.FirstChildElement().FirstChildElement().FirstChildElement().Element();
    while(elem)
    {
        if (elem->Attribute("name") == property)
            return elem->Attribute("value");
        elem = elem->NextSiblingElement();
    }
    return "(null)";
}
