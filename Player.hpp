#pragma once

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable {
    private:
        static int playersCount;
        int id;
        sf::RectangleShape bar;
        int width;
        int height;
        double speed;

        
        
    protected:
        virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
        
    public:
    
        Player( const sf::Color& mainColor, const sf::Color& secColor);
        void UpdateState( sf::Time& dt);
};