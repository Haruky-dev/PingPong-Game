#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

class Player : public sf::Drawable {
    private:
        sf::Sprite bar;
        // sf::Texture scoreTxt;
        double speed;

        static int playersCount;
        int score;
        
        
        
    protected:
        virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
        
    public:
    
        int id;
        Player( const sf::Sprite& spr );
        void UpdateState( sf::Time& dt);
        sf::FloatRect getBounds() const;
        // static void incScore( const int id );
        // static void resetScore() const;

        void getScore();
};