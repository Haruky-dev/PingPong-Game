#include <Play.hpp>

Play::Play() : State() {}

void Play::Load() {
    // loading
}

void Play::Update( sf::Time& dt ) {}

void Play::Render( sf::RenderWindow& win ) const {}

StateType Play::getType() const { return StateType::Play; }