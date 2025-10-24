#include "Game.hpp"

#include <print>

Game::Game() : F() {

    win = std::make_unique<sf::RenderWindow>( 
        sf::VideoMode( Utils::WIDTH, Utils::HEIGHT ), "PingPong Game :)"
    );

    dt = sf::Time::Zero;
    clk = sf::Clock();
    
    P1 = std::make_unique<Player>( 
        sf::Color::Yellow, sf::Color::White
    );
    P2 = std::make_unique<Player>( 
        sf::Color::Cyan, sf::Color::White
    );
    
    ball = std::make_unique<Ball>();
    ball->setPlayers( *P1, *P2 );

}


void Game::load() {}

void Game::run() {

    while ( win->isOpen() ) {


        dt = clk.restart();

        sf::Event ev;
        while ( win->pollEvent(ev) )
            if ((ev.type == sf::Event::Closed) ||
                (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) )
                    win->close();
                   
        F.UpdateState( dt );
        P1->UpdateState( dt );
        P2->UpdateState( dt );
        ball->UpdateState( dt );


        win->clear();

        win->draw( *P1 );
        win->draw( *P2 );
        win->draw( *ball );
        win->draw( F );

        win->display();
    }
}