#include <tools/Math.hpp>

#include <math.h>

sf::Vector2f Math::Normalize( const sf::Vector2f& A ) {
    const double M = std::sqrt( (A.x * A.x  +   A.y * A.y) ); // Magnitude
    
    if (M <= 0.00f) return sf::Vector2f( 0.f, 0.f );

    sf::Vector2f UnitVect(A.x / M, A.y / M);

    return UnitVect;
}

const double Math::Dot( const sf::Vector2f& A, const sf::Vector2f& B ) {
    return static_cast<double>( A.x * B.x  +  A.y * B.y );
}

void Math::Reflect( sf::Vector2f& vect, Tool::Sides side ) {
    sf::Vector2f n = Math::Normalize(Tool::Norms.at(side));

    if (n.x == 0.f && n.y == 0.f) return;

    const double dotProd = Math::Dot( vect, n );
    vect.x = vect.x - 2.f * dotProd * n.x;
    vect.y = vect.y - 2.f * dotProd * n.y;
}

double Math::Lerp( const double A, const double B, const double t ) {
    return ( A + (B - A) * t );
}

sf::Vector2f Math::Lerp( const sf::Vector2f& A, const sf::Vector2f& B, const double t ) {
    return sf::Vector2f(
        A.x + (B.x - A.x) * t,
        A.y + (B.y - A.y) * t
    );
}

double Math::easeIn( const double x ) {
    return x * x * x;
}
double Math::easeOut( const double x ) {
    return 1 - (1-x)*(1-x)*(1-x);
}
double Math::easeInOut( const double x ) {
    return (x < 0.5f)? 4.f * x * x * x :
        1 - ( (-2.f * x + 2)*(-2.f * x + 2)*(-2.f * x + 2) ) /2.f;
}