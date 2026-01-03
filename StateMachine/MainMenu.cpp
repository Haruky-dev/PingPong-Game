#include "MainMenu.hpp"

#include "InputEv.hpp"
#include "../Assets.hpp"
#include "../SoundAssets.hpp"

#include <print>

MainMenu::MainMenu() : State() {}

void MainMenu::Load() {
    this->accTime = sf::Time::Zero;
    std::println("[MainMenu] Loading..");
    // bg.setSize( sf::Vector2f( 720.f, 480.f ));
    // bg.setFillColor( sf::Color::Blue );
    this->bg = Assets::getInst().getMainBg();

    this->setButtonsCount( 3 );

    std::println("[MainMenu] Loaded!");

    // r = (rand() % (end - start + 1)) + start
}

void MainMenu::Update( sf::Time& dt ) {
    this->accTime+=dt;
    if (accTime.asSeconds() >= 2.0f) {
        std::println("MainMenu: 2s passed by..");
        accTime = sf::Time::Zero;
    }
}

void MainMenu::Render( sf::RenderWindow& win ) const {
    win.setTitle("Main Menu");
    win.draw( bg );
    win.draw( Assets::getInst().getMMBtn(0, false));
    win.draw( Assets::getInst().getMMBtn(1, false));
    win.draw( Assets::getInst().getMMBtn(2, false));
}


StateType MainMenu::getType() const { return StateType::MainMenu; }