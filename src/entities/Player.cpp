#include <entities/Player.hpp>

#include <entities/Ball.hpp>
#include <tools/Tool.hpp>
#include <tools/Math.hpp>
#include <tools/Json.hpp>

#include <math.h>

Player::Player(const sf::Sprite &spr, bool side)
    : bar(spr), score(0), accTime(0.f), speed(Json::getFloat("p.speed")),
    AIspeed(Json::getFloat("ai.speed")) {

    this->bar.setOrigin({
        sf::Vector2f(this->bar.getTexture().getSize()) / 2.f
    });

    if (side) {
        this->id = 1;
        bar.setPosition({Tool::WIDTH - 20.f, Tool::HEIGHT / 2.f});
    } else {
        this->id = 2;
        bar.setPosition({20.f, Tool::HEIGHT / 2.f});
        this->bar.setRotation( sf::Angle( sf::degrees(180.f) ));
    }
}

void Player::UpdateState(sf::Time &dt) {
    assert( this->id == 1 );
    
    double Y_pos = bar.getPosition().y;
    double halfHeight = this->getBounds().size.y / 2.0f;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        if (Y_pos - halfHeight > 12.0f)
            bar.move({0, -speed * dt.asSeconds()});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        if (Y_pos + halfHeight < Tool::HEIGHT - 12.0f)
            bar.move({0, speed * dt.asSeconds()});
    }
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(bar, states);
}

sf::FloatRect Player::getBounds() const {
    return this->bar.getGlobalBounds();
}

void Player::UpdateAI(sf::Time &dt, Ball &ball) {
    /*
        Possible areas to feeble AI
            - add retDur before reaction
            - drop speed
            - react only when the ball is somewhat near
            -
    */
    // Second Approach - Prediction
    // why the errors of "incomplete type'ball' is not allowed"?
    // because Ball is forward declared only in Player.hpp
    // solution:
    double TakenTime = std::abs((ball.getPos().x - this->getPos().x) / ball.getVelocity().x);
    double estimatedY = ball.getPos().y + ball.getVelocity().y * TakenTime;

    // Reversing 'estimatedY' when the ball is doomed to hit a wall and reflect
    while (estimatedY < 0 || estimatedY > Tool::HEIGHT) {
        if (estimatedY < 0)
            estimatedY = -estimatedY;
        else
            estimatedY = Tool::HEIGHT * 2 - estimatedY;
    }

    double diffY = estimatedY - this->bar.getPosition().y;

    // Movement Logic
    if (ball.moving && (std::abs(diffY) > Json::getFloat("ai.deadZone"))) {
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
                this->bar.move({0.f, (float) -std::min(mov, std::abs(diffY))});
            else // future ballY is BELLOW AI bar
                this->bar.move({0.f, (float) std::min(mov, diffY)});
        }
    }

    // Return to Center Logic
    // (When ball is not moving || moving towards West Player)
    if ((!ball.moving) ||
        ((accTime <= Json::getFloat("ai.retTime")) &&
            (ball.getDirec().x > 0)
    )) {
        
        this->accTime += dt.asSeconds();
        
        float K = accTime / Json::getFloat("ai.retDur"); 
        K = std::clamp( K, 0.0f, 1.f );

        float targetY = Math::Lerp(this->getPos().y, Tool::HEIGHT / 2.0f, Math::easeOut(K));
        float step = targetY - getPos().y;

        this->bar.move({0.f, step});
    }

    else if (ball.getDirec().x <= 0) {
        accTime = 0.f;
    }
}

sf::Vector2f Player::getPos() const { return this->bar.getPosition(); }