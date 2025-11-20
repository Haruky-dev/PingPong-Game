/* Base class that define 'shape' of all derived states */
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "StateType.hpp"

class StateManager;


class State {
    protected:
        bool loadFlag;
        bool overlapFlag;
        bool freezeFlag;

        explicit State() : loadFlag(false), overlapFlag(false), freezeFlag(false) {}

    public:
        virtual void Load() = 0;
        virtual void Update( sf::Time& dt ) = 0;
        virtual void Render( sf::RenderWindow& win ) const = 0; 

        // getters
        virtual StateType getType() const = 0;

        // flags
        void setLoaded( bool flag ) { loadFlag = flag; }
        bool isLoaded() const { return loadFlag; }

        void setOverlap( bool flag ) { overlapFlag = flag; }
        bool isOverlapping() const { return overlapFlag; }

        void setFreeze( bool flag ) { freezeFlag = flag; }
        bool isFrozen() const { return freezeFlag; }

        virtual ~State() = default;
};