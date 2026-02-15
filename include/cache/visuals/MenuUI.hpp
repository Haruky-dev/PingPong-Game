#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <string>
#include <optional>

#include <engine/Progressive.hpp>
#include <engine/State.hpp>
#include <engine/input/Action.hpp>
#include <tools/Tool.hpp>

#define BTN_COUNT 3

class MenuUI {
    private:
        MenuUI() = default;
        ~MenuUI() = default;

        MenuUI( const MenuUI& ) = delete;
        MenuUI( const MenuUI&& ) = delete;

        MenuUI& operator=( const MenuUI& ) = delete;
        MenuUI& operator=( const MenuUI&& ) = delete;

        std::optional<sf::Sprite> bg;
        std::optional<sf::Sprite> btns[BTN_COUNT];

        sf::Rect<int> b_bounds[BTN_COUNT];

    public:
        static MenuUI& getInst();

        void Load( Progressive& );

        const sf::Sprite& get( const std::string& id, const int i=-1 ) const;

        const sf::Rect<int>& btnBound( const int id ) const;
};