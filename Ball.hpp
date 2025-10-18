#pragma once

#include <SFML/Graphics.hpp>
#include <vector>


// using Vect = std::vector<sf::Vector2f>;

class Ball : public sf::Drawable {
    private:
        bool start;
        sf::CircleShape ball;
        int radius;
        int speed;
        sf::Vector2f side;
        sf::Vector2f direc;
        sf::Vector2f unitDirec;
        sf::Vector2f sPoint;

    protected:
        virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

    public:
        Ball();
        bool CheckCollision();
        void Reposition( sf::Vector2f& side );
        void UpdateState( const sf::Time& dt );
        const sf::Vector2f getDirec() const;
};