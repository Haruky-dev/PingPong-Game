#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include "Ball.hpp"

class Player : public sf::Drawable {
    private:
        sf::Sprite bar;
        double speed;

        static int playersCount;
        int score;
        
        // sf::Time dbgTime;
        // char dbgMsg;
        
        
    protected:
        virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
        
    public:
    
        int id;
        Player( const sf::Sprite& spr );

        void UpdateState( sf::Time& dt);
        void UpdateAI( sf::Time& dt, Ball& ball );

        sf::FloatRect getBounds() const;
        sf::Vector2f getPos() const;
};