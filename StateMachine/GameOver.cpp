#include "GameOver.hpp"

#include "../Utils.hpp"

#include <print>


GameOver::GameOver() : State() {}

void GameOver::Load() {
    this->accTime = sf::Time::Zero;

    this->bg.setRadius( 100.f );
    this->bg.setFillColor( sf::Color::White );
    this->bg.setOutlineColor( sf::Color::Black );
    this->bg.setOutlineThickness( 10.f );
    this->bg.setOrigin( this->bg.getRadius(), this->bg.getRadius() );
    this->bg.setPosition( Utils::WIDTH/2.f, Utils::HEIGHT/2.f );

    std::println("[GameOver] Loaded!");
}

void GameOver::Update( sf::Time& dt ) {
    accTime+=dt;

    if (accTime.asSeconds() >= 2.f) {
        std::println("[GameOver] 2s Passed by");

        accTime = sf::Time::Zero;
    }
}

void GameOver::Render( sf::RenderWindow& win ) const {
    win.setTitle("Game Over!");
    win.draw( bg );
}

StateType GameOver::getType() const { return StateType::GameOver; }