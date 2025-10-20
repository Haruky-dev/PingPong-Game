#include <SFML/Graphics.hpp>

#include "Utils.hpp"
#include "Player.hpp"
#include "Ball.hpp"

#include <iostream>

int main( void ) {
    sf::RenderWindow win( sf::VideoMode( Utils::WIDTH, Utils::HEIGHT ), "PingPong");

    sf::Time dt = sf::Time::Zero;
    sf::Clock Clk;
    Utils::FrameRate F;

    sf::Time accTime = sf::Time::Zero;
    double delay = 0.8f;

    Player p1( sf::Color::Yellow, sf::Color::White );
    Player p2( sf::Color::Cyan, sf::Color::White );

    Ball ball;
    ball.setPlayers( p1, p2 );

    while ( win.isOpen() ) {
        dt = Clk.restart();
        
        sf::Event ev;
        while ( win.pollEvent(ev) )
            if ((ev.type == sf::Event::Closed ) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) )
                win.close();

        if ( accTime.asSeconds() >= delay ) {
            accTime = sf::Time::Zero;
            // std::cout<< sf::Mouse::getPosition(win).x << ' ' << sf::Mouse::getPosition(win).y << '\n';
            // std::cout<< ball.getDirec().x << ' ' << ball.getDirec().y << '\n';
        }   accTime += dt;
                
        F.UpdateState(dt);
        p1.UpdateState(dt);
        p2.UpdateState(dt);
        ball.UpdateState(dt);


        win.clear();

        win.draw(F);
        win.draw(ball);
        win.draw(p1);
        win.draw(p2);
        
        win.display();
    }
}