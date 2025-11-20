#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Ball;

class Player : public sf::Drawable {
    private:
        sf::Sprite bar;
        double speed;

        int score;
        int AIspeed;
        
        sf::Time accTime;
        
    protected:
        virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
        
    public:
    
        int id;
        Player( const sf::Sprite& spr, bool side );
            // side; 0: for Human control, 1: for AIs

        void UpdateState( sf::Time& dt);
        void UpdateAI( sf::Time& dt, Ball& ball );

        sf::FloatRect getBounds() const;
        sf::Vector2f getPos() const;
};