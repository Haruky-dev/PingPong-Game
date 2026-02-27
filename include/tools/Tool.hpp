#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_map>

class Ball;
class Player;


class Tool {
    public:
        static int P1_SCORE;
        static int P2_SCORE;

        static int WIDTH;
        static int HEIGHT;
        static float f_WIDTH;
        static sf::Vector2f W_CTR;

        enum class Sides {
            TOP, LEFT, BOTTOM, RIGHT
        };

        // changed to an array later on
        static std::unordered_map<Tool::Sides, sf::Vector2f> Norms;

        static sf::IntRect getBound( const sf::Sprite& spr );
        static bool checkWallColl( Ball& ball, Tool::Sides& side );
        static bool checkPlayColl( const Player& p1, const Player& p2, Ball& ball, Tool::Sides& side );
};