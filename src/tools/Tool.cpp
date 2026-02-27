#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <tools/Tool.hpp>

#include <tools/Json.hpp>
#include <entities/Ball.hpp>
#include <entities/Player.hpp>


int Tool::WIDTH = Json::getInt("win.W");
int Tool::HEIGHT = Json::getInt("win.H");

float Tool::f_WIDTH = Tool::WIDTH / 5.f;

sf::Vector2f Tool::W_CTR = {
    Tool::WIDTH / 2.0f,
    Tool::HEIGHT / 2.0f
};

int Tool::P1_SCORE = 0;
int Tool::P2_SCORE = 0;

std::unordered_map<Tool::Sides, sf::Vector2f> Tool::Norms = {
    { Tool::Sides::TOP,    {0.f, -1.f} },
    { Tool::Sides::BOTTOM, {0.f, 1.f}  },
    { Tool::Sides::LEFT,   {-1.f, 0.f} },
    { Tool::Sides::RIGHT,  {1.f, 0.f}  },
};

sf::Rect<int> Tool::getBound( const sf::Sprite& spr ) {
    return sf::IntRect(
        static_cast<sf::Vector2i>(spr.getGlobalBounds().position),
        static_cast<sf::Vector2i>(spr.getGlobalBounds().size)
    );
}

bool Tool::checkWallColl( Ball& ball, Tool::Sides& side ) {
    sf::FloatRect pos = ball.getBounds();


    // Check if ball is within collable area !!!

    if (pos.position.y <= 12.f) { // 12px of the background edge
        side = Tool::Sides::TOP;
        return true;
    } else if ((pos.position.y + pos.size.y) >= Tool::HEIGHT - 12.0f) {
        side = Tool::Sides::BOTTOM;
        return true;
    } 

    // goal case
    if ( pos.position.x <= 0 ) {
        ball.ResetPos();

        if (Tool::P2_SCORE > Json::getInt("setting.maxScore"))
            throw std::runtime_error("Game Over. Invalid Value Reached");

        ball.orient = 'l';
        Tool::P2_SCORE++;
    }
    else if ((pos.position.x + pos.size.x) >= Tool::WIDTH) {
        ball.ResetPos();

        if (Tool::P1_SCORE > Json::getInt("setting.maxScore"))
            throw std::runtime_error("Game Over. Invalid Value Reached" );

        ball.orient = 'r';
        Tool::P1_SCORE++;
    }
    
    return false;
}

bool Tool::checkPlayColl( const Player& p1, const Player& p2, Ball& ball, Tool::Sides& side ) {
    sf::Rect<float> ballPos = ball.getBounds();

    if ( ballPos.position.x > (Tool::WIDTH - Tool::f_WIDTH) ) {
        if (p1.getBounds().findIntersection( ball.getBounds() ).has_value()) {
            side = Tool::Sides::RIGHT;
            return true;
        }    
    }
    
    else if ( ballPos.position.x < Tool::f_WIDTH ) {
        if (p2.getBounds().findIntersection( ball.getBounds() ).has_value()) {
            side = Tool::Sides::LEFT;
            return true;
        }
    }
    
    return false;
}