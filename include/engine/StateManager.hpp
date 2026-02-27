#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>
#include <memory>
#include <vector>

#include <engine/State.hpp>

enum class Action;


class StateManager {
    private:
        // A storing unit that holds factory functions of states
        std::unordered_map<
            State::Type, std::function<std::unique_ptr<State>()>
            > _stateRegister;

        std::vector<std::unique_ptr<State>> _stateStack;

    private:
        void pushState( State::Type T, bool freezeLast=false, bool overlapLast=false );
        void updateStates( sf::Time& dt );
        void controlOut( const Action out );
        void renderStates( sf::RenderWindow& win  ) const;


    public:
        StateManager();
        ~StateManager();

    public:
        void Update( sf::Time& dt, sf::RenderWindow& win );
        void Render( sf::RenderWindow& win ) const;
};