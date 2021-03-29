#include <bits/stdc++.h>
#include "Game.h"
//using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//using namespace sf;

int main()
{
    //init srand

    std::srand(static_cast<unsigned>(time(NULL)));

    //initializing game engine
    Game game;

    //game loop !!!!!!!!!!!!!!!

    while(game.running() && !game.getEndGame()){

        //update window
        game.update();


        //RENDERING
        game.render();


    }






    return 0;

}
