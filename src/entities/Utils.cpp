#include <entities/Utils.hpp>

#include <math.h>

#include <json/Json.hpp>
#include <entities/Player.hpp>
#include <entities/Ball.hpp>

int Utils::WIDTH = Json::getInt("win.W");
int Utils::HEIGHT = Json::getInt("win.H");

sf::Vector2f Utils::W_CTR = {
    Utils::WIDTH / 2.0f,
    Utils::HEIGHT / 2.0f
};

int Utils::P1_SCORE = 0;
int Utils::P2_SCORE = 0;

std::unordered_map<Utils::Sides, sf::Vector2f> Utils::Norms = {
    {Utils::Sides::TOP, {0.f, -1.f}},
    {Utils::Sides::BOTTOM, {0.f, 1.f}},
    {Utils::Sides::LEFT, {-1.f, 0.f}},
    {Utils::Sides::RIGHT, {1.f, 0.f}},
};

sf::Vector2f Utils::Normalize( const sf::Vector2f& vect ) {
    const double M = std::sqrt( (vect.x * vect.x  +   vect.y * vect.y) ); // Magnitude
    
    if (M <= 0.00f) return sf::Vector2f( 0.f, 0.f );

    sf::Vector2f UnitVect(vect.x / M, vect.y / M);

    return UnitVect;
}

const double Utils::Dot( const sf::Vector2f& vect1, const sf::Vector2f& vect2 ) {
    return static_cast<double>( vect1.x*vect2.x  +  vect1.y*vect2.y );
}

void Utils::Reflect( sf::Vector2f& vect, Utils::Sides side ) {
    sf::Vector2f n = Utils::Normalize(Utils::Norms.at(side));

    if (n.x == 0.f && n.y == 0.f) return;

    const double dotProd = Utils::Dot( vect, n );
    vect.x = vect.x - 2.f * dotProd * n.x;
    vect.y = vect.y - 2.f * dotProd * n.y;
}

double Utils::Lerp( const double A, const double B, const double t ) {
    return ( A + (B - A) * t );
}

sf::Vector2f Utils::Lerp( const sf::Vector2f& A, const sf::Vector2f& B, const double t ) {
    return sf::Vector2f(
        A.x + (B.x - A.x) * t,
        A.y + (B.y - A.y) * t
    );
}

double Utils::easeIn( const double x ) {
    return x * x * x;
}
double Utils::easeOut( const double x ) {
    return 1 - (1-x)*(1-x)*(1-x);
}
double Utils::easeInOut( const double x ) {
    return (x < 0.5f)? 4.f * x * x * x :
        1 - ( (-2.f * x + 2)*(-2.f * x + 2)*(-2.f * x + 2) ) /2.f;
}
sf::IntRect Utils::getBound( const sf::Sprite& spr ) {
    return sf::IntRect(
        static_cast<sf::Vector2i>(spr.getPosition()),
        // static_cast<sf::Vector2i>(spr.getGlobalBounds().position),
        static_cast<sf::Vector2i>(spr.getGlobalBounds().size)
    );
}

bool Utils::checkWallColl( Ball& ball, Utils::Sides& side ) {
    sf::FloatRect pos = ball.getBounds();


    // Check if ball is within collable area !!!

    if (pos.position.y <= 12.f) { // 12px of the background edge
        side = Utils::Sides::TOP;
        return true;
    } else if ((pos.position.y + pos.size.y) >= Utils::HEIGHT - 12.0f) {
        side = Utils::Sides::BOTTOM;
        return true;
    } 

    // goal case
    if ( pos.position.x <= 0 ) {
        ball.ResetPos();

        // safe check
        if (Utils::P2_SCORE > 5)
            throw std::runtime_error("Game Over. Invalid Value Reached");

        ball.orient = 'l';
        Utils::P2_SCORE++;
    }
    else if ((pos.position.x + pos.size.x) >= Utils::WIDTH) {
        ball.ResetPos();

        // safe check
        if (Utils::P1_SCORE > 5)
            throw std::runtime_error("Game Over. Invalid Value Reached" );

        ball.orient = 'r';
        Utils::P1_SCORE++;
    }
    
    return false;
}

bool Utils::checkPlayColl( const Player& p1, const Player& p2, Ball& ball, Utils::Sides& side ) {
    if (! (&p1 && &p2))
        throw std::runtime_error("Error Occured! Insufficient number of Player.");

    // Check if ball is in collable area first !!!!
        // Compare performance, if not notable,
            // implement a grid based collision detector


    // !! needs better collision check later
    if (p1.getBounds().findIntersection( ball.getBounds() ).has_value()) {
    // if (p1.getBounds().intersects(ball.getBounds())) {
        side = Utils::Sides::RIGHT;
        return true;
    }

    else if (p2.getBounds().findIntersection( ball.getBounds() ).has_value()) {
    // else if (p2.getBounds().intersects(ball.getBounds())) {
        side = Utils::Sides::LEFT;
        return true;
    }

    return false;
}

Utils::FrameRate::FrameRate()
    : accTime(sf::Time::Zero), frames(0), fps(0), font(), txt(font, "") {

        if (!font.openFromFile("assets/RasterForge.ttf"))
            throw std::runtime_error("Unable to load Font");

        txt.setFont(font);
        txt.setString( "" );
        // txt.setScale( 4.f, 4.f );
        // txt.setFillColor( sf::Color::Green);
        txt.setFillColor( sf::Color(255, 165, 171) );
        Utils::FrameRate::centerText();

}

void Utils::FrameRate::UpdateState( sf::Time& dt ) {
    accTime += dt;
    frames++;

    // must be set on conf.json later on
    if (accTime.asSeconds() >= 0.8f ) { // 0.5 === delay time
        fps = static_cast<int>( frames / accTime.asSeconds() );

        // DBG
        // std::cout << fps << ", ";

        // txt.setString( "FPS [" + std::to_string( fps ) + ']' );
        txt.setString( std::to_string(fps) );

        Utils::FrameRate::centerText();

        accTime = sf::Time::Zero;
        frames = 0;
    }
}

void Utils::FrameRate::centerText() {
    // auto bounds = Utils::FrameRate::txt.getLocalBounds();
    // sf::Vector2f len = {bounds.width, bounds.height};
    // txt.setOrigin( len/2.f);
    // txt.setPosition(Utils::WIDTH/2.f, Utils::HEIGHT - 10.f);
    txt.setPosition( {10.f, 10.f} );
}

void Utils::FrameRate::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    target.draw( txt, states );
}