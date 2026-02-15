#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>

#include <memory>

#include <engine/State.hpp>

class MainMenu : public State {
    private:
        sf::Time accTime;
        std::unique_ptr<sf::Music> music;

    public:
        MainMenu();
        void Load() override;
        void Update( sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;

        // Action msAction( const Input& in ) const override;
        State::Type getType() const override;


        void exit() override;
        void pause() override;

        ~MainMenu() = default;
};