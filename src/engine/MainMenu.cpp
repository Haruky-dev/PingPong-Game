#include <engine/MainMenu.hpp>

#include <engine/InputEv.hpp>

#include <cache/visuals/MenuUI.hpp>

#include <cache/SoundCache.hpp>

#include <iostream>

MainMenu::MainMenu() : State() {}

void MainMenu::Load() {
    this->accTime = sf::Time::Zero;
    std::cout << "[MainMenu] Loading..\n";

    this->music.emplace( "assets/musics/Yoshis_Story-Games_of_Happiness.ogg" );
    // this->music->openFromFile( "assets/musics/Yoshis_Story-Games_of_Happiness.ogg" );

    this->setButtonsCount( 3 );

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


StateType MainMenu::getType() const { return StateType::MainMenu; }