#include "MainMenu.hpp"

#include <print>

MainMenu::MainMenu() : State() {}

void MainMenu::Load() {
    this->accTime = sf::Time::Zero;
    std::println("Pretend like I am loading..");
    bg.setSize( sf::Vector2f( 300.f, 300.f ));
    bg.setPosition( 200.f, 200.f );
    bg.setFillColor( sf::Color::Red );
}

void MainMenu::Update( sf::Time& dt ) {
    this->accTime+=dt;
    if (accTime.asSeconds() > 1.0f) {
        std::println("MainMenu: 1s passed by");
    }
}

void MainMenu::Render( sf::RenderWindow& win ) const {
    win.draw( bg );
}