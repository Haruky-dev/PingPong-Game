#include "Player.hpp"

#include "Ball.hpp"
#include "Utils.hpp"

#include <math.h>

Player::Player( const sf::Sprite& spr, bool side )
    : speed(500), score(0), accTime(sf::Time::Zero), AIspeed(100)
    {

    this->bar = spr;
    auto tempS = spr.getTexture()->getSize();
    this->bar.setOrigin( tempS.x /2.0f, tempS.y /2.0f );


    if ( side ) {
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
    /*
        Paussible areas to feeble AI
            - add delay before reaction
            - drop speed
            - react only when the ball is somewhat near
            - 
    */
    // Second Approach - Prediction
    double TakenTime  = std::abs((ball.getPos().x - this->getPos().x) / ball.getVelocity().x);
    double estimatedY = ball.getPos().y + ball.getVelocity().y * TakenTime;

    while (estimatedY < 0 || estimatedY > Utils::HEIGHT) {
        if (estimatedY < 0)
            estimatedY = -estimatedY;
        else
            estimatedY = Utils::HEIGHT * 2 - estimatedY;
    }

    double diffY = estimatedY - this->bar.getPosition().y; 

        // Movement Logic
    if (ball.moving && (std::abs(diffY) > 20.f)) { // 20px Dead Zone, no reaction
        double mov = this->AIspeed * dt.asSeconds();
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

        if (ball.getDirec().x <= 0) { // ball is moving towards AI / East Player
            if (diffY < 0) // future ballY is ABOVE AI bar
                this->bar.move( 0.f, -std::min(mov, std::abs(diffY)));
            else // future ballY is BELLOW AI bar
                this->bar.move( 0.f, std::min(mov, diffY));
        }
    }

        // Return to Center Logic
            // (When ball is not moving || moving towards West Player)
    if ( (!ball.moving) ||
        ((accTime.asSeconds() <= 50.0f) && (ball.getDirec().x > 0)))
    {
        this->accTime += dt;
        // try K = elapsedTime / movDuration;
        // that makes sure it's between 0 and 1
            // and it tracks the progress
        double K = accTime.asSeconds() /  50.0f; // 1.0f: Animation Duration
        // K = (K < 0.0f)? 0 : (K > 1.0f)? 1 : K;
        K = std::clamp(K, (double) 0.0f, (double) 1.0f);

        // double fk = K * K;
        double fk = K*K * (3 - 2*K);

        double targetY = getPos().y + (Utils::HEIGHT/2.0f - getPos().y) * fk;
        double step = targetY - getPos().y;

        this->bar.move( 0.f, step);
       }

    else if (ball.getDirec().x <= 0) {
        accTime = sf::Time::Zero;
    }
}

sf::Vector2f Player::getPos() const {
    return this->bar.getPosition();
}