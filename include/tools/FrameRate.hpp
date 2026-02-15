#pragma once

#include <SFML/Graphics.hpp>

class FrameRate : public sf::Drawable {
    sf::Font font;
    sf::Text txt;

    sf::Time accTime;
    float delay;
    int frames, fps;

    void adjTxt();

    protected:
        virtual void draw( sf::RenderTarget&, sf::RenderStates ) const override;

    public:
        FrameRate();
        void UpdateState( sf::Time& );
};