#include <engine/MainMenu.hpp>

#include <cache/visuals/MenuUI.hpp>
#include <engine/input/Request.hpp>

#include <cache/SoundCache.hpp>

#include <iostream>

MainMenu::MainMenu() : State() {}

void MainMenu::Load() {
    this->accTime = sf::Time::Zero;
    std::cout << "[MainMenu] Loading..\n";

    this->music = std::make_unique<sf::Music>();
    if (!(this->music->openFromFile( "assets/musics/Yoshis_Story-Games_of_Happiness.ogg" )))
        throw std::runtime_error("Failure");
        
    this->music->setLooping( true );

    this->setButtonsCount( 3 );

    this->setRequest({
        { sf::Keyboard::Key::P, Action::raisePlay },
        { sf::Keyboard::Key::S, Action::raiseSett },
        { sf::Keyboard::Key::Q, Action::raiseQuit }
    });
    this->setRequest({
        { sf::Mouse::Button::Left, Action::raisePlay, MenuUI::getInst().btnBound( 0 ) },
        { sf::Mouse::Button::Right, Action::raiseSett, MenuUI::getInst().btnBound( 1 ) },
        { sf::Mouse::Button::Right, Action::raiseQuit, MenuUI::getInst().btnBound( 2 ) }
    });

    std::cout << "[MainMenu] Loaded!\n";
}

void MainMenu::Update( sf::Time& dt ) {
    if (this->music->getStatus() != sf::Music::Status::Playing)
        this->music->play();

    this->accTime+=dt;
    if (accTime.asSeconds() >= 2.0f) {
        std::cout << "MainMenu: 2s passed by..\n";
        accTime = sf::Time::Zero;
    }
}

void MainMenu::Render( sf::RenderWindow& win ) const {
    win.setTitle("Main Menu");

    win.draw( MenuUI::getInst().get("bg") );
    for (int i = 0; i < this->getButtonsCount(); i++)
        win.draw( MenuUI::getInst().get("btn", i) );
}


State::Type MainMenu::getType() const { return State::Type::MainMenu; }

void MainMenu::exit() {
    this->music.reset();
}

void MainMenu::pause() {
    if ( this->music->getStatus() != sf::Music::Status::Stopped )
        this->music->stop();
}