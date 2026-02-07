#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <string>
#include <utility>
#include <optional>
#include <unordered_map>

#include <engine/Progressive.hpp>
#include <engine/StateType.hpp>
#include <entities/Utils.hpp>

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

        std::unordered_map<
            int, std::pair<StateType, sf::IntRect>
        > btnProp;
        /* { buttonID : {parentState (where he leads to), bounds} } */

    public:
        static MenuUI& getInst();

        void Load( Progressive& );

        const sf::Sprite& get( const std::string& id, const int i=-1 ) const;

        StateType btnLabel( const int id ) const;
        sf::IntRect btnBound( const int id ) const;
};