#pragma once

#include "State.hpp"

class Play : public State {
    private:
        // prv members

    public:
        void Load() override;
        void Update( sf::Time& dt ) override;
        void Render( sf::RenderWindow& win ) override;
        
        void setLoad( bool flag ) override;
        bool isLoaded() const override;
};