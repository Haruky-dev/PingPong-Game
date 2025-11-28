#include <SFML/Graphics.hpp>

#include "StateMachine/StateManager.hpp"
#include "Utils.hpp"

#include <memory>

int main( void ) {

    std::unique_ptr<sf::RenderWindow> win;
    win = std::make_unique<sf::RenderWindow>(
        sf::VideoMode( 720, 480),
        "Testing",
        sf::Style::Default & ~sf::Style::Resize
    );

    // init win.position to center
    sf::VideoMode deskTop = sf::VideoMode::getDesktopMode();
    win->setPosition( sf::Vector2i(
        (deskTop.width - Utils::WIDTH)   /2,
        (deskTop.height - Utils::HEIGHT) /2
    ) );

    StateManager manager;

    sf::Clock clk;
    sf::Time dt = sf::Time::Zero;

    while ( win->isOpen() ) {
        dt = clk.restart();

        sf::Event ev;
        while (win->pollEvent( ev ))
            if ( (ev.type == sf::Event::Closed) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                    // manager.Close() // Quit State
                    win->close();

        manager.Update( dt, *win );

        win->clear();

        manager.Render( *win );

        win->display();
    }
    return 0; 
}