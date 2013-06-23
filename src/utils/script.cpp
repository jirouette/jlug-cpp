#include "script.hpp"

std::list<jlug::Script*> jlug::Script::scripts = jlug::Script::initScripts();

std::list<jlug::Script*> jlug::Script::initScripts()
{
	std::list<jlug::Script*> l;
	return l;
}

jlug::Script::Script()
{
	scripts.push_back(this);
}

jlug::Script::~Script()
{
	scripts.remove(this);
}
