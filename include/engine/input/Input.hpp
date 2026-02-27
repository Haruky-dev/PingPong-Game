// A box containing different aspects of user input each frame.
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>


struct Input {
    struct msProp {
        sf::Vector2i pos;
        sf::Mouse::Button btn;
        bool clicked = false;

        msProp( const sf::Vector2i& vect ={0, 0}, sf::Mouse::Button btn=sf::Mouse::Button::Extra1, bool click=false )
        : btn(btn), clicked(click) {
            this->pos.x = vect.x;
            this->pos.y = vect.y;
        }
    };
    struct kbProp {
        sf::Keyboard::Key key = sf::Keyboard::Key::Unknown;
        bool clicked = false;

        kbProp( sf::Keyboard::Key key = sf::Keyboard::Key::Unknown, bool click = false )
            : key(key), clicked(click) {}
    };

    msProp mouse;
    kbProp keyb;
};