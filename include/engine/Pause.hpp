#pragma once

#include <SFML/Graphics.hpp>

#include <engine/State.hpp>
#include <engine/StateType.hpp>


class Pause : public State {
    private:
        sf::RectangleShape bg;
        sf::Time accTime;

    public:
        Pause();
        
        void Load() override;
        void Update( sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;

        StateType getType() const override;

        ~Pause() = default;
};