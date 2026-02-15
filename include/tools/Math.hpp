#pragma once

#include <SFML/Graphics.hpp>
#include <tools/Tool.hpp>

class Math {
    public:
        static sf::Vector2f Normalize( const sf::Vector2f& A );
        static const double Dot( const sf::Vector2f& A, const sf::Vector2f& B );
        static void Reflect( sf::Vector2f& v, Tool::Sides side );
        static double Lerp( const double A, const double B, const double t );
        static sf::Vector2f Lerp( const sf::Vector2f& A, const sf::Vector2f& B, const double t );
        static double easeIn( const double x );
        static double easeOut( const double x );
        static double easeInOut( const double x );
};