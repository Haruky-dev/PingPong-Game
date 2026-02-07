#include <engine/Pause.hpp>

#include <entities/Utils.hpp>

#include <iostream>

Pause::Pause() : State() {}

void Pause::Load() {
    this->accTime = sf::Time::Zero;
    std::cout << "[Pause] Loading..\n";
    bg.setSize( sf::Vector2f( 300.f, 300.f ));
    bg.setOrigin( bg.getSize() / 2.f );
    bg.setPosition( Utils::W_CTR );
    bg.setFillColor( sf::Color::Yellow );
}

void Pause::Update( sf::Time& dt ) {
    accTime+=dt;
    if (accTime.asSeconds() > 2.0f) {
        std::cout << "Game Paused: 2s Passed by..\n";
        accTime = sf::Time::Zero;
    }
}

void Pause::Render( sf::RenderWindow& win ) const {
    win.setTitle("Game Paused!");
    win.draw( bg );
}

StateType Pause::getType() const { return StateType::Pause; }