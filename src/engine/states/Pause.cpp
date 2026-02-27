#include <engine/states/Pause.hpp>

#include <tools/Tool.hpp>
#include <engine/input/Action.hpp>

#include <iostream>

Pause::Pause() : State() {}

void Pause::Load() {
    std::cout << "[Pause] Loading..\n";
    
    this->accTime = sf::Time::Zero;
    
    bg.setSize( sf::Vector2f( 300.f, 300.f ));
    bg.setOrigin( bg.getSize() / 2.f );
    bg.setPosition( Tool::W_CTR );
    bg.setFillColor( sf::Color::Yellow );

    this->setRequest({
        { sf::Keyboard::Key::Enter, Action::dropOverlap },
        { sf::Keyboard::Key::Escape, Action::raiseMain }
    });
    
    std::cout << "[Pause] Loaded!\n";
}

void Pause::Update( sf::Time& dt ) {
    accTime+=dt;
    if (accTime.asSeconds() > 2.0f) {
        std::cout << "[Pause]\n";
        accTime = sf::Time::Zero;
    }
}

void Pause::Render( sf::RenderWindow& win ) const {
    win.setTitle("Game Paused!");
    win.draw( bg );
}

State::Type Pause::getType() const { return State::Type::Pause; }