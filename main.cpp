#include <SFML/Graphics.hpp>

#include "StateMachine/StateManager.hpp"
#include "Utils.hpp"
#include "Json.hpp"

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

    bool focused = true;

    while ( win->isOpen() ) {
        dt = clk.restart();

        sf::Event ev;
        while (win->pollEvent( ev )) {
            if ( ev.type == sf::Event::GainedFocus ) {
                focused = true;
            } else if ( ev.type == sf::Event::LostFocus ) {
                    focused = false;
            }

            if (focused) {
                if ( (ev.type == sf::Event::Closed) ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                        win->close(); // manager.Close( *win ) // Quit State

                // refrech conf.json for debug
                if ( (ev.type == sf::Event::KeyPressed) && (ev.key.code == sf::Keyboard::R) )
                    // Json::getInst().reLoad();
                    Json::reLoad();
            }
        }

        if (focused) manager.Update( dt, *win );

        win->clear();

        manager.Render( *win );

        win->display();
    }
    return 0; 
}