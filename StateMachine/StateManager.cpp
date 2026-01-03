#include "StateManager.hpp"

#include "State.hpp"
#include "InputEv.hpp"
#include "MainMenu.hpp"
#include "Pause.hpp"
#include "Setting.hpp"
#include "Play.hpp"
#include "GameOver.hpp"
#include "Loading.hpp"

#include "../Utils.hpp"
#include "../Assets.hpp"
#include "../SoundAssets.hpp"
#include "../Json.hpp"

#include <print>


// -- CONSTRUCTOR/DEST SECTION
StateManager::StateManager() : _stateStack() {
    // register all states
    _stateRegister[StateType::MainMenu] = []() { return std::make_unique<MainMenu>(); };
    _stateRegister[StateType::Setting]  = []() { return std::make_unique<Setting>(); };
    _stateRegister[StateType::Pause]    = []() { return std::make_unique<Pause>(); };
    _stateRegister[StateType::Play]     = []() { return std::make_unique<Play>(); };
    _stateRegister[StateType::GameOver] = []() { return std::make_unique<GameOver>(); };
    _stateRegister[StateType::Loading]  = []() { return std::make_unique<Loading>(); };
    // Future state to add: Info
    // _stateRegister[StateType::Info] = []() { return std::make_unique<Info>(); };

    // Assets::getInst().loadResources();
    // SoundAssets::getInst().Load();

    // _stateStack.push_back( _stateRegister[StateType::MainMenu]() );
    _stateStack.push_back( _stateRegister[StateType::Loading]() );

    _stateStack.back()->Load();
    
    currSound = &(SoundAssets::getInst().getMusic( 0 ));
}

StateManager::~StateManager() = default;


// -- PUBLIC FUNCs SECTION
void StateManager::Update( sf::Time& dt, sf::RenderWindow& win ) {
    if (currSound && (currSound->getStatus() != sf::Sound::Playing))
        currSound->play();

    if ( !(this->_stateStack.empty()) ) {
        this->updateStates( dt );
        
        for (int i = 0; i<this->_stateStack.back()->getButtonsCount(); i++) {
            if (InputEv::getInst().buttonClick(
                Assets::getInst().getButtonBound( i ), win ) ) {
                    // this->pushState( Assets::getButtonLabel( i ) );
                    switch (Assets::getInst().getButtonLabel( i )) {
                        case StateType::Play:
                            this->pushState( StateType::Play );
                            break;
                        case StateType::Setting:
                            this->pushState( StateType::Setting );
                            break;
                        case StateType::Quit:
                            std::println("[Quit] Clicked.");
                    }
            }
        }
    }

    switch (this->_stateStack.back()->getType()) {
        case StateType::Loading:
            if ( static_cast<Loading*>( this->_stateStack.back().get() )->loadDone )
                this->pushState( StateType::MainMenu );

        case StateType::MainMenu:
            
            break;

        case StateType::Play:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                this->pushState( StateType::Pause );

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                this->pushState( StateType::MainMenu);

            // Utils::MAX_SCORE;
            else if (Utils::P1_SCORE >= Json::getInt("setting.maxScore") ||
                Utils::P2_SCORE >= Json::getInt("setting.maxScore"))
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

        case StateType::Setting:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                this->popState( StateType::Setting );
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

            Utils::P1_SCORE = 0;
            Utils::P2_SCORE = 0;

            if (currSound) currSound->pause();
            currSound = &(SoundAssets::getInst().getMusic( 0 ));

            break;

        case StateType::Play:
            if (currSound) currSound->pause();
            currSound = &(SoundAssets::getInst().getMusic( 1 ));

            break;

        case StateType::Pause:
            this->_stateStack.back()->setFreeze( true );
            overlap = true;
            break;

        case StateType::Setting:
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
        _stateStack.back()->Load();
        _stateStack.back()->setLoaded(true);
    }
}

void StateManager::popState( StateType stateType ) {
    // Situational Modifictions
    switch (stateType) {
        case StateType::Pause:
            // safe check
            if (this->_stateStack.size() > 1)
                // 'unPause' last state
                this->_stateStack[ this->_stateStack.size() - 2 ]->setFreeze( false );
            break;

        case StateType::Setting:
            if (this->_stateStack.size() > 1)
                this->_stateStack[ this->_stateStack.size() - 2 ]->setFreeze( false );
        
        case StateType::GameOver:
            if (this->_stateStack.size() > 2)
                this->_stateStack[ this->_stateStack.size() - 2]->setFreeze(false);

            Utils::P1_SCORE = 0;
            Utils::P2_SCORE = 0;

    }

        // Taking for guarantted that " input.StateType == _stateStack.back().StateType "
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
        // AKA a main state, that takes up the whole window
    while ( (currIndex > 0) && _stateStack[currIndex]->isOverlapping() ) {
        currIndex--;
    }

    for (int i = currIndex; i < _stateStack.size(); i++)
        _stateStack[i]->Render( win );
}