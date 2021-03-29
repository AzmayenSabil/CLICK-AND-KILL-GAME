#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
    this class acts as a game engine
*/

class Game
{
    public:

        //Constructor & destructor
        Game();
        virtual ~Game();
        //-----------------------//

        //accessors
        const bool running() const;
        const bool getEndGame() const;
        //----------------------//

        //functions
        void spawnEnemy();
        void pollEvents();

        void updateMousePositions();
        void updateEnemies();
        void updateText();
        void update();

        void renderText(sf::RenderTarget& target);
        void renderEnemies(sf::RenderTarget& target);
        void render();
        //----------------------//

    protected:

    private:

        //window
        sf::RenderWindow* window; //pointer
        sf::VideoMode videoMode;
        sf::Event ev;

        //mouse position -> to determine where the mouse pointer is
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosView;

        //resources
        sf::Font font;

        //text
        sf::Text uiText;

        //related to game logic
        bool endGame;
        unsigned points;
        int health;
        float enemySpawnTimer;
        float enemySpawnTimerMax;
        int maxEnemies;
        bool mouseHeld;


        //game objects
        std::vector<sf::RectangleShape> enemies;
        sf::RectangleShape enemy;

        //private functions
        void initVariable();
        void initWindow();
        void initFonts();
        void initText();
        void initEnemies();
};

#endif // GAME_H
