// Handles all game resources

#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <string>

class Assets {
    private:
        Assets() = default;
        Assets& operator=(Assets& other) = delete;

        // sf::Font font;
        std::unique_ptr<sf::Texture> bgText;
        std::unique_ptr<sf::Texture> padText;
        std::unique_ptr<sf::Texture> ballText;
        std::unique_ptr<sf::Sprite> bgSprite;
        std::unique_ptr<sf::Sprite> padSprite;
        std::unique_ptr<sf::Sprite> ballSprite;
        std::unique_ptr<sf::Sprite> scoreSprite;
        std::unique_ptr<sf::Sprite> scoreSprite1;

        std::unique_ptr<sf::Texture> SCORE_TEXTS[6];

        // paths
        // static std::string FONT; // = "Resources/arialFont.ttf";
        static std::string BG;
        static std::string PAD;
        static std::string BALL;
        // static std::vector<std::string> SCORE;
        // static inline std::unique_ptr<std::string[]> SCORE;
        
    public:
        // Singleton Accessor
        static Assets& getInst();
        void loadResources();

        static std::string SCORE[6];

        // getters
        sf::Sprite& getBg()   const;
        sf::Sprite& getPad()  const;
        sf::Sprite& getBall() const;
        sf::Sprite& getScore( const int id ) const;
};