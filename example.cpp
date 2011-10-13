#include "example.hpp"
#include "shape.hpp"
#include "square.hpp"

void game(void)
 {
    jlug::Window win(800, 600, "hello world ! ");
    jlug::Input input = win.getInput();
    jlug::Player player(4, "", input, win);
    jlug::AnimatedCharacter second(1, "");
    jlug::Map map("map.tmx");

    player.setCoord(0, 3);
    second.setCoord(5, 5);

    while(!input[jlug::KeyCode::Escape] && win.isOpen())
    {
        //win.processEvents(); // Facultative because isOpen() does processEvents().
        win.clear();

        player.move(map); // hi ! 
        for (unsigned int k(0);k<map.getLayersSize();++k)
            map.displayLayer(win, k);
        second.display(map, win);
        player.display(map, win);
        
        win.flip();
    }
    win.close();
 }