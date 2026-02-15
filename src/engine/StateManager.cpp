#include <engine/StateManager.hpp>

#include <engine/input/Action.hpp>
#include <engine/input/InputEv.hpp>
#include <engine/MainMenu.hpp>
#include <engine/Pause.hpp>
#include <engine/Setting.hpp>
#include <engine/Play.hpp>
#include <engine/GameOver.hpp>
#include <engine/Loading.hpp>

#include <tools/Tool.hpp>
#include <cache/TextureCache.hpp>
#include <cache/SoundCache.hpp>
#include <tools/Json.hpp>

#include <cache/visuals/MenuUI.hpp>
#include <cache/visuals/SettingUI.hpp>
#include <cache/visuals/PlayUI.hpp>

#include <iostream>

// -- CONSTRUCTOR/DEST SECTION
StateManager::StateManager() : _stateStack() {
    // register all states
    _stateRegister[State::Type::MainMenu] = []() { return std::make_unique<MainMenu>(); };
    _stateRegister[State::Type::Setting]  = []() { return std::make_unique<Setting>(); };
    _stateRegister[State::Type::Pause]    = []() { return std::make_unique<Pause>(); };
    _stateRegister[State::Type::Play]     = []() { return std::make_unique<Play>(); };
    _stateRegister[State::Type::GameOver] = []() { return std::make_unique<GameOver>(); };
    _stateRegister[State::Type::Loading]  = []() { return std::make_unique<Loading>(); };
    // Future state to add: Info
    // _stateRegister[State::Type::Info] = []() { return std::make_unique<Info>(); };

    _stateStack.push_back( _stateRegister[State::Type::Loading]() );
    _stateStack.back()->Load();
}

StateManager::~StateManager() = default;


// -- PUBLIC FUNCs SECTION
void StateManager::Update( sf::Time& dt, sf::RenderWindow& win ) {
    if ( this->_stateStack.empty() )
        return;

    this->updateStates( dt );

    Input in;

    in.mouse = InputEv::MouseClick( this->_stateStack.back()->getButtons(), win );
    in.keyb  = InputEv::keybClick( this->_stateStack.back()->getKeys() );

    this->controlOut(
        this->_stateStack.back()->Read( in )
    );

    switch ( this->_stateStack.back()->getType() ) {
        case State::Type::Loading:
            if ( static_cast<Loading*>
                ( this->_stateStack.back().get() )->loadDone.load()
            )
                this->pushState( State::Type::MainMenu );
            break;

        case State::Type::Play:
            if (
                ( Tool::P1_SCORE >= Json::getInt("setting.maxScore") )
                || ( Tool::P2_SCORE >= Json::getInt("setting.maxScore") )
            )
                this->pushState( State::Type::GameOver, true, true );
    }
}

void StateManager::Render( sf::RenderWindow& win ) const {
    if ( !(this->_stateStack.empty()) )
        this->renderStates( win );
}


// -- PRIVATE Func Section
void StateManager::pushState( State::Type T, bool freezeLast, bool overlapLast ) {
    if (!(this->_stateStack.empty())
        && ( this->_stateStack.back()->getType() == T ))
        return;

    if (freezeLast)
        this->_stateStack.back()->setFreeze( freezeLast );

    this->_stateStack.push_back( this->_stateRegister[T]() );
    this->_stateStack.back()->setOverlap( overlapLast );

    if ( !_stateStack.back()->isLoaded() ) {
        _stateStack.back()->Load();
        _stateStack.back()->setLoaded(true);
    }
}

void StateManager::popState( State::Type T ) {
    // Situational Modifictions
    switch (T) {
        case State::Type::Pause:
            // safe check
            if (this->_stateStack.size() > 1)
                // 'unPause' last state
                this->_stateStack[ this->_stateStack.size() - 2 ]->setFreeze( false );
            break;

        case State::Type::Setting:
            if (this->_stateStack.size() > 1)
                this->_stateStack[ this->_stateStack.size() - 2 ]->setFreeze( false );
        
    }

        // Taking for guarantted that " input.State::Type == _stateStack.back().State::Type "
    this->_stateStack.pop_back();
}

void StateManager::controlOut( const Action out ) {
    if ( out == Action::None )
        return;


    switch ( out ) {
        case Action::raiseMain:
            Tool::P1_SCORE = Tool::P2_SCORE = 0;
            this->_stateStack.clear();

            this->pushState( State::Type::MainMenu );            
            break;

        case Action::raisePause:
            this->_stateStack.back()->pause();
            this->pushState( State::Type::Pause, true, true );
            break;

        case Action::raisePlay:
            this->_stateStack.back()->exit();
            this->pushState( State::Type::Play );
            break;

        case Action::raiseSett:
            // this->_stateStack.back()->pause();
            this->pushState( State::Type::Setting, true, true );
            break;

        case Action::raiseQuit:
            std::cout << "Wanna quit?\n";
            break;

        case Action::dropOverlap:
            assert(
                ( this->_stateStack.back()->isOverlapping() )
                && (this->_stateStack.size() > 1)
            );

            this->_stateStack.pop_back();
            this->_stateStack.back()->setFreeze( false );
            break;

        

        case Action::dropGameOv:
            assert( this->_stateStack.back()->getType()
                    == State::Type::GameOver );

            assert( this->_stateStack.size() > 1 );

            Tool::P1_SCORE = Tool::P2_SCORE = 0;

            this->_stateStack.at(
                    this->_stateStack.size() - 2 
                )->setFreeze( false );

            this->_stateStack.pop_back();

            this->pushState( State::Type::Play );
            break;
        
    }
}

void StateManager::updateStates( sf::Time& dt ) const {
    // update all (top + overlapping) states in _stateStack every frame

    int I = static_cast<int>(this->_stateStack.size()) - 1;

    for ( ; I >= 0; I-- ) {
        if ( !this->_stateStack[ I ]->isFrozen() )
            this->_stateStack[ I ]->Update( dt );

        if ( !this->_stateStack[ I ]->isOverlapping() )
            break;
    }
}

void StateManager::renderStates( sf::RenderWindow& win ) const {
    // render all (top + overlapping) states in _stateStack starting from the first

        // non-overlapping one. Preserve visibility order
    if ( this->_stateStack.empty() )
        return;

    int currIndex = static_cast<int>(this->_stateStack.size()) - 1;

    // find index of last state that isn't overlaping
        // AKA a main state, that takes up the whole window
    while ( (currIndex > 0) && _stateStack[currIndex]->isOverlapping() ) {
        currIndex--;
    }

    for (int i = currIndex; i < _stateStack.size(); i++)
        _stateStack[i]->Render( win );
}
