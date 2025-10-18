#include <SFML/Graphics.hpp>

class Utils {
    public:
        // Constants
        static int WIDTH;
        static int HEIGHT;

        static double EPSILON;
            // Norms vect
        static sf::Vector2f TOP;
        static sf::Vector2f BOTTOM;
        static sf::Vector2f LEFT;
        static sf::Vector2f RIGHT;


        // Math funcs
        static sf::Vector2f Normalize( const sf::Vector2f& vect );

        static const double Dot( const sf::Vector2f& vect1, const sf::Vector2f& vect2 );

        static void Reflect( sf::Vector2f& vect, const sf::Vector2f& norm );

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

