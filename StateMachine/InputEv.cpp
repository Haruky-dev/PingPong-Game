#include "InputEv.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Mouse.hpp>

InputEv& InputEv::getInst() {
    static InputEv inst = InputEv();
    return inst;
}

bool InputEv::buttonClick( const sf::IntRect& buttonBound, sf::RenderWindow& win ) const {
    const sf::Vector2<int> msPos = sf::Mouse::getPosition( win );    

    return ( (buttonBound.contains( msPos )) &&
            ( sf::Mouse::isButtonPressed( sf::Mouse::Left )));
}