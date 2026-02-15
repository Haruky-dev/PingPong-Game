#pragma once

#include <SFML/Graphics.hpp>

#include <engine/State.hpp>


class Pause : public State {
    private:
        sf::RectangleShape bg;
        sf::Time accTime;

    public:
        Pause();
        
        void Load() override;
        void Update( sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;

        State::Type getType() const override;

        ~Pause() = default;
};