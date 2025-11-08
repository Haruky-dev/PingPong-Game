#include "Ball.hpp"

#include "Utils.hpp"
#include "Player.hpp"
#include "Assets.hpp"

#include <print>
#include <math.h>

Ball::Ball( const sf::Sprite& spr )
    : start(false), speed(300.f), accTime(sf::Time::Zero),
      moving(false), EastP(nullptr), WestP(nullptr) {

        // !! make better random system on utils
        srand(time(NULL));

        // this->orient = 'l'; // randonize later !!
        // suggested sollution to a random oreint
        char orients[2] = {'l', 'r'};
        this->orient = orients[ rand() % 2 ];

        this->ball = spr;
        auto tempS = spr.getTexture()->getSize();
        this->ball.setOrigin( tempS.x /2.0f, tempS.y /2.0f );      

        this->ResetPos();

}

void Ball::LaunchBall() {
    // target
    if ( this->orient == 'l' )
        direc.x = 0.0f;
    else if (this->orient == 'r')
        direc.x = Utils::WIDTH;
        
    // randPoint = (rand() % (end - start + 1)) + start
    
    //   1st Half         2nd Half
    // [ 0,  200 ]  U  [ 250,  480 ]
    char halfs[2] = {'1', '2'};
    if ( halfs[rand() % 2] == '1' ) {
        direc.y = rand() % 200;
    } else {
        direc.y = (rand() % (230)) + 250;
    }

    // direction = targetPos - currPos;
    direc -= ball.getPosition();

    unitDirec  = Utils::Normalize(direc);
    //velocity = unitDirec * speed;
    velocity.x = unitDirec.x * speed;
    velocity.y = unitDirec.y * speed;

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
        newBallPos.y = BallBounds.width/2.0f + 12.0f;
    else if (side == Utils::Sides::BOTTOM)
        newBallPos.y = Utils::HEIGHT - BallBounds.height/2.0f - 12.0f;
    
    // Resolve sticking for player case
    else if (side == Utils::Sides::LEFT)
        newBallPos.x = PlayBounds.width/2.0f + 35.0f;
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
    if (moving) {
        if ( accTime.asMilliseconds() >= 50.0f ) {
            accTime = sf::Time::Zero;

            // 
            int direc = (unitDirec.x > 0)? 1 : -1;
            ball.rotate( 0.05f * this->speed * direc);

        } else accTime+= dt;
    }
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

    // combine those two
    if ( Utils::checkPlayColl( *EastP, *WestP, *this, side)
      || Utils::checkWallColl(*this, side)) {

        Utils::Reflect(unitDirec, side);
        // update velocity
        this->velocity.x = this->unitDirec.x * this->speed;
        this->velocity.y = this->unitDirec.y * this->speed;

        AdjustPos(side);
    }
}

sf::FloatRect Ball::getBounds() const {
    return this->ball.getGlobalBounds();
}

sf::Vector2f Ball::getPos() const {
    return ball.getPosition();
}

sf::Vector2f Ball::getDirec() const {
    return this->unitDirec;
}