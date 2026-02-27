#pragma once

#include <SFML/Graphics.hpp>

#include <engine/State.hpp>
#include <engine/features/Animated.hpp>


class Setting : public State, public Animated {
    private:
        sf::Sprite bg;
        sf::Sprite shad;
        sf::Color shadClr;
        float initPos;

        float t, elapsed;
        const float duration; // sec
        int direc;

    public:
        Setting();
        void Load() override;
        void Update( sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;

        void requestExit() override;
        bool animated() const override;
        bool exitDone() const override;
        
        State::Type getType() const override;

        ~Setting() = default;
};