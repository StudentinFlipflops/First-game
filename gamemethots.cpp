#include "game.h"
//#include <ctime>
//#include <vector>
//#include <SFML/Graphics.hpp>

//private methots ****************************************************************************************************

void Game::initvariables()
{
    this->window = nullptr;

    this->points = 0 ;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5; 
    this->mouseHeld = false ;
    this->health = 10 ;
    this->endGame = false ; 




}


void Game::initwindow()
{
    this->videomode.height = 500; 
    this->videomode.width = 500;
    this->window  = new sf::RenderWindow(this->videomode, "balls" , sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}


void Game::initFonts()
{
    if(this->Font.loadFromFile("fonts/Metropolian-Display.ttf"))
    {
        std::cout<<"ERROR::GAME::INITFONTS::Failed to load font!!!" << std::endl;  
    }

}

void Game::initText()
{
    this->uitext.setFont(this->Font); 
    this->uitext.setCharacterSize(24); 
    this->uitext.setFillColor(sf::Color::White); 
    this->uitext.setScale(1.f , 1.f );
    this->uitext.setString("none");
}

void Game::initenemies()
{
    this->enemy.setPosition(sf::Vector2f(50.f,50.f));
    this->enemy.setSize(sf::Vector2f(25.f , 25.f));
    this->enemy.setFillColor(sf::Color::Red);
    //this->enemy.setOutlineColor(sf::Color::Blue);
    // this->enemy.setOutlineThickness(1.f);




}

//constructor  Destructors ****************************************************************************************************

Game::Game()
{
    this-> initvariables();
    this->initwindow();
    this->initenemies();
    this->initFonts();
    this->initText();
}

 Game::~Game()
{
    delete this-> window;
}



// Accesors  ****************************************************************************************************
const bool Game::getWindowIsOpen() const 
{
    return this->window->isOpen();
}

const bool Game::getEndGame() const 
{
    return this->endGame; 
}

// methots ****************************************************************************************************




void Game::spawnEnemy(){
        
    // spawn the enemy and sets colora and position( all random )

    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)), 
        0.f
    );

    //randomize enemy type
    int type = rand() % 5 ;
    
    switch (type)
    {
    case 0 :
        this->enemy.setFillColor(sf::Color::Red); 
        this->enemy.setSize(sf::Vector2f(20.f , 20.f));
        
        break;
    
    case 1 :
        this->enemy.setFillColor(sf::Color::Magenta); 
        this->enemy.setSize(sf::Vector2f(40.f , 40.f));
        
        break;
    
    case 2 :
        this->enemy.setFillColor(sf::Color::Cyan); 
        this->enemy.setSize(sf::Vector2f(50.f , 50.f));
        
        break;
    
    case 3 :
        this->enemy.setFillColor(sf::Color::Blue); 
        this->enemy.setSize(sf::Vector2f(70.f , 70.f));
        
        break;
    
    case 4 :
        this->enemy.setFillColor(sf::Color::Green); 
        this->enemy.setSize(sf::Vector2f(100.f , 100.f));
        
        break;
    
    default:
            this->enemy.setFillColor(sf::Color::Yellow); 
            this->enemy.setSize(sf::Vector2f(1000.f , 1000.f));
        
        break;
    
    }



    this->enemies.push_back(this->enemy);



}


void Game::pollEvents()
{
    while(this->window->pollEvent(this->ev))
    {

        switch (this->ev.type )
        {
        case sf::Event::Closed:

            this->window->close();
            break;

        case sf::Event::KeyPressed:

            if(this->ev.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
            }
            break;

        default:
            break;
        }
    }

}



//update 

void Game::updateMousePositions()
{
    /*
        return void

        updates mouse positions:
            *Mouse relative to window (vector2i)
    */

    this->mousePosWindow = sf::Mouse::getPosition(*this->window); 
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow); 
}


void Game::updateText()
{
    std::stringstream ss; 

    ss<<"points: " << this->points <<"\nhealth: " << this-> health ;
    
    
    this->uitext.setString(ss.str());


}

void Game::updateEnemies(){


    /*
     ...
    */

    // Updating the timer for enemy spawning

    if((int)this->enemies.size() < this->maxEnemies)
    {


        if(this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {

        
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
           this->enemySpawnTimer += 1.f;


    }

    //move the enemies

    for(int i = 0 ; i < (int)this->enemies.size(); i++)
    {      
        this-> enemies[i].move(0.f, 3.f);

        if(this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() +i);
            this->health--;
            // std::cout<< "health: " << this->health << std::endl ; 

        }
    
    }

        //check if clicked  upon

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {

        if(this->mouseHeld == false)
        {
            this->mouseHeld = true; 
            bool deleted =false ; 

            for(size_t i = 0 ; i<this->enemies.size() && deleted ==false ; i++)
            {
            
                if(this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {

                    this->enemies.erase(this->enemies.begin() +i);
                    deleted = true ; 

                    if(this->enemies[i].getFillColor() ==  sf::Color::Red)
                        this->points+= 10 ; 
                    else if(this->enemies[i].getFillColor() ==  sf::Color::Magenta)
                        this->points+= 7 ; 
                    else if(this->enemies[i].getFillColor() ==  sf::Color::Cyan)
                        this->points+= 5 ; 
                    else if(this->enemies[i].getFillColor() ==  sf::Color::Blue)
                        this->points+= 3 ; 
                    else if(this->enemies[i].getFillColor() ==  sf::Color::Green)
                        this->points+= 1 ; 


                         
                    //std::cout<< "points: " << this->points << std::endl ; 

                }

            }   
          
        
        }    
    }
    else 
    {
        this->mouseHeld = false; 
    }


}


void Game::update()
{
    this->pollEvents();
    


    if(this->endGame == false)
    { 
        this->updateEnemies();

        this->updateText();

        this->updateMousePositions();

    }


    //end game contition 
    if(this->health <= 0 )
    {
        this->endGame = true; 
    }
}


//render

void Game::renderText(sf::RenderTarget& target )
{
    target.draw(this->uitext);

}

void Game::renderEnemies(sf::RenderTarget& target )
{

    //  render all enemies
    for(auto &e : this->enemies)
    {
        target.draw(e);
    }
}

void Game::render()
{   
    
    this->window->clear();

    //draw game objects 

    this->renderEnemies(*this->window);
    this->renderText(*this->window);

    this->window->display();

}

