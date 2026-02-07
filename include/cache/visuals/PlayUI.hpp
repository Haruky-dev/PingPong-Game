#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <string>
#include <optional>

#include <engine/Progressive.hpp>

class PlayUI {
    private:
        PlayUI() = default;
        ~PlayUI() = default;

        PlayUI( const PlayUI& ) = delete;
        PlayUI( const PlayUI&& ) = delete;

        PlayUI& operator=( const PlayUI& ) = delete;
        PlayUI& operator=( const PlayUI&& ) = delete;

        std::optional<sf::Sprite> bg;
        std::optional<sf::Sprite> pad;
        std::optional<sf::Sprite> ball;
        std::optional<sf::Sprite> countD;
        std::optional<sf::Sprite> score_1;
        std::optional<sf::Sprite> score_2;

    public:
        static PlayUI& getInst();
        void Load( Progressive& );
        const sf::Sprite& get( const std::string& id, int i=-1 );
};