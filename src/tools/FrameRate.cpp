#include <tools/FrameRate.hpp>

#include <json/Json.hpp>

FrameRate::FrameRate()
    : accTime(sf::Time::Zero), frames(0), fps(0), font(),
    txt(font, ""), delay(Json::getFloat("setting.fps_t")) {

        if (!font.openFromFile("assets/RasterForge.ttf"))
            throw std::runtime_error("Unable to load Font");

        txt.setFont(font);
        txt.setString( "" );
        // txt.setScale( 4.f, 4.f );
        // txt.setFillColor( sf::Color::Green);
        txt.setFillColor( sf::Color(255, 165, 171) );
        this->adjTxt();

}

void FrameRate::UpdateState( sf::Time& dt ) {
    this->accTime += dt;
    this->frames++;

    // must be set on conf.json later on
    if ( this->accTime.asSeconds() >=  this->delay ) {
        fps = static_cast<int>( this->frames / this->accTime.asSeconds() );

        txt.setString( std::to_string(fps) );

        this->adjTxt();

        this->accTime = sf::Time::Zero;
        this->frames = 0;
    }
}

void FrameRate::adjTxt() {
    txt.setPosition( {10.f, 10.f} );
}

void FrameRate::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    target.draw( this->txt, states );
}