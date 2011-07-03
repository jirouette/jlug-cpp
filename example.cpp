#include "example.hpp"

void game(void)
 {
    jlug::Window win(800, 600, "hello world ! ");
    jlug::ImageManager IM;
    jlug::Character perso(4, "", IM), second(3, "", IM);
    jlug::Input input = win.getInput();
    jlug::Map map("map.tmx", IM);

    perso.setCoord(0, 3);
    perso.setSpeed(5);
    perso.setMove(jlug::Move::RIGHT);
    int i = -16;
    while(!input[jlug::KeyCode::Escape] && win.isOpen())
    {
        //win.processEvents(); // Facultative because isOpen() does processEvents().
        if (input[jlug::KeyCode::Space])
            perso.setMove(jlug::Move::DOWN, 8);
        if (input[jlug::KeyCode::Enter])
            perso.setMove(jlug::Move::LEFT, 5);
        if (input[jlug::KeyCode::Ctrl])
            perso.setMove(jlug::Move::NONE);
        perso.move(map);
        if (input[jlug::KeyCode::Left])
            map.xscroll-= 16;
        else if (input[jlug::KeyCode::Right])
            map.xscroll+= 16;

        if (input[jlug::KeyCode::Up])
            map.yscroll-= 16;
        else if (input[jlug::KeyCode::Down])
            map.yscroll+= 16;

        if (map.xscroll < 0)
            map.xscroll = 0;
        else if (map.xscroll >= map.getWidth()*map.getTileWidth()-win.getWidth())
            map.xscroll = map.getWidth()*map.getTileWidth()-win.getWidth();


        if (map.yscroll < 0)
            map.yscroll = 0;
        else if (map.yscroll >= map.getHeight()*map.getTileHeight()-win.getHeight())
            map.yscroll = map.getHeight()*map.getTileHeight()-win.getHeight();


        win.clear();
        for (unsigned int k(0);k<map.getLayersSize();++k)
            map.displayLayer(win, k);
        second.display(map, win);
        perso.display(map, win);
        win.flip();
    }
    win.close();
 }

