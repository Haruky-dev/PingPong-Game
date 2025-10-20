#include "Ball.hpp"

#include "Utils.hpp"
#include "Player.hpp"

#include <iostream>
#include <math.h>

Ball::Ball()
    : radius(10.f), start(true), speed(400.f),
      moving(false), EastP(nullptr), WestP(nullptr) {

        ball.setRadius( radius );
        ball.setFillColor( sf::Color::White );
        ball.setPosition( Utils::WIDTH/2.f, Utils::HEIGHT/2.f );

        srand(time(NULL));
}

void Ball::LauchBall() {
    // target
    direc.x = 0.0f;
    direc.y = (rand() % (Utils::HEIGHT));

    // direction = targetPos - currPos;
    direc -= ball.getPosition();
    // direc.x = (rand() % (Utils::WIDTH));
    // direc.y = 0.f;       

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
        newBallPos.y = BallBounds.top;
    else if (side == Utils::Sides::BOTTOM)
        newBallPos.y = Utils::HEIGHT - BallBounds.height;
    
    // Resolve sticking for player case
    else if (side == Utils::Sides::LEFT)
        newBallPos.x = BallBounds.left + PlayBounds.width + 5.0f; // I couldn't find a way other than hard code it :)
    else if (side == Utils::Sides::RIGHT)
        newBallPos.x = Utils::WIDTH - PlayBounds.width - 35.0f; // so as that :)
    
    ball.setPosition( newBallPos );
}

void Ball::ResetPos() {
    ball.setPosition( Utils::WIDTH/2.f, Utils::HEIGHT/2.f );
    moving = false;
}

void Ball::UpdateState( const sf::Time& dt ) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        Ball::ResetPos();

    if (start) {
        this->LauchBall();
        start = false;
    }
    
    if (moving)
        ball.move( speed * dt.asSeconds() * unitDirec );
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