#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <string>
#include <optional>

#include <engine/Progressive.hpp>


class SettingUI {
    private:
        SettingUI() = default;
        ~SettingUI() = default;

        SettingUI( const SettingUI& ) = delete;
        SettingUI( const SettingUI&& ) = delete;

        SettingUI& operator=( const SettingUI& ) = delete;
        SettingUI& operator=( const SettingUI&& ) = delete;

        std::optional<sf::Sprite> bg;
        std::optional<sf::Sprite> shad;

    public:
        static SettingUI& getInst();
        void Load( Progressive& );
        const sf::Sprite& get( const std::string& id, const int i=-1 ) const;
};