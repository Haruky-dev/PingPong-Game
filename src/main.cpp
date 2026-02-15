#include <SFML/Graphics.hpp>

#include <engine/StateManager.hpp>
#include <tools/Tool.hpp>
#include <tools/Json.hpp>

#include <memory>

#include <iostream>

int main( void ) {

    std::unique_ptr<sf::RenderWindow> win;
    win = std::make_unique<sf::RenderWindow>(
        sf::VideoMode( {720, 480} ),
        "Testing",
        sf::Style::Default & ~sf::Style::Resize
    );

    // center win
    win->setPosition(
        ( sf::Vector2i(sf::VideoMode::getDesktopMode().size) -
          sf::Vector2i({Tool::WIDTH, Tool::HEIGHT}) )
        / 2);
    
    StateManager manager{};

    sf::Clock clk;
    sf::Time dt = sf::Time::Zero;

    bool focused = true;

    while ( win->isOpen() ) {
        dt = clk.restart();

        while ( const std::optional<sf::Event> ev = win->pollEvent() ) {
            if ( ev->is<sf::Event::FocusGained>() )
                focused = true;
            else if ( ev->is<sf::Event::FocusLost>() )
                focused = false;

            if (focused) {
                if ( ev->is<sf::Event::Closed>() )
                    win->close();
                else if ( ev->is<sf::Event::KeyPressed>() ) {
                    if ( ev->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Q ) 
                        win->close();

                // refrech conf.json for debug
                    else if ( ev->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::R )
                        Json::reLoad();
                }
            }
        }

        if (focused) manager.Update( dt, *win );

        win->clear();

        manager.Render( *win );

        win->display();
    }
    return 0; 
}