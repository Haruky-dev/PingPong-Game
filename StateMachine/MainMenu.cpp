#include "MainMenu.hpp"

#include <print>

MainMenu::MainMenu() : State() {}

void MainMenu::Load() {
    this->accTime = sf::Time::Zero;
    std::println("[MainMenu] Loading..");
    bg.setSize( sf::Vector2f( 720.f, 480.f ));
    bg.setFillColor( sf::Color::Blue );
    std::println("[MainMenu] Loaded!");
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
}


StateType MainMenu::getType() const { return StateType::MainMenu; }