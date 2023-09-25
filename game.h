#ifndef GAME_H
#define GAME_H




#include <iostream>
#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>


/*
Class that acts like game engine


*/



class Game
{
    private:
        //Variables


        //window 
        sf::RenderWindow* window; 
        sf::VideoMode videomode;
        sf::Event ev; 


        // mouse positions
        sf::Vector2i mousePosWindow; 
        sf::Vector2f mousePosView; 
        
        //resoources 
        sf::Font Font ;         


        //TEXT
        sf::Text uitext; 


        //game logic

        unsigned points;
        int health; 
        float enemySpawnTimer;
        float enemySpawnTimerMax;
        int maxEnemies;
        bool endGame; 
        bool mouseHeld; 

        // game objects 
        sf::RectangleShape enemy; 
        std::vector<sf::RectangleShape> enemies; 


        //Private functions
        void initvariables();
        void initwindow();
        void initFonts();
        void initText();
        void initenemies();
    
    
    public: 

        // section of constructos and destructors
        Game();
        virtual ~Game();

        //accesors
        const bool getWindowIsOpen() const ;
        const bool getEndGame() const ; 

        //methots
        void spawnEnemy();



        void pollEvents();
        void updateMousePositions();
        void updateText();
        void updateEnemies();
        void update();


        void renderText(sf::RenderTarget& target );
        void renderEnemies(sf::RenderTarget& target );
        void render();
};


#endif