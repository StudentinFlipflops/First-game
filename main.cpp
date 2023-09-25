#include <iostream>
#include "game.h"

int main()
{   
    // Init srand 
    
    std::srand(static_cast<unsigned>(time(NULL)));

    //window stuff
    //init game engine
    Game game;


    // magic began here
    while (game.getWindowIsOpen() && !game.getEndGame())
    {
        game.update();
        game.render();

    }


    //fck this exit
    return 0;
}




