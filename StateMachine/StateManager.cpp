#include "StateManager.hpp"

#include "State.hpp"
#include "MainMenu.hpp"
#include "Pause.hpp"
// #include "Setting.hpp"
#include "Play.hpp"
#include "GameOver.hpp"

#include "../Utils.hpp"

#include <print>


// -- CONSTRUCTOR/DEST SECTION
StateManager::StateManager() : _stateStack() {
    // register all states
    _stateRegister[StateType::MainMenu] = []() { return std::make_unique<MainMenu>(); };
    // _stateRegister[StateType::Setting] = []() { return std::make_unique<Setting>(); };
    _stateRegister[StateType::Pause]    = []() { return std::make_unique<Pause>(); };
    _stateRegister[StateType::Play]     = []() { return std::make_unique<Play>(); };
    _stateRegister[StateType::GameOver] = []() { return std::make_unique<GameOver>(); };
    // Future state to add: Info
    // _stateRegister[StateType::Info] = []() { return std::make_unique<Info>(); };

    _stateStack.push_back( _stateRegister[StateType::MainMenu]() );
    _stateStack.back()->Load();
    // _stateStack.top()->setLoaded(true);
}

StateManager::~StateManager() = default;


// -- PUBLIC FUNCs SECTION
void StateManager::Update( sf::Time& dt ) {
    if ( !(this->_stateStack.empty()) )
        this->updateStates( dt );

    switch (this->_stateStack.back()->getType()) {
        case StateType::MainMenu:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                this->pushState( StateType::Play );
            break;

        case StateType::Play:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                this->pushState( StateType::Pause );

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                this->pushState( StateType::MainMenu);

            // Utils::MAX_SCORE;
            else if (Utils::P1_SCORE >= 5 || Utils::P2_SCORE >= 5)
                this->pushState( StateType::GameOver );                
            break;
            
        case StateType::Pause:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                this->popState( StateType::Pause );
            break;

        case StateType::GameOver:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                this->popState( StateType::GameOver );
                this->pushState( StateType::Play );
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
                this->popState( StateType::GameOver );
                this->pushState( StateType::MainMenu );
            }
            break;
    }
}

void StateManager::Render( sf::RenderWindow& win ) const {
    if ( !(this->_stateStack.empty()) )
        this->renderStates( win );
}


// -- PRIVATE Func Section
void StateManager::pushState( StateType stateType ) {
    if (this->_stateStack.back()->getType() == stateType)
       // throw std::runtime_error(" WARN: Replicated State Pushed! ");
        return;

    bool overlap = false;
    /*
        bool: overlape
            mark a state with overlap flag
        if (state->isOverlapping)
            update prev state on stack if exist
            // recursively do
    */
    switch (stateType) {
        case StateType::MainMenu:
            // Reset stack
            this->_stateStack.clear();

            break;

        case StateType::Pause:
            this->_stateStack.back()->setFreeze( true );
            overlap = true;
            break;

        case StateType::GameOver:
            this->_stateStack.back()->setFreeze( true );
            overlap = true;
    }

    this->_stateStack.push_back( _stateRegister[stateType]() );
    this->_stateStack.back()->setOverlap( overlap );
    // make a function to load/uload top state on stack
        // 'back' is the last added state (== stack::top())
    if ( !_stateStack.back()->isLoaded() ) {
        std::println("\nWARN: Pushed an Unloaded State!!\n");

        _stateStack.back()->Load();
        _stateStack.back()->setLoaded(true);
    }
}

void StateManager::toggleState( StateType stateType, bool toggle ) {
    // if state exists in stack:
        // - if toggle: state->Load()
        // if !toggle: state->Unload() // or Freeze not sure yet
    // else:
        // create new one:
            // if toggle: state->Load()
            // else: state->UnLoad() / Freeze

    std::vector<std::unique_ptr<State>>::iterator state;

    state = std::find_if(_stateStack.begin(), _stateStack.end(),
                [stateType](const auto& st) {
                    return st->getType() == stateType;
                });
        // find_if return an iterator pointing to the object if finds
        // and that obj is a 'std::unique_ptr<State>'
        // so I have to use as such: '((*(*state))).member' or '(*state)->member'

    if (state == _stateStack.end())
        std::println("State NOT Found");
    else
        std::println("State Found");
}

void StateManager::popState( StateType stateType ) {
    // this->_stateStack.pop_back();
    switch (stateType) {
        case StateType::Pause:
            // safe check
            if (this->_stateStack.size() > 1)
                // 'unPause' last state
                this->_stateStack[ this->_stateStack.size() - 2 ]->setFreeze( false );
            break;
        
        case StateType::GameOver:
            if (this->_stateStack.size() > 2)
                this->_stateStack[ this->_stateStack.size() - 2]->setFreeze(false);

            Utils::P1_SCORE = 0;
            Utils::P2_SCORE = 0;
    }

    this->_stateStack.pop_back();
}

void StateManager::updateStates( sf::Time& dt ) const {
    // update all states in _stateStack every frame

    if (this->_stateStack.empty())
        return;

    int I = static_cast<int>(this->_stateStack.size()) - 1;
    for ( ; I >= 0; I-- ) {
        if ( !this->_stateStack[ I ]->isFrozen() )
            this->_stateStack[ I ]->Update( dt );

        if ( !this->_stateStack[ I ]->isOverlapping() )
            break;
    }
}

void StateManager::renderStates( sf::RenderWindow& win ) const {
    // render all states in _stateStack starting from the first
        // non-overlapping one. Preserve visibility order
    if ( this->_stateStack.empty() )
        return;

    // last element index
    int currIndex = static_cast<int>(this->_stateStack.size()) - 1;

    // find index of last state that isn't overlaping
        // (A main state, that takes up the whole window)
    while ( (currIndex > 0) && _stateStack[currIndex]->isOverlapping() ) {
        currIndex--;
    }

    for (int i = currIndex; i < _stateStack.size(); i++)
        _stateStack[i]->Render( win );
}