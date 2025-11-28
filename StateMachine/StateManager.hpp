#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <functional>
#include <vector>

#include "StateType.hpp"

class State;


class StateManager {
    public:
        StateManager();
        ~StateManager();

    public:
        void Update( sf::Time& dt, sf::RenderWindow& win );
        void Render( sf::RenderWindow& win ) const;

    private:
        // A storing unit that holds factory functions of states
        std::unordered_map<
            StateType, std::function<std::unique_ptr<State>()>
            > _stateRegister;

        std::vector<std::unique_ptr<State>> _stateStack;

    private:
        void pushState( StateType stateType );
        void toggleState( StateType stateType, bool toggle );
        void popState( StateType stateType);
        void updateStates( sf::Time& dt ) const;
        void renderStates( sf::RenderWindow& win  ) const;
};