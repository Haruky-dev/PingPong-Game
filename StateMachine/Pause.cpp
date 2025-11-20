#include "Pause.hpp"

#include "../Utils.hpp"

#include <print>

Pause::Pause() : State() {}

void Pause::Load() {
    this->accTime = sf::Time::Zero;
    std::println("[Pause] Loading..");
    bg.setSize( sf::Vector2f( 300.f, 300.f ));
    bg.setOrigin( bg.getSize().x/2.0f, bg.getSize().y/2.0f );
    bg.setPosition( Utils::WIDTH/2.0f, Utils::HEIGHT/2.0f );
    bg.setFillColor( sf::Color::Yellow );
}

void Pause::Update( sf::Time& dt ) {
    accTime+=dt;
    if (accTime.asSeconds() > 2.0f) {
        std::println("Game Paused: 2s Passed by..");
        accTime = sf::Time::Zero;
    }
}

void Pause::Render( sf::RenderWindow& win ) const {
    win.setTitle("Game Paused!");
    win.draw( bg );
}

StateType Pause::getType() const { return StateType::Pause; }