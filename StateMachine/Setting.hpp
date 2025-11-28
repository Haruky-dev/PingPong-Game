#pragma once

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "StateType.hpp"


class Setting : public State {
    private:
        sf::Sprite bg;
        sf::Sprite shad;

    public:
        Setting();
        void Load() override;
        void Update( sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;

        StateType getType() const override;

        ~Setting() = default;
};