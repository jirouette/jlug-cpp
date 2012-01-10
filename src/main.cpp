#include <iostream>
#include "utils/constants.hpp"
#include "example.hpp"

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
    }
    else
    {
        jlug::Constants::getInstance().set("exec", "");
        jlug::Constants::getInstance().set("path", "./");
    }

    jlug::Constants::getInstance().set("charsets", "../res/charsets/");

    game();
    return 0;
}
