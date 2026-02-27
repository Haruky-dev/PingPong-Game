#include <cassert>
#include <entities/Ball.hpp>

#include <entities/Player.hpp>

#include <tools/Tool.hpp>
#include <tools/Math.hpp>
#include <tools/Json.hpp>

#include <cache/SoundCache.hpp>

#include <math.h>


Ball::Ball( const sf::Sprite& spr )
    : ball(spr), start(false), cd(0), accTime(sf::Time::Zero),
      moving(false), EastP(nullptr), WestP(nullptr),
      padHit( SoundCache::getInst().get("padHit")), wallHit( SoundCache::getInst().get("wallHit")),
      speed(Json::getFloat("ball.speed")), accel(Json::getFloat("ball.accel")) {

        // !! make better random system on utils
        srand(time(NULL));

        char orients[2] = {'l', 'r'};
        this->orient = orients[ rand() % 2 ];

        this->ball.setOrigin(
            sf::Vector2f(spr.getTexture().getSize()) / 2.f
        );

        this->ResetPos();
}

void Ball::LaunchBall() {
    // target
    if ( this->orient == 'l' )
        direc.x = 0.0f;
    else if (this->orient == 'r')
        direc.x = Tool::WIDTH;
        
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

    unitDirec  = Math::Normalize(direc);
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

void Ball::AdjustPos( Tool::Sides side ) {
    assert( EastP && WestP );

    sf::FloatRect BallBounds = getBounds();
    sf::FloatRect PlayBounds = EastP->getBounds();
    sf::Vector2f newBallPos = ball.getPosition();
    
    switch ( side ) {
        case Tool::Sides::TOP:
            newBallPos.y = BallBounds.size.x/2.0f + 12.0f;
            break;
        case Tool::Sides::BOTTOM:
            newBallPos.y = Tool::HEIGHT - (BallBounds.size.x/2.0f + 12.0f);
            break;
        case Tool::Sides::LEFT:
            newBallPos.x = PlayBounds.size.x/2.f + 35.f;
            break;
        case Tool::Sides::RIGHT:
            newBallPos.x = Tool::WIDTH - (PlayBounds.size.x/2.f + 35.f);
            break;
    }

    this->speed += this->accel;
    ball.setPosition( newBallPos );
}

void Ball::ResetPos() {
    ball.setPosition( Tool::W_CTR );
    moving = false;
    start = true;
    // reset speed
    this->speed = Json::getFloat("ball.speed");
}

void Ball::Rotate( const sf::Time& dt ) {
    if (moving) {
        if ( accTime.asMilliseconds() >= Json::getFloat("ball.rot") ) {
            accTime = sf::Time::Zero;

            // 
            int direc = (unitDirec.x > 0)? 1 : -1;
            // ball.rotate( 0.05f * this->speed * direc);
            ball.rotate( sf::Angle( sf::degrees(0.05f * this->speed * direc) ));

        } else accTime+= dt;
    }
}

void Ball::UpdateState( const sf::Time& dt ) {
    
    if (!moving && start) {
        if (accTime.asSeconds() >= 3.0f) {
            this->LaunchBall();
            start = false;
            // moving = true;
            accTime = sf::Time::Zero;
        } else {
            accTime+=dt;
            cd = (int) accTime.asSeconds();
            if (cd == 3) cd = -1;
        }
    }

    else if (moving) {
        Rotate( dt );
        ball.move( speed * dt.asSeconds() * unitDirec );
    }

    if ( Tool::checkPlayColl( *EastP, *WestP, *this, side)
      || Tool::checkWallColl(*this, side)) {

        if (side == Tool::Sides::LEFT || side == Tool::Sides::RIGHT) {
            this->padHit.play();
        } else {
            this->wallHit.play();
        }

        Math::Reflect(unitDirec, side);
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

/* if (ball.getDirec().x <= 0) // ball is moving towards LEFT. */
sf::Vector2f Ball::getDirec() const {
    return this->unitDirec;
}

sf::Vector2f Ball::getVelocity() const {
    return this->velocity;
}