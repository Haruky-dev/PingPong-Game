#pragma once

#include <SFML/Graphics.hpp>
#include "Utils.hpp"


// using Vect = std::vector<sf::Vector2f>;

class Ball : public sf::Drawable {
    private:
        sf::CircleShape ball;
        sf::Vector2f direc;
        sf::Vector2f unitDirec;
        sf::Vector2f sPoint;
        Utils::Sides side;
        
        int radius;
        int speed;
        bool start;
        

    protected:
        virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

    public:
        Ball();
        bool CheckCollision();
        void Reposition( Utils::Sides side );
        void UpdateState( const sf::Time& dt );
        const sf::Vector2f getDirec() const;
};