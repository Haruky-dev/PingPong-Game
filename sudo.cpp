#include <SFML/Graphics.hpp>

#include "Utils.hpp"
#include "Player.hpp"
#include "Ball.hpp"

#include <iostream>

int main( void ) {
    sf::RenderWindow win( sf::VideoMode( Utils::WIDTH, Utils::HEIGHT ), "PingPong");

    sf::Time deltaTime = sf::Time::Zero;
    sf::Clock Clk;
    Utils::FrameRate F;

    sf::Time accTime = sf::Time::Zero;
    double delay = 0.8f;

    Player p1( sf::Color::Yellow, sf::Color::White );
    Player p2( sf::Color::Cyan, sf::Color::White );
    Ball ball;

    while ( win.isOpen() ) {
        deltaTime = Clk.restart();
        
        sf::Event ev;
        while ( win.pollEvent(ev) )
            if ((ev.type == sf::Event::Closed ) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) )
                win.close();

        if ( accTime.asSeconds() >= delay ) {
            accTime = sf::Time::Zero;
            std::cout<< sf::Mouse::getPosition(win).x << ' ' << sf::Mouse::getPosition(win).y << '\n';
            // std::cout<< ball.getDirec().x << ' ' << ball.getDirec().y << '\n';
        }   accTime += deltaTime;
                
        F.UpdateState(deltaTime);
        p1.UpdateState(deltaTime);
        p2.UpdateState(deltaTime);
        ball.UpdateState(deltaTime);


        win.clear();

        win.draw(F);
        win.draw(ball);
        win.draw(p1);
        win.draw(p2);
        
        win.display();
    }
}