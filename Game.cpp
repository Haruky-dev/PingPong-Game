#include "Game.hpp"

#include "Assets.hpp"

#include <iostream>

Game::Game() : F() {

    win = std::make_unique<sf::RenderWindow>( 
        sf::VideoMode( Utils::WIDTH, Utils::HEIGHT ), "PingPong Game :)"
    );

    dt = sf::Time::Zero;
    clk = sf::Clock();
}

// handle resources loading
void Game::load() {
    // load data

    Assets::getInst().loadResources();

    // create players
    Game::P1 = std::make_unique<Player>( Assets::getInst().getPad() );
    Game::P2 = std::make_unique<Player>( Assets::getInst().getPad() );

    // create ball
    Game::ball = std::make_unique<Ball>( Assets::getInst().getBall() );
    ball->setPlayers( *P1, *P2 );
}

void Game::run() {

    this->load();

    // for DBG msgs
    // sf::Time accTime = sf::Time::Zero;

    while ( win->isOpen() ) {

        dt = clk.restart();

        sf::Event ev;
        while ( win->pollEvent(ev) )
            if ((ev.type == sf::Event::Closed) ||
                (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) )
                    win->close();
        
        // DBG
        // if (accTime.asSeconds() >= 0.5f) {
        //     accTime = sf::Time::Zero;
        //     // std::cout<< sf::Mouse::getPosition( *win ).x << ' ' << sf::Mouse::getPosition( *win ).y << '\n';
        //     P1->getScore();
        //     P2->getScore();
        // } accTime += dt;

        F.UpdateState( dt );
        P1->UpdateState( dt );
        P2->UpdateState( dt );
        ball->UpdateState( dt );

        win->clear();

        win->draw( Assets::getInst().getBg() );
        win->draw( Assets::getInst().getScore(1) );
        win->draw( Assets::getInst().getScore(2) );
        win->draw( *P1 );
        win->draw( *P2 );
        win->draw( *ball );
        win->draw( F );

        win->display();
    }
}