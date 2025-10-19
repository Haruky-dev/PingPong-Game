#include "Ball.hpp"

#include "Utils.hpp"

#include <print>

Ball::Ball() : radius(10.f), start(true), speed(400.f), moving(true) {
    ball.setRadius( radius );
    ball.setFillColor( sf::Color::White );
    // ball.setOutlineThickness(1.f);
    // ball.setOutlineColor( sf::Color::White);
    ball.setPosition( Utils::WIDTH/2.f, Utils::HEIGHT/2.f );

    srand(time(NULL));
}

void Ball::draw( sf::RenderTarget& target, sf::RenderStates states ) const  {
    target.draw(ball, states);
}

bool Ball::CheckCollision() {
    // Check TOP collistiond
    sf::FloatRect pos = this->ball.getGlobalBounds();

    if (pos.top <= 0) {
        side = Utils::Sides::TOP;
        return true;

    } else if ((pos.top + pos.height) >= Utils::HEIGHT) {
        side = Utils::Sides::BOTTOM;
        return true;

    } else if (pos.left <= 0) {
        side = Utils::Sides::LEFT;
        return true;

    } else if (pos.left + pos.width >= Utils::WIDTH) {
        side = Utils::Sides::RIGHT;
        return true;
    }

    // return side != Utils::Sides::NONE;
    return false;
}

void Ball::Reposition( Utils::Sides side ) {
    sf::FloatRect pos = ball.getGlobalBounds();
    sf::Vector2f newPos = ball.getPosition();
    // sf::Vector2f pos = ball.getPosition();
    
    if (side == Utils::Sides::TOP) {
        newPos.y = pos.top;

    } else if (side == Utils::Sides::BOTTOM) {
        newPos.y = Utils::HEIGHT - pos.height;

    } else if (side == Utils::Sides::LEFT) {
        newPos.x = pos.left;

    } else if (side == Utils::Sides::RIGHT) {
        newPos.x = Utils::WIDTH - pos.width;
    }

    // side = Utils::Sides::NONE;
    ball.setPosition( newPos );
}

void Ball::ResetPos() {
    ball.setPosition( Utils::WIDTH/2.f, Utils::HEIGHT/2.f );
    moving = false;
}

void Ball::UpdateState( const sf::Time& dt ) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        Ball::ResetPos();

    if (start) {
        direc.x = Utils::WIDTH;
        direc.y = (rand() % (Utils::HEIGHT));
        
        // Target
        // direc.x = (rand() % (Utils::WIDTH));
        // direc.y = 0.f;
        
        // calc direc
            // direc = target - curr
        direc -= ball.getPosition();
        unitDirec = Utils::Normalize(direc);
        start = false;   
        moving = true;
    }
    
    if (moving)
        ball.move( speed * dt.asSeconds() * unitDirec );


    // if (CheckCollision()) {
    //     // Utils::Reflect(this->direc, side);
    //     Utils::Reflect(this->unitDirec, side);
    //     // unitDirec = Utils::Normalize(direc);
    //     // reposition
    //     Reposition(side);
    // }
    if (Utils::checkWallColl(*this, side)) {
        Utils::Reflect(unitDirec, side);
        Reposition(side);
    }
}

sf::FloatRect Ball::getBounds() const {
    return this->ball.getGlobalBounds();
}