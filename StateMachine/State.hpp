/* Base class that define 'shape' of all derived states */
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "StateType.hpp"

class StateManager;


class State {
    protected:
        bool loadFlag;

        explicit State() : loadFlag(false){}

    public:
        virtual void Load() = 0;
        virtual void Update( sf::Time& dt ) = 0;
        virtual void Render( sf::RenderWindow& win ) const = 0; 

        virtual StateType getType() const = 0;

        void setLoaded( bool flag ) { loadFlag = flag; }
        bool isLoaded() const { return loadFlag; }

        virtual ~State() = default;
};