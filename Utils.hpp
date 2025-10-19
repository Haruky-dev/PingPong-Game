#pragma once

#include <SFML/Graphics.hpp>
#include <map>

class Ball;
class Player;

class Utils {
    public:
        // Constants
        static int WIDTH;
        static int HEIGHT;

        static double EPSILON;

        // Norms vect
            // Normal Vects on each side
        enum class Sides {
            TOP, LEFT, BOTTOM, RIGHT
        };

        static std::map<Utils::Sides, sf::Vector2f> Norms;

        // Math funcs
        static sf::Vector2f Normalize( const sf::Vector2f& vect );

        static const double Dot( const sf::Vector2f& vect1, const sf::Vector2f& vect2 );

        static void Reflect( sf::Vector2f& vect, Utils::Sides side );

        static bool checkWallColl( Ball& ball, Utils::Sides& side );

        // static void checkPlayColl( const Player& p1, Player& p2 );

        // FPS Counting
        class FrameRate : public sf::Drawable {
            private:
                sf::Text txt;
                sf::Font font;

                sf::Time accTime; // Accumulated time
                int frames, fps;

                void centerText();
            
            protected:
                virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
            
            public:
                FrameRate();

                void UpdateState( sf::Time& dt );
        };
};

