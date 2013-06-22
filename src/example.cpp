#include "example.hpp"
#include "models/shape.hpp"
#include "models/square.hpp"
#include "utils/resourcemanager.hpp"
#include "utils/constants.hpp"
#include <iostream>

void game(void)
 {
    jlug::Window win(800, 600, "hello world ! ");
    jlug::Input input = win.getInput();

    std::list<jlug::Character*> characters;

    characters.push_back(new jlug::Player(4, "jr", input, win));
    characters.push_back(new jlug::Character(3, ""));
    characters.push_back(new jlug::AnimatedCharacter(1, ""));
    jlug::Map map("../res/maps/map.tmx");


    std::list<jlug::Character*>::iterator it(characters.begin());

    (*it)->setCoord(10, 35);
    (*++it)->setCoord(25, 40);
    (*++it)->setCoord(10, 10);

    while(!input[jlug::KeyCode::Escape] && win.isOpen())
    {
        //win.processEvents(); // Facultative because isOpen() does processEvents().
        win.clear();

        //first.setMove(map, jlug::Move::NONE);
        //first.setMove(map, player.getPosition(), 5);

        //first.move(map);

        //player.move(map); // hi ! 

        for(std::list<jlug::Character*>::iterator character(characters.begin()) ; character != characters.end() ; ++character)
            (*character)->move(map);


        for (unsigned int k(0);k<map.getDepth();++k)
            map.displayLayer(win, k);
        

        for(std::list<jlug::Character*>::iterator character(characters.begin()) ; character != characters.end() ; ++character)
            (*character)->display(map, win);


        //player.displayUsername(win);
        
        win.flip();
    }
    win.close();
 }
