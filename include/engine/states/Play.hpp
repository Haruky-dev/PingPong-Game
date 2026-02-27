#pragma once

#include <SFML/Audio/Music.hpp>

#include <memory>

#include <engine/State.hpp>
#include <engine/input/Action.hpp>

#include <entities/Player.hpp>
#include <entities/Ball.hpp>
#include <tools/FrameRate.hpp>


class Play : public State {
    private:
        std::unique_ptr<Player> P1;
        std::unique_ptr<Player> P2;
        std::unique_ptr<Ball> ball;
        std::unique_ptr<FrameRate> F;

        std::unique_ptr<sf::Music> music;
        
        Action feature() const override;

    public:
        Play();
        ~Play();
        void Load() override;
        void Update( sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;

        void exit() override;
        void pause() override;
        // void contiue;
          
        State::Type getType() const override;
};