#include "Play.hpp"

#include <SFML/Graphics.hpp>
#include "../Assets.hpp"


Play::Play() : State() {}

Play::~Play() = default;

void Play::Load() {

    // Assets::getInst().loadResources();
    this->P1   = std::make_unique<Player>( Assets::getInst().getPad(), 1 );
    this->P2   = std::make_unique<Player>( Assets::getInst().getPad(), 0 );

    this->ball = std::make_unique<Ball>( Assets::getInst().getBall() );
    ball->setPlayers( *P1, *P2 );

    this->F    = std::make_unique<Utils::FrameRate>();
}

void Play::Update( sf::Time& dt ) {
    P1->UpdateState( dt );
    P2->UpdateAI( dt, *ball );
    ball->UpdateState( dt );
    F->UpdateState( dt );
}

void Play::Render( sf::RenderWindow& win ) const {
    win.draw( Assets::getInst().getBg() );
    win.draw( *F );

    if (ball->cd != -1)
        win.draw( Assets::getInst().getCD( ball->cd ));

    win.draw( Assets::getInst().getScore(1) );
    win.draw( Assets::getInst().getScore(2) );
    win.draw( *P1 );
    win.draw( *P2 );
    win.draw( *ball );
}

StateType Play::getType() const { return StateType::Play; }