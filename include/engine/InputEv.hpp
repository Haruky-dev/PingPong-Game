#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class InputEv {
    private:
        InputEv() = default;
        InputEv( const InputEv& other ) = delete;
        InputEv& operator=( const InputEv& other ) = delete;

    public:
        // Singleton Accessor
        static InputEv& getInst();

        bool buttonClick( const sf::IntRect& buttonBound, sf::RenderWindow& win ) const;
};