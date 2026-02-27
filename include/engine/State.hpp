/* Base class that define shape of all derived states */
#pragma once

#include <SFML/Window/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <engine/input/InputManager.hpp>
#include <engine/input/Request.hpp>
#include <engine/input/Action.hpp>
#include <engine/input/Input.hpp>

#include <initializer_list>


class StateManager;


class State { 
    private:
        virtual Action feature() const {
            return Action::None;
        }
    
    public:
        enum class Type {
            Loading,
            MainMenu,
            Setting,
            Play,
            Pause,
            GameOver,
            Quit
        };

    protected:
        Request request;
        int buttonsCount;
        bool loadFlag;
        bool overlapFlag;
        bool freezeFlag;


        explicit State() : loadFlag(false), overlapFlag(false),
            freezeFlag(false), buttonsCount(0) {}

    public:
        virtual void   Load() = 0;
        virtual void   Update( sf::Time& dt ) = 0;
        virtual void   Render( sf::RenderWindow& win ) const = 0; 

        virtual Action Read( const Input& input ) {
            Action act = this->feature();
 
            if ( act == Action::None )
                act = InputManager::verifyInput( this->request, input );
            
            return act;
        }
        
        // getters
        virtual State::Type getType() const = 0;
        virtual bool animated() const { return false; }
        virtual bool exitDone() const { return true; }
        virtual int getButtonsCount() const { return this->buttonsCount; }

        // setters (other than flags setters)
        virtual void setButtonsCount( const int n ) { this->buttonsCount = n; }
        virtual void requestExit() {}

        virtual void setRequest( const std::initializer_list< Request::kbBinding >& that ) {
            for ( const Request::kbBinding& K : that )
                this->request.vitalKeys.push_back( K );
        }
        virtual void setRequest( const std::initializer_list< Request::msBinding >& that ) {
            for ( const Request::msBinding& B : that )
                this->request.vitalButtons.push_back( B );
        }

        virtual std::vector<sf::Keyboard::Key> getKeys() const {
            std::vector<sf::Keyboard::Key> keys;
            keys.reserve( this->request.vitalKeys.size() );

            for ( const Request::kbBinding& B : this->request.vitalKeys )
                keys.push_back( B.key );

            return keys;
        }

        virtual std::vector<sf::Mouse::Button> getButtons() const {
            std::vector<sf::Mouse::Button> buttons;
            buttons.reserve( this->request.vitalButtons.size() );

            for ( const Request::msBinding& B : this->request.vitalButtons )
                buttons.push_back( B.btn );

            return buttons;
        }


        // flags
        void setLoaded( bool flag ) { this->loadFlag = flag; }
        bool isLoaded() const { return this->loadFlag; }

        void setOverlap( bool flag ) { this->overlapFlag = flag; }
        bool isOverlapping() const { return this->overlapFlag; }

        void setFreeze( bool flag ) { this->freezeFlag = flag; }
        bool isFrozen() const { return this->freezeFlag; }

        // actions
        virtual void exit() {}
        virtual void pause() {}

        virtual ~State() = default;
};