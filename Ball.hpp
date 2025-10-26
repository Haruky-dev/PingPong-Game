#pragma once

#include <SFML/Graphics.hpp>
#include "Utils.hpp"

class Player;

class Ball : public sf::Drawable {
    private:
        sf::CircleShape ball;
        sf::Vector2f direc;
        sf::Vector2f unitDirec;
        sf::Vector2f sPoint;
        Utils::Sides side;

        Player* EastP;
        Player* WestP;
        
        int radius;
        int speed;
        bool start;
        bool moving;
        

    protected:
        virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

    public:
        Ball();
        void LaunchBall();
        void setPlayers( Player& p1, Player& p2 );
        void AdjustPos( Utils::Sides side );
        void ResetPos();
        void UpdateState( const sf::Time& dt );

        sf::FloatRect getBounds() const;
};