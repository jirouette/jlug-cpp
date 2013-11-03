#include "script.hpp"

std::map<lua_State*, jlug::Script*> jlug::Script::scripts = jlug::Script::initScripts();

std::map<lua_State*, jlug::Script*> jlug::Script::initScripts()
{
	std::map<lua_State*, jlug::Script*> m;
	return m;
}

void jlug::Script::end()
{
	for(std::map<lua_State*, jlug::Script*>::iterator it(scripts.begin()) ; it != scripts.end() ; ++it)
		if ((*it).second->special)
		{
			delete (*it).second;
			end();
			break;
		}
}

int jlug::Script::createScript(lua_State *state)
{
	int n(lua_gettop(state));
	for (int i(1); i <= n ; ++i)
		if (lua_isstring(state, i))
			new jlug::Script(lua_tostring(state, i), true);
	return 0;
}

jlug::Script::Script(const std::string& filename, bool s):name(filename)
{
	special = s || true;
	init();
}

jlug::Script::Script(const std::string& filename):name(filename)
{
	init();
}

void jlug::Script::init()
{
	L = luaL_newstate();
	luaL_openlibs(L);
	lua_register(L, "script", jlug::Script::createScript);
	Lunar<jlug::Window>::Register(L);
	Lunar<jlug::Input>::Register(L);
	Lunar<jlug::Map>::Register(L);
	Lunar<jlug::Character>::Register(L);
	working = !(luaL_loadfile(L, (jlug::Constants::getInstance().get("path")+name).c_str()) || lua_pcall(L, 0, 0, 0));
	if (!working)
		error() << "Cannot read '" << name << "' : " << lua_tostring(L, -1) << std::endl;
	call("init", 0, "");
	scripts.insert(std::pair<lua_State*, jlug::Script*>(L, this));
}

jlug::Script::~Script()
{
	if (working)
		lua_close(L);
	scripts.erase(L);
	print() << "Terminated. " << std::endl;
	flush();
}

void jlug::Script::call(const std::string& function, int nbargs, const std::string& param, ...)
{
	if (!working)
		return;
	lua_getglobal(L, function.c_str());
	if (!lua_isfunction(L,-1))
	{
		lua_pop(L, 1);
		error() << "Error : '" << function << "' is not a function" << std::endl;
		return;
	}

	if (nbargs > 0)
	{
		va_list vl;
		va_start(vl, param);
		lua_pushvfstring(L, param.c_str(), vl);
		va_end(vl);
	}

	working = !lua_pcall(L, nbargs, 0, 0);
	if (!working)
		error() << "Error with function '" << function << "' : " << lua_tostring(L, -1) << std::endl;
}

std::ostringstream& jlug::Script::error()
{
	err << '[' << name << "] ";
	return err;
}

std::ostringstream& jlug::Script::print()
{
	out << '[' << name << "] ";
	return out;
}

void jlug::Script::flush()
{
	std::cout << out.str();
	std::cerr << err.str();
}
