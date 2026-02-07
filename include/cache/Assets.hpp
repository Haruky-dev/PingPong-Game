// Handles all game resources

#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <memory>
#include <vector>
#include <string>

#include "StateMachine/StateType.hpp"

class Progressive;


class Assets {
    private:
        Assets() = default;
        Assets& operator=(Assets& other) = delete;

        // Pairs of <ID, StateType>, StateType here doesn't denote
            // what state does the button (from its ID) belong to.
            // it points to what State should this button leads
            // I know it's not the best thing, but I choosed simplicity
        static std::unordered_map<int, StateType> buttonLabels;

        // [PLAY] State Assets
        std::unique_ptr<sf::Texture> bgText;
        std::unique_ptr<sf::Texture> padText;
        std::unique_ptr<sf::Texture> ballText;
        std::unique_ptr<sf::Sprite> bgSprite;
        std::unique_ptr<sf::Sprite> padSprite;
        std::unique_ptr<sf::Sprite> ballSprite;
        std::unique_ptr<sf::Sprite> scoreSprite;
        std::unique_ptr<sf::Sprite> scoreSprite1;
        std::unique_ptr<sf::Sprite> countDSprite;

        std::unique_ptr<sf::Texture> SCORE_TEXTS[6];
        std::unique_ptr<sf::Texture> CD_TEXTS[6];

        // [MAINMENU] State Assets
        std::unique_ptr<sf::Texture> MainMenuTxt;
        std::unique_ptr<sf::Sprite> MainMenuSpr;

        std::unique_ptr<sf::Texture> BTN_TXT[6];
        std::unique_ptr<sf::Sprite> BTN_SPR[3];

        // [Setting] State Assets
        std::unique_ptr<sf::Texture> SettTxt;
        std::unique_ptr<sf::Sprite> SettSpr;
        std::unique_ptr<sf::Texture> ShadTxt;
        std::unique_ptr<sf::Sprite> ShadSpr;

        static std::string BG;
        static std::string PAD;
        static std::string BALL;
        static std::string CD[3];
        static std::string SCORE[6];

        static std::string MAIN_MENU;
        static std::string MM_BTNS[6];
        static std::string SETT;
        static std::string SHAD;
        
    public:
        // Singleton Accessor
        static Assets& getInst();
        void Load( Progressive& prog );

        // getters

            // [PLAY] State
        sf::Sprite& getBg()   const;
        sf::Sprite& getPad()  const;
        sf::Sprite& getBall() const;
        sf::Sprite& getScore( const int id ) const;
        sf::Sprite& getCD( const int n ) const;

            // [MAIN_MENU] State
        sf::Sprite&   getMainBg() const;
        sf::Sprite&   getMMBtn( const int id, bool hover) const;
        sf::Sprite&   getSettingMenu() const;
        sf::Sprite&   getShadow() const;
        sf::Rect<int> getButtonBound( const int id ) const;
        StateType     getButtonLabel( const int id ) const;

            // [SETTING] State
};