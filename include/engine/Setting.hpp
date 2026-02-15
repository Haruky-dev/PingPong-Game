#pragma once

#include <SFML/Graphics.hpp>

#include <engine/State.hpp>


class Setting : public State {
    private:
        sf::Sprite bg;
        sf::Sprite shad;
        sf::Color shadClr;
        float initPos;

        float t, elapsed;
        const float duration; // sec

    public:
        Setting();
        void Load() override;
        void Update( sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;

        State::Type getType() const override;

        ~Setting() = default;
};