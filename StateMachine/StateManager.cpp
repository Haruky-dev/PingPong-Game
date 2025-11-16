#include "StateManager.hpp"

#include "State.hpp"

#include "MainMenu.hpp"
#include "Pause.hpp"
// #include "Setting.hpp"
// #include "Play.hpp"
// #include "GameOver.hpp"

#include <print>

// StateManager::_stateStack
    // = std::make_unique<std::stack< std::unique_ptr< State > >();
// std::stack<std::unique_ptr<State>> StateManager::_stateStack;

StateManager::StateManager() : _stateStack(), accTime(sf::Time::Zero),
        changeFlag(false)
{
    // register all states
    _stateRegister[StateType::MainMenu] = []() { return std::make_unique<MainMenu>(); };
    // _stateRegister[StateType::Setting] = []() { return std::make_unique<Setting>(); };
    _stateRegister[StateType::Pause]    = []() { return std::make_unique<Pause>(); };
    // _stateRegister[StateType::Play]     = []() { return std::make_unique<Play>(); };
    // _stateRegister[StateType::GameOver] = []() { return std::make_unique<GameOver>(); };

    _stateStack.push_back( _stateRegister[StateType::MainMenu]() );
    _stateStack.back()->Load();
    // _stateStack.top()->setLoaded(true);
}

StateManager::~StateManager() = default;

// managaer.pushState(std::make_unique<state>)
void StateManager::pushState( StateType stateType ) {
    this->_stateStack.push_back( _stateRegister[stateType]() );

    // make a function to load/uload top state on stack
        // 'back' is the last added state (== stack::top())
    if ( !_stateStack.back()->isLoaded() ) {
        std::println("\nWARN: Pushed an Unloaded State!!\n");

        _stateStack.back()->Load();
        _stateStack.back()->setLoaded(true);
    }
}

void StateManager::popState() {
    this->_stateStack.pop_back();
}

void StateManager::changeState( StateType stateType, bool duplicate ) {
    /*
        if 'duplicate': create new state
        else: (in stake)? bring to top : create new state
            // bring to top:
                - hold it temporarly // ensure not creating a new one
                - clean it's leftover (std::move leaves a nullptr)
                - push the hold
    */

    if (!duplicate) {
        for (int i = 0; i<_stateStack.size(); ++i)
            if (_stateStack[i]->getType() == stateType) {
                auto tempHold = std::move( _stateStack[i] ); // hold
                _stateStack.erase( _stateStack.begin() + i ); // clean
                _stateStack.push_back( std::move(tempHold) ); // push
                return;
            }
    }

    // duplicate || not found
    _stateStack.push_back( _stateRegister[stateType]() );    
    _stateStack.back()->Load();
}

void StateManager::Update( sf::Time& dt ) {
    // this->_stateStack.top()->Update( dt );
    accTime+=dt;

    if (!changeFlag && accTime.asSeconds() >= 3.0f) {
        changeFlag = true;
        accTime = sf::Time::Zero;

        // this->pushState( StateType::MainMenu );
        this->changeState( StateType::Pause );

        std::println(" Current/Top State: [Pause] ");
    }
    else if (changeFlag && accTime.asSeconds() >= 2.0f) {
        changeFlag = false;
        accTime = sf::Time::Zero;

        // this->pushState( StateType::Pause );
        this->changeState( StateType::MainMenu );

        std::println( " Current/Top State: [MainMenu] ");
    }
}

void StateManager::Render( sf::RenderWindow& win ) const {
    if ( !(this->_stateStack.empty()) )
        this->_stateStack.back()->Render( win );
}