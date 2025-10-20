#include "Player.hpp"
#include "Utils.hpp"

#include <iostream>

int Player::playersCount = 0;

Player::Player(const sf::Color &mainColor, const sf::Color &secColor)
    : width(8), height(50), speed(450.f)
{
    playersCount++;

    // check #Players. Assign IDs
    if ( playersCount > 2 )
        throw std::runtime_error("Cannot Created A Third Player!");

    if ( playersCount == 1 ) {
        this->id = 1;
    } else {
        this->id = 2;
    }

    bar.setSize( sf::Vector2f( width, height ));
    bar.setOrigin( width/2.f, height/2.f );
    bar.setFillColor( mainColor );
    bar.setOutlineThickness( 2.f );
    bar.setOutlineColor( secColor );

    if ( this->id == 1 )
        bar.setPosition( Utils::WIDTH - 20.f, Utils::HEIGHT/2.f );
    else
        bar.setPosition( 20.f, Utils::HEIGHT/2.f );
}

void Player::UpdateState( sf::Time& dt) {
    double Y_pos = bar.getPosition().y;

    // Arrows
    if (this->id == 1) {
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) {
            if ( Y_pos - height/2.f > 0)
                bar.move( 0, - speed * dt.asSeconds() );
        } if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ) {
            if (Y_pos + height/2.f < Utils::HEIGHT)
                bar.move( 0, speed * dt.asSeconds() );
        }
        
    // WASD
    } else {
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) ) {
            if ( Y_pos - height/2.f > 0)
                bar.move( 0, - speed * dt.asSeconds() );
        } if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) ) {
            if (Y_pos + height/2.f < Utils::HEIGHT)
                bar.move( 0, speed * dt.asSeconds() );
        }
    }
}


void Player::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    target.draw( bar, states );
}

sf::FloatRect Player::getBounds() const {
    return this->bar.getGlobalBounds();
}