#include "example.hpp"
#include "models/shape.hpp"
#include "models/square.hpp"
#include "utils/resourcemanager.hpp"
#include "utils/constants.hpp"
#include "utils/script.hpp"
#include <iostream>

void game(void)
 {
    jlug::Window win(800, 600, "hello world ! ");
    jlug::Input input = win.getInput();

    jlug::Map map("../res/maps/map.tmx", win, input);

    //map.addCharacter(new jlug::Player(4, "jr", input, win));
    /*map.addCharacter(new jlug::Character(3, ""));
    map.addCharacter(new jlug::AnimatedCharacter(1, ""));*/


    /*(*it)->setCoord(10, 35);
    (*++it)->setCoord(25, 40);
    (*++it)->setCoord(10, 10);*/

    jlug::Script coucou("scripts/init.lua");
    coucou.call("main", 1, "%s", "jlug");

    while(!input[jlug::KeyCode::Escape] && win.isOpen())
    {
        //win.processEvents(); // Facultative because isOpen() does processEvents().
        win.clear();

        //first.setMove(map, jlug::Move::NONE);
        //first.setMove(map, player.getPosition(), 5);

        //first.move(map);

        //player.move(map); // hi ! 

        map.moveCharacters();
        for (unsigned int k(0);k<map.getDepth();++k)
            map.displayLayer(win, k);
        map.displayCharacters(win);
        


        //player.displayUsername(win);
        
        win.flip();
    }
    win.close();
    jlug::Script::end();

 }
