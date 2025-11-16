#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>

class State;

class StateManager {
    private:
        std::stack<std::unique_ptr<State>> _stateStack;
        std::unique_ptr<State> currState;
        sf::Time accTime;
        bool changedState = false;

    public:
        StateManager();
        ~StateManager();
        void pushState( std::unique_ptr<State> state );
        void popState();
        void changeState();

        void Update( sf::Time& dt );
        void Render( sf::RenderWindow& win ) const;
};