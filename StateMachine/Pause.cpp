#include "Pause.hpp"

#include <print>

Pause::Pause() : State() {}

void Pause::Load() {
    this->accTime = sf::Time::Zero;
    std::println("Pretend like I am loading..");
    bg.setSize( sf::Vector2f( 100.f, 100.f ));
    bg.setPosition( 100.f, 100.f );
    bg.setFillColor( sf::Color::Yellow );
}

void Pause::Update( sf::Time& dt ) {
    accTime+=dt;
    if (accTime.asSeconds() > 1.0f) {
        std::println("Game Paused: 1s Passed by..");
    }
}

void Pause::Render( sf::RenderWindow& win ) const {
    win.setTitle("Game Paused!");
    win.draw( bg );
}