#pragma once

#include <SFML/Graphics.hpp>

#include "State.hpp"

class MainMenu : public State {
    private:
        sf::RectangleShape bg;
        sf::Time accTime;

    public:
        MainMenu();
        void Load() override;
        void Update( sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;

        ~MainMenu() = default;
};