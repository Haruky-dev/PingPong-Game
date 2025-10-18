#include "Ball.hpp"
#include "Utils.hpp"

#include <print>

Ball::Ball() : radius(10.f), start(true), speed(200.f) {
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
        side = Utils::TOP;
        return true;
    } else if ((pos.top + pos.height) >= Utils::HEIGHT) {
        side = Utils::BOTTOM;
        return true;
    } else if (pos.left <= 0) {
        // std::println("\n{}", pos.left);
        side = Utils::LEFT;
        return true;
    } else if (pos.left + pos.width >= Utils::WIDTH) {
        side = Utils::RIGHT;
        return true;
    }

    return false;
}

void Ball::Reposition( sf::Vector2f& side ) {
    sf::FloatRect pos = ball.getGlobalBounds();
    sf::Vector2f newPos = ball.getPosition();
    // sf::Vector2f pos = ball.getPosition();
    
    if (side == Utils::TOP) {
        newPos.y = pos.top;
    } else if (side == Utils::BOTTOM) {
        newPos.y = Utils::HEIGHT - pos.height;
    } else if (side == Utils::LEFT) {
        newPos.x = pos.left;
    } else if (side == Utils::RIGHT) {
        newPos.x = Utils::WIDTH - pos.width;
    }

    ball.setPosition( newPos );
}

void Ball::UpdateState( const sf::Time& dt ) {
    if (start) {
        // direc.x = 0;
        // direc.y = (rand() % (Utils::HEIGHT));
        
        // Target
        direc.x = (rand() % (Utils::WIDTH));
        direc.y = 0.f;
        
        // calc direc
            // direc = target - curr
        direc -= ball.getPosition();
        unitDirec = Utils::Normalize(direc);
        start = false;
    } else {

    }

    ball.move( speed * dt.asSeconds() * unitDirec );


    if (CheckCollision()) {
        // Utils::Reflect(this->direc, side);
        Utils::Reflect(this->unitDirec, side);
        // unitDirec = Utils::Normalize(direc);
        // reposition
        Reposition(side);
    }
}

const sf::Vector2f Ball::getDirec() const {
    return direc;
}