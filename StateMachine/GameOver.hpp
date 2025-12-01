#pragma once

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "StateType.hpp"

class GameOver : public State {
    private:
        sf::CircleShape bg;
        sf::Time accTime;

    public:
        GameOver();
        
        void Load() override;
        void Update( sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;

        StateType getType() const override;

        ~GameOver() = default;
};