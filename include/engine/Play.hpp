#pragma once

#include <SFML/Audio/Music.hpp>

#include <memory>
#include <utility>

#include <engine/State.hpp>
#include <engine/StateType.hpp>

#include <entities/Player.hpp>
#include <entities/Ball.hpp>
#include <entities/Utils.hpp>


class Play : public State {
    private:
        std::unique_ptr<Player> P1;
        std::unique_ptr<Player> P2;
        std::unique_ptr<Ball> ball;
        std::unique_ptr<Utils::FrameRate> F;

        // std::optional<sf::Music> music;

    public:
        Play();
        ~Play();
        void Load() override;
        void Update( sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;
  
        StateType getType() const override;
};