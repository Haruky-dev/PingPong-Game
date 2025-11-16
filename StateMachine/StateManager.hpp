#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <functional>
#include <vector>

#include "StateType.hpp"

class State;


class StateManager {
    private:
        // std::vector<std::unique_ptr<State>> _stateStack;
        // A storing unit that holds factory functions of states
        std::unordered_map<
            StateType, std::function<std::unique_ptr<State>()>
            > _stateRegister;

        std::vector<std::unique_ptr<State>> _stateStack;

        sf::Time accTime;

        bool changeFlag;
        
    public:
        StateManager();
        ~StateManager();
        void pushState( StateType stateType );
        void changeState( StateType stateType, bool duplicate=false );
        void popState();

        void Update( sf::Time& dt );
        void Render( sf::RenderWindow& win ) const;
};