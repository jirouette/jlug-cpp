#include "example.hpp"
#include "models/shape.hpp"
#include "models/square.hpp"
#include "utils/resourcemanager.hpp"
#include "utils/constants.hpp"
#include "scripts/script.hpp"
#include <iostream>

void game(void)
 {
    jlug::Window win(800, 600, "hello world ! ");
    jlug::Input input = win.getInput();

    jlug::Map map("../res/maps/map.tmx", win, input);

    jlug::Script coucou("scripts/init.lua");
    coucou.call("main", 1, "%s", "jlug");

    while(!input[jlug::KeyCode::Escape] && win.isOpen())
    {
        //win.processEvents(); // Facultative because isOpen() does processEvents().
        win.clear();

        map.moveCharacters();
        for (unsigned int k(0);k<map.getDepth();++k)
            map.displayLayer(win, k);
        map.displayCharacters(win);
        win.flip();
    }
    win.close();
    jlug::Script::end();

 }
