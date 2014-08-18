#include <iostream>
#include "utils/constants.hpp"
#include "scripts/script.hpp"

int main(int argc, char* argv[])
{
    if (argc > 0)
    {
        std::string path(argv[0]);
        size_t filePos(path.find_last_of("/\\"));

        jlug::Constants::getInstance().set("exec", path);

        if (filePos != std::string::npos)
            jlug::Constants::getInstance().set("path", 
                    path.substr(0, filePos)+'/');
        else
            jlug::Constants::getInstance().set("path", "./");
        
        for (int i(0); i < argc ; ++i)
        {
            std::ostringstream oss;
            oss << "argv[" << i << "]";
            jlug::Constants::getInstance().set(oss.str(), argv[i]);
        }
    }
    else
    {
        jlug::Constants::getInstance().set("argv[0]", "");
        jlug::Constants::getInstance().set("exec", "");
        jlug::Constants::getInstance().set("path", "./");
    }

    jlug::Constants::getInstance().set("git_version", GIT_VERSION);
    jlug::Constants::getInstance().set("charsets", "../res/charsets/");

    jlug::Script("../scripts/main.lua");
    jlug::Script::end();
    return 0;
}
