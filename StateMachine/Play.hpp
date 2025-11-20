#pragma once

#include <memory>

#include "State.hpp"
#include "StateType.hpp"
#include "../Player.hpp"
#include "../Ball.hpp"


class Play : public State {
    private:
        std::unique_ptr<Player> P1;
        std::unique_ptr<Player> P2;
        std::unique_ptr<Ball> ball;

    public:
        Play();
        ~Play();
        void Load() override;
        void Update( sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;
  
        StateType getType() const override;
};