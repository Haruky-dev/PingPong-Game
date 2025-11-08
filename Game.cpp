#include "Game.hpp"

#include "Assets.hpp"

#include <print>

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

    // sf::Vertex direcLine[2] = {
    //     sf::Vertex( ball->getPos(), sf::Color::Green ),
    //     sf::Vertex( sf::Vector2f(P2->getPos().x, ball->getPos().y), sf::Color::Green )
    // };
    
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
        //     // sf::Vector2i mousePos = sf::Mouse::getPosition( *win );
        //     // std::println(" Mouse [x: {}, y: {}]", mousePos.x, mousePos.y);
        // } accTime += dt;

        F.UpdateState( dt );
        P1->UpdateState( dt );
        P2->UpdateAI( dt, *ball );
        ball->UpdateState( dt );

        // direcLine[0].position = ball->getPos();
        // direcLine[1].position = {
        //     P2->getPos().x, P2->getPos().y
        // };
        // direcLine[1].position = ball->getDirec() + ball->getPos();


        // direcLine1[0] = direcLine[0];
        // direcLine1[0].color = sf::Color::Cyan;
        // direcLine1[1].position = P2->getPos();



        win->clear();

        win->draw( Assets::getInst().getBg() );
        win->draw( Assets::getInst().getScore(1) );
        win->draw( Assets::getInst().getScore(2) );
        win->draw( *P1 );
        win->draw( *P2 );
        win->draw( *ball );
        win->draw( F );

        // win->draw( direcLine, 2, sf::Lines );

        win->display();
    }
}