#pragma once

#include <SFML/Graphics.hpp>
#include "Utils.hpp"

class Player;

class Ball : public sf::Drawable {

    friend class Utils;
    friend class Player;
    
    private:
        sf::Sprite ball;
        sf::Vector2f direc;
        sf::Vector2f unitDirec;
        sf::Vector2f velocity;
        Utils::Sides side;

        sf::Time accTime;

        Player* EastP;
        Player* WestP;
        
        int speed;
        char orient; // 'l': left, 'r': right
        bool start;
        bool moving;
            
    protected:
        virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
        
    public:
        Ball( const sf::Sprite& spr );

        void LaunchBall();
        void setPlayers( Player& p1, Player& p2 );
        void AdjustPos( Utils::Sides side );
        void ResetPos();
        void Rotate( const sf::Time& dt );
        void UpdateState( const sf::Time& dt );

        sf::FloatRect getBounds() const;
        sf::Vector2f getPos() const;
        sf::Vector2f getDirec() const;
};