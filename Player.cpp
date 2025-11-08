#include "Player.hpp"

#include "Utils.hpp"
#include "Assets.hpp"

#include <math.h>

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
}

void Player::UpdateState( sf::Time& dt ) {
    double Y_pos = bar.getPosition().y;
    double halfHeight = this->getBounds().height/2.0f;

    // Arrows
    if (this->id == 1) {
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) {
            if ( Y_pos - halfHeight > 14.0f)
                bar.move( 0, - speed * dt.asSeconds() );
        } if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ) {
            if (Y_pos + halfHeight < Utils::HEIGHT - 14.0f)
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

void Player::UpdateAI( sf::Time& dt, Ball& ball ) {
    double barY = this->bar.getPosition().y;
    double ballY = ball.getPos().y;
    double diffY = ballY - barY;

    // add random error
    // diffY -= (rand() % 120) - 60;
    
    if (ball.moving && (std::abs(diffY) > 20.f)) { // 50px Dead Zone, no reaction
        double mov = this->speed * dt.asSeconds();
        /*
            mov sometimes might be bigger than the actual distance (diffY)
            to the target (due to non-linear 'dt' variance for example).
            Thus, we have to check for that when moving something right?
            That explains the use of 'std:::min()' later on (literally
            doing "if (mov > dist) moveBy(dist); else moveBy(mov)" )
            Hope that you remember it, me or whoever you who's reading it.

            This operation is called Clamping, and the problem it does
            prevent is called 'Overshooting'.
        */

        // if (ball.getDirec().x <= 0) { // ball is moving right
            if (diffY < 0) // ball is ABOVE bar
                this->bar.move( 0.f, -std::min(mov, std::abs(diffY)));
            else // ball is BELLOW bar
                this->bar.move( 0.f, std::min(mov, diffY));
        }

        else {
            double CenterDist = Utils::HEIGHT/2.f - this->getPos().y;
            this->bar.move( 0.f, CenterDist * dt.asSeconds());
        }

        // if (this->getPos().y < 20.f)
        //     this->bar.setPosition(0.f, 20.f);
        // else if (this->getPos().y > Utils::HEIGHT - 20.f)
        //     this->bar.setPosition(0.f, Utils::HEIGHT - 45.f);

}

sf::Vector2f Player::getPos() const {
    return this->bar.getPosition();
}