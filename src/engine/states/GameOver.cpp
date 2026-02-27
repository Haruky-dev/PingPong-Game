#include <engine/states/GameOver.hpp>

#include <tools/Tool.hpp>
#include <engine/State.hpp>

#include <iostream>


GameOver::GameOver() : State() {}

void GameOver::Load() {
    std::cout << "[GameOver] Loading..\n";

    this->accTime = sf::Time::Zero;

    this->bg.setRadius( 100.f );
    this->bg.setFillColor( sf::Color::White );
    this->bg.setOutlineColor( sf::Color::Black );
    this->bg.setOutlineThickness( 10.f );
    this->bg.setOrigin( {this->bg.getRadius(), this->bg.getRadius()} );
    this->bg.setPosition( Tool::W_CTR );

    std::cout << "[GameOver] Loaded!\n";

    this->setRequest({
        { sf::Keyboard::Key::Enter, Action::dropOverlap },
        { sf::Keyboard::Key::Escape, Action::raiseMain }
    });
}

void GameOver::Update( sf::Time& dt ) {
    accTime+=dt;

    if (accTime.asSeconds() >= 2.f) {
        std::cout << "[GameOver]\n";

        accTime = sf::Time::Zero;
    }
}

void GameOver::Render( sf::RenderWindow& win ) const {
    win.setTitle("Game Over!");
    win.draw( bg );
}

State::Type GameOver::getType() const { return State::Type::GameOver; }
