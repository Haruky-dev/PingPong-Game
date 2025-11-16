#include "StateManager.hpp"

#include "State.hpp"

#include "MainMenu.hpp"
#include "Pause.hpp"

#include <print>

// StateManager::_stateStack
    // = std::make_unique<std::stack< std::unique_ptr< State > >();
// std::stack<std::unique_ptr<State>> StateManager::_stateStack;

StateManager::StateManager() : _stateStack(), accTime(sf::Time::Zero),
    currState(nullptr), changedState(false)
{
    _stateStack.push( std::make_unique<MainMenu>() );
    // _stateStack.top()->setLoaded(true);
}

StateManager::~StateManager() = default;

// managaer.pushState(std::make_unique<state>)
// StateManager.cpp
void StateManager::pushState( std::unique_ptr<State> state ) {
    if (!state)
        throw std::runtime_error("Passing none valid State.");

    this->_stateStack.push( std::move( state ) );

    // make a function to load/uload top state on stack
    if ( !_stateStack.top()->isLoaded() ) {
        _stateStack.top()->Load();
        _stateStack.top()->setLoaded(true);
    }
}

void StateManager::popState() {
    this->_stateStack.pop();
}

void StateManager::changeState() {
    if ( !(this->_stateStack.empty()) )
        this->_stateStack.pop();
}

void StateManager::Update( sf::Time& dt ) {
    // this->_stateStack.top()->Upda   te( dt );

    accTime+=dt;

    if (!changedState && accTime.asSeconds() >= 3.0f) {
        changedState = true;
        accTime = sf::Time::Zero;

        this->pushState( std::make_unique<Pause>() );

        std::println(" Current/Top State: [Pause] ");
    }
    else if (changedState && accTime.asSeconds() >= 2.0f) {
        changedState = false;
        accTime = sf::Time::Zero;

        this->pushState( std::make_unique<MainMenu>() );

        std::println( " Current/Top State: [MainMenu] ");
    }
}

void StateManager::Render( sf::RenderWindow& win ) const {
    if ( !(this->_stateStack.empty()) )
        this->_stateStack.top()->Render( win );
}