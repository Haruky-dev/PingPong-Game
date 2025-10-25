// Handles all game resources

#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

class Assets {
    private:
        Assets() = default;
        Assets& operator=(Assets& other) = delete;

        // sf::Font font;
        // is it better to use them as static members or to have an accessing function? 
        // answer: accessing function
        std::unique_ptr<sf::Texture> bgText;
        // std::unique_ptr<sf::Texture> padText;
        // std::unique_ptr<sf::Texture> ballText;
        std::unique_ptr<sf::Sprite> bgSprite;
        // std::unique_ptr<sf::Sprite> padSprite;
        // std::unique_ptr<sf::Sprite> ballSprite;

        // paths
        // static std::string FONT; // = "Resources/arialFont.ttf";
        static std::string BG;   // = "Resources/game-bg.png";
        // static std::string PAD  = "";
        // static std::string BALL;

    public:
        static Assets& getInstance();
        void loadResources();

        // getters
        sf::Sprite& getBg()   const;
        // sf::Sprite& getPad()  const;
        // sf::Sprite& getBall() const;
};