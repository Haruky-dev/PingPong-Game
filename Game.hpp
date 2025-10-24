#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "Utils.hpp"
#include "Player.hpp"
#include "Ball.hpp"

class Game {
    private:
        std::unique_ptr<sf::RenderWindow> win;
        sf::Time dt;
        sf::Clock clk;
        Utils::FrameRate F;

        std::unique_ptr<Player> P1;
        std::unique_ptr<Player> P2;

        std::unique_ptr<Ball> ball;

    public:
        Game(); 
        void load();
        void run();
};