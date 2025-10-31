#include "Utils.hpp"

#include <math.h>

#include <iostream>

#include "Player.hpp"
#include "Ball.hpp"

int Utils::WIDTH = 720;
int Utils::HEIGHT = 480;

int Utils::P1_SCORE = 0;
int Utils::P2_SCORE = 0;

bool Utils::changeScore = 0;

double Utils::EPSILON = 1e-16;


// void Utils::incScore( int& PlayerScore ) {
//     if (PlayerScore > 6)
//         // game over situation
//         // std::println( "INVALID SCORE VALUE REACHED, GAME OVER!" );
//         throw std::runtime_error(" Score Reached Invalid Value! ");
        
//     else if (PlayerScore >= 0)
//         throw std::runtime_error(" Score Reached Invalid [NEGATIVE] Value! ");
 
//     // valid val => inc
//     PlayerScore++;
// }

std::map<Utils::Sides, sf::Vector2f> Utils::Norms = {
    {Utils::Sides::TOP, {0.f, -1.f}},
    {Utils::Sides::BOTTOM, {0.f, 1.f}},
    {Utils::Sides::LEFT, {-1.f, 0.f}},
    {Utils::Sides::RIGHT, {1.f, 0.f}},
};

sf::Vector2f Utils::Normalize( const sf::Vector2f& vect ) {
    const double M = std::sqrt( (vect.x * vect.x  +   vect.y * vect.y) ); // Magnitude

    if (M <= Utils::EPSILON) return sf::Vector2f( 0.f, 0.f );

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

bool Utils::checkWallColl( Ball& ball, Utils::Sides& side ) {
    sf::FloatRect pos = ball.getBounds();

    if (pos.top <= 12.f) { // 12px of the background edge
        side = Utils::Sides::TOP;
        return true;
    } else if ((pos.top + pos.height) >= Utils::HEIGHT - 12.0f) {
        side = Utils::Sides::BOTTOM;
        return true;
    } 

    // goal case
    if ( pos.left <= 0 ) {
            changeScore = true;
        ball.ResetPos();

        if (Utils::P2_SCORE > 5)
            throw std::runtime_error("Game Over. Invalid Value Reached");
        
        Utils::P2_SCORE++;
    }
    else if ((pos.left + pos.width) >= Utils::WIDTH) {
        changeScore = true;
        ball.ResetPos();

        if (Utils::P1_SCORE > 5)
            throw std::runtime_error("Game Over. Invalid Value Reached" );
    
        Utils::P1_SCORE++;
    }
    
    changeScore = false;

    // else if ((pos.left <= 0) || ((pos.left + pos.width) >= Utils::WIDTH)) {
    //     ball.ResetPos();
    // }

    return false;
}

bool Utils::checkPlayColl( const Player& p1, const Player& p2, Ball& ball, Utils::Sides& side ) {
    if (! (&p1 && &p2))
        throw std::runtime_error("Error Occured! Insufficient number of Player.");

    if (p1.getBounds().intersects(ball.getBounds())) {
        side = Utils::Sides::RIGHT;
        return true;
    }

    else if (p2.getBounds().intersects(ball.getBounds())) {
        side = Utils::Sides::LEFT;
        return true;
    }

    return false;
}

Utils::FrameRate::FrameRate()
    : accTime(sf::Time::Zero), frames(0), fps(0) {

        if (!font.loadFromFile("Resources/arialFont.ttf"))
            throw std::runtime_error("Unable to load Font");

        txt.setFont(font);
        txt.setString( " FPS: [] " );
        txt.setScale( 0.4f, 0.4f );
        // txt.setFillColor( sf::Color::Green);
        txt.setFillColor( sf::Color(255, 165, 171) );
        Utils::FrameRate::centerText();

}

void Utils::FrameRate::UpdateState( sf::Time& dt ) {
    accTime += dt;
    frames++;

    if (accTime.asSeconds() >= 0.5f ) { // 0.5 === delay time
        fps = static_cast<int>( frames / accTime.asSeconds() );

        // DBG
        // std::cout << fps << ", ";

        txt.setString( "FPS [" + std::to_string( fps ) + ']' );
        Utils::FrameRate::centerText();

        accTime = sf::Time::Zero;
        frames = 0;
    }
}

void Utils::FrameRate::centerText() {
    auto bounds = Utils::FrameRate::txt.getLocalBounds();
    sf::Vector2f len = {bounds.width, bounds.height};
    txt.setOrigin( len/2.f);
    txt.setPosition(Utils::WIDTH/2.f, Utils::HEIGHT - 10.f);
}

void Utils::FrameRate::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    target.draw( txt, states );
}