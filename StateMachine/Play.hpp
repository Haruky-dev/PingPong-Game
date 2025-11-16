#pragma once

#include "State.hpp"
#include "StateType.hpp"

class Play : public State {
    private:
        // prv members

    public:
        Play();
        void Load() override;
        void Update( sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) const override;
  
        StateType getType() const override;
};