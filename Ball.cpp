#include "Ball.hpp"

#include "Utils.hpp"
#include "Player.hpp"
#include "Assets.hpp"

#include <print>
#include <math.h>

Ball::Ball( const sf::Sprite& spr )
    : start(false), speed(300.f), accTime(sf::Time::Zero),
      moving(false), EastP(nullptr), WestP(nullptr) {

        this->ball = spr;
        auto tempS = spr.getTexture()->getSize();
        this->ball.setOrigin( tempS.x /2.0f, tempS.y /2.0f );

        this->ResetPos();

        // !! make better random system on utils
        srand(time(NULL));
}

void Ball::LaunchBall() {
    // target
    direc.x = 0.0f;
    // randPoint = (rand() % (end - start + 1)) + start
    direc.y = (rand() % (Utils::HEIGHT));
    // direc.y = (rand() % (static_cast<int>(Utils::HEIGHT/2.f) + 1)) + Utils::HEIGHT/2.f;
    // direc.y = (rand() % (static_cast<int>(Utils::HEIGHT) + 1)) + Utils::HEIGHT/2.f;

    // direction = targetPos - currPos;
    direc -= ball.getPosition();

    unitDirec = Utils::Normalize(direc);
    moving = true;
}

void Ball::setPlayers( Player& p1, Player& p2 ) {
    this->EastP = &p1;
    this->WestP = &p2;
}

void Ball::draw( sf::RenderTarget& target, sf::RenderStates states ) const  {
    target.draw(ball, states);
}

void Ball::AdjustPos( Utils::Sides side ) {
    if (! (EastP && WestP))
        throw std::runtime_error("Error Occured! Unsufficient Number of Players.");

    sf::FloatRect BallBounds = getBounds();
    sf::FloatRect PlayBounds = EastP->getBounds();
    sf::Vector2f newBallPos = ball.getPosition();

    // hits top/bottom walls
    if (side == Utils::Sides::TOP)
        // newBallPos.y = BallBounds.top + this->radius;
        // newBallPos.y = this->radius + 12.0f; // 12px of the bg edge
        newBallPos.y = BallBounds.width/2.0f + 12.0f;
    else if (side == Utils::Sides::BOTTOM)
        newBallPos.y = Utils::HEIGHT - BallBounds.height/2.0f - 12.0f;
    
    // Resolve sticking for player case
    else if (side == Utils::Sides::LEFT)
        newBallPos.x = PlayBounds.width/2.0f + 35.0f;
        // newBallPos.x = BallBounds.left + PlayBounds.width + 5.0f; // I couldn't find a way other than hard code it :)
    else if (side == Utils::Sides::RIGHT)
        newBallPos.x = Utils::WIDTH - PlayBounds.width/2.0f - 35.0f; // so as that :)
    
    this->speed += 20;

    ball.setPosition( newBallPos );
}

void Ball::ResetPos() {
    ball.setPosition( Utils::WIDTH/2.0f, Utils::HEIGHT/2.0f );
    moving = false;
    this->speed = 300.0f;
}

void Ball::Rotate( const sf::Time& dt ) {
    if (moving)
        if ( accTime.asMilliseconds() >= 50.0f ) {
            accTime = sf::Time::Zero;
            ball.rotate(10.0f);
        }
        else accTime+= dt;
}

void Ball::UpdateState( const sf::Time& dt ) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        Ball::ResetPos();

    if (start) {
        this->LaunchBall();
        start = false;
    }
    
    if (moving) {
        Rotate( dt );
        ball.move( speed * dt.asSeconds() * unitDirec );
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        start = true;
    }

    if (Utils::checkPlayColl( *EastP, *WestP, *this, side)) {
        Utils::Reflect(unitDirec, side);
        AdjustPos(side);
    }

    else if (Utils::checkWallColl(*this, side)) {
        Utils::Reflect(unitDirec, side);
        AdjustPos(side);
    }
}

sf::FloatRect Ball::getBounds() const {
    return this->ball.getGlobalBounds();
}