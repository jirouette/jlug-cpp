#include "example.hpp"
#include "models/shape.hpp"
#include "models/square.hpp"
#include "utils/resourcemanager.hpp"
#include "utils/constants.hpp"
#include "utils/script.hpp"
#include "models/polygon.hpp"
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

    std::string charsetFilename;
    charsetFilename = jlug::Constants::getInstance().get("path");
    charsetFilename += jlug::Constants::getInstance().get("charsets");
    charsetFilename += "4.png";

    std::list<jlug::Character*>::iterator it(characters.begin());

    (*it)->setCoord(10, 35);
    (*++it)->setCoord(25, 40);
    (*++it)->setCoord(10, 10);

    jlug::Script coucou("scripts/init.lua");
    coucou.call("main", 1, "%s", "jlug");

    jlug::Image& sprite(jlug::ImageManager::getInstance()[charsetFilename]);
    //jlug::Square p;
    /*jlug::Polygon p(GL_TRIANGLES, 10);
    p.addVertex(jlug::Point(0, 0, 0), jlug::Point(0, 25, 0));
    p.addVertex(jlug::Point(0, 1, 0), jlug::Point(0, 0, 0));
    p.addVertex(jlug::Point(1, 1, 0), jlug::Point(19, 0, 0));
    //p.addVertex(jlug::Point(1, 0, 0), jlug::Point(19, 25, 0));
    //p.addVertex(jlug::Point(1, 0, 2));
    p.setPixelTranslation(16, 16);
    p.setColor(255, 255, 255);
    p.setPosition(jlug::Point(20, 30, 1));
    p.scale(19, 25, 1);
    p.rotate(30, 0, 0);
    p.setTextureSize(0, 0, sprite.getRealWidth(), sprite.getRealHeight());
    p.setTextureZone(0, 0, 19, 25);
    p.setTexture(sprite.getTexture());*/
    jlug::ObjRenderer objr("BR_Umbreon.obj");
    objr.setColor(255, 255, 255);
    //objr.setPosition(jlug::Point(99990, 99990, 99990));

    //objr.translate(30, 30, 2);


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
        //p.draw();
        objr.rotate(180, 0, 0);
        objr.translate(0, -20, 0);
        objr.draw();
        win.flip();
    }
    win.close();
    jlug::Script::end();

 }
