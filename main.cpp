#include <SFML/Graphics.hpp>

#include "StateMachine/StateManager.hpp"

#include <memory>

int main( void ) {
    std::unique_ptr<sf::RenderWindow> win;
    win = std::make_unique<sf::RenderWindow>( sf::VideoMode( 720, 480), "Testing" );
    StateManager manager;

    sf::Clock clk;
    sf::Time dt = sf::Time::Zero;
    sf::Time accTime = sf::Time::Zero;

    while ( win->isOpen() ) {
        dt = clk.restart();

        sf::Event ev;
        while (win->pollEvent( ev ))
            if ( (ev.type = sf::Event::Closed) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                    win->close();

        manager.Update( dt );

        win->clear();

        manager.Render( *win );

        win->display();
    }
    return 0; 
}