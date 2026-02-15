#include <engine/GameOver.hpp>

#include <entities/Utils.hpp>
#include <engine/State.hpp>

#include <iostream>


GameOver::GameOver() : State() {}

void GameOver::Load() {
    this->accTime = sf::Time::Zero;

    this->bg.setRadius( 100.f );
    this->bg.setFillColor( sf::Color::White );
    this->bg.setOutlineColor( sf::Color::Black );
    this->bg.setOutlineThickness( 10.f );
    this->bg.setOrigin( {this->bg.getRadius(), this->bg.getRadius()} );
    this->bg.setPosition( Utils::W_CTR );

    std::cout << "[GameOver] Loaded!\n";

    this->setRequest({
        { sf::Keyboard::Key::Enter, Action::dropGameOv },
        { sf::Keyboard::Key::Escape, Action::raiseMain }
    });
}

void GameOver::Update( sf::Time& dt ) {
    accTime+=dt;

    if (accTime.asSeconds() >= 2.f) {
        std::cout << "[GameOver] 2s Passed by\n";

        accTime = sf::Time::Zero;
    }
}

void GameOver::Render( sf::RenderWindow& win ) const {
    win.setTitle("Game Over!");
    win.draw( bg );
}

State::Type GameOver::getType() const { return State::Type::GameOver; }