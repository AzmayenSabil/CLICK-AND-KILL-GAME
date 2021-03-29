#include "Game.h"


void Game::initVariable(){
    this->window = nullptr;

    //game logic variable initialization
    this->endGame = false;
    this->points = 0;
    this->health = 10;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
    this->mouseHeld = false;
}

void Game::initWindow(){
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "A DEMO GAME - 1", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initFonts(){
    if(this->font.loadFromFile("fonts/Youtube-Star.ttf")){
        std::cout<<"Successfully Loaded"<<"\n";
    }
}

void Game::initText(){
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

void Game::initEnemies(){

    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setFillColor(sf::Color::Cyan);
}

//constructor & destructor

Game::Game()
{
    this->initVariable();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initEnemies();
}

Game::~Game()
{
    delete this->window;
}

//Accessors

const bool Game::running() const{
    return this->window->isOpen();
}

const bool Game::getEndGame() const{
    return this->endGame;
}


//function-----------------------****

void Game::spawnEnemy(){

    this->enemy.setPosition(
        static_cast<float>(rand()%static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f

        //randomly spawning enemy

    );

    //randomizing enemy type
    int type = rand()%5;

    switch(type){
    case 0:
        this->enemy.setSize(sf::Vector2f(10.f, 10.f));
        this->enemy.setFillColor(sf::Color::Magenta);
        break;
    case 1:
        this->enemy.setSize(sf::Vector2f(30.f, 30.f));
        this->enemy.setFillColor(sf::Color::Blue);
        break;
    case 2:
        this->enemy.setSize(sf::Vector2f(50.f, 50.f));
        this->enemy.setFillColor(sf::Color::Green);
        break;
    case 3:
        this->enemy.setSize(sf::Vector2f(70.f, 70.f));
        this->enemy.setFillColor(sf::Color::Cyan);
        break;
    case 4:
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        this->enemy.setFillColor(sf::Color::Red);
        break;

    default:
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        this->enemy.setFillColor(sf::Color::Yellow);
        break;
    }



    this->enemies.push_back(this->enemy);

}


void Game::pollEvents(){
    while(this->window->pollEvent(this->ev)){
        switch(this->ev.type){

        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if(this->ev.key.code == sf::Keyboard::Escape){
                this->window->close();
            }
            break;

        }
    }
}



void Game::updateMousePositions(){

    //window mouse position relative to window

    this->mousePosWindow = sf::Mouse::getPosition(*this->window); //getting the mouse pointer position
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);  //????? didn't quite understand


}


void Game::updateText(){

    std::stringstream ss;

    ss<<"POINTS: "<<this->points<<"\n"
      <<"HEALTH: "<<this->health<<"\n";

    this->uiText.setString(ss.str());
}


void Game::updateEnemies(){

    if(this->enemies.size() < this->maxEnemies)
    {
        if(this->enemySpawnTimer >= this->enemySpawnTimerMax){
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f; // ????
        }else{
            this->enemySpawnTimer += 1.f; // ????
        }
    }

    //moving and updating the enemy

    for(int i=0; i<this->enemies.size(); i++){

        bool deleted = false;

        this->enemies[i].move(0.f,2.f);

        if(this->enemies[i].getPosition().y > this->window->getSize().y){
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
            //std::cout<<"HEALTH: "<<this->health<<"\n";
        }

    }

    //check if clicked upon

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

        if(this->mouseHeld == false){ // how the calling works ? how action event works?

            this->mouseHeld = true;
            bool deleted = false;

            for(size_t i=0; i<this->enemies.size() && deleted == false; i++){

                if(this->enemies[i].getGlobalBounds().contains(this->mousePosView)){

                    if(this->enemies[i].getFillColor() == sf::Color::Magenta)
                        //gain points
                        this->points += 10;
                    else if(this->enemies[i].getFillColor() == sf::Color::Blue)
                        //gain points
                        this->points += 7;
                    else if(this->enemies[i].getFillColor() == sf::Color::Green)
                        //gain points
                        this->points += 5;
                    else if(this->enemies[i].getFillColor() == sf::Color::Cyan)
                        //gain points
                        this->points += 3;
                    else if(this->enemies[i].getFillColor() == sf::Color::Red)
                        //gain points
                        this->points += 1;


                    //std::cout<<"POINTS: "<<this->points<<"\n";

                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                }
            }

        }
    }

    else{
        this->mouseHeld = false;
    }


}



void Game::update(){

    this->pollEvents();

    if(this->endGame == false){

        this->updateMousePositions();

        this->updateText();

        this->updateEnemies();
    }


    //endgame condition
    if(this->health <= 0){

        this->endGame = true;
    }

}

void Game::renderText(sf::RenderTarget& target){

    target.draw(this->uiText);
}


void Game::renderEnemies(sf::RenderTarget& target){

    for(auto &e : this->enemies){
        target.draw(e);
    }
}


void Game::render(){

    /*
        //clear old frame
        //render objects
        //display frame in window

    */

    this->window->clear();

    //draw game objects
    this->renderEnemies(*this->window);

    this->renderText(*this->window);

    this->window->display();
}

