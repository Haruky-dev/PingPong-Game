#include "Player.hpp"

#include "Utils.hpp"
#include "Assets.hpp"

int Player::playersCount = 0;

Player::Player( const sf::Sprite& spr ) : speed(500.f), score(0) {

    this->bar = spr;
    auto tempS = spr.getTexture()->getSize();
    this->bar.setOrigin( tempS.x /2.0f, tempS.y /2.0f );

    playersCount++;

    // check #Players. Assign IDs
    if ( playersCount > 2 )
        throw std::runtime_error("Cannot Created A Third Player!");

    if ( playersCount == 1 ) {
        this->id = 1;
    } else {
        this->id = 2;
        this->bar.setRotation( 180.0f );
    }

    if ( this->id == 1 )
        bar.setPosition( Utils::WIDTH - 20.f, Utils::HEIGHT/2.f );
    else
        bar.setPosition( 20.f, Utils::HEIGHT/2.f );

    // scoreTxt.loadFromFile( Assets::SCORE[ this->score ] );
}

void Player::UpdateState( sf::Time& dt) {
    double Y_pos = bar.getPosition().y;

    // Arrows
    if (this->id == 1) {
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) {
            if ( Y_pos - getBounds().height/2.f > 14.0f)
                bar.move( 0, - speed * dt.asSeconds() );
        } if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ) {
            if (Y_pos + getBounds().height/2.f < Utils::HEIGHT - 14.0f)
                bar.move( 0, speed * dt.asSeconds() );
        }
        
    // WASD
    } else {
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) ) {
            if ( Y_pos - 25.0f > 14.0f)
                bar.move( 0, - speed * dt.asSeconds() );
        } if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) ) {
            if (Y_pos + 25.0f < Utils::HEIGHT - 14.0f)
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

// void Player::incScore( const int id ) {
//     if ( score > 4 )
//         score = 0;
//     else if ( score >= 0 )
//         score++;
// }

// void Player::resetScore() const {
//     score = 0;
// }

void Player::getScore() {
}