#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>

#include <utility>

#include <engine/State.hpp>
#include <engine/StateType.hpp>


class MainMenu : public State {
    private:
        sf::Time accTime;
        std::optional<sf::Music> music;

    public:
        MainMenu();
        void Load() override;
        void Update( sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;

        StateType getType() const override;

        ~MainMenu() = default;
};