#include <engine/Play.hpp>

#include <SFML/Graphics.hpp>

#include <cache/visuals/PlayUI.hpp>

#include <cache/SoundCache.hpp>


Play::Play() : State() {}

Play::~Play() = default;

void Play::Load() {

    this->P1 = std::make_unique<Player>(
        PlayUI::getInst().get("pad"), 1
    );
    this->P2 = std::make_unique<Player>(
        PlayUI::getInst().get("pad"), 0
    );
    this->ball = std::make_unique<Ball>(
        PlayUI::getInst().get("ball")
    );
    
    ball->setPlayers( *P1, *P2 );

    this->F = std::make_unique<Utils::FrameRate>();

    this->music = std::make_unique<sf::Music>();
    if (!(this->music->openFromFile( "assets/musics/Toejam_and_Earl.ogg" )))
        throw std::runtime_error("Failure");
        
    this->music->setLooping( true );

    this->setRequest({
        { sf::Keyboard::Key::Escape, Action::raiseMain },
        { sf::Keyboard::Key::Space, Action::raisePause }
    });
}

void Play::Update( sf::Time& dt ) {
    if ( this->music->getStatus() != sf::Music::Status::Playing )
        this->music->play();
        
    P1->UpdateState( dt );
    P2->UpdateAI( dt, *ball );  
    ball->UpdateState( dt );
    F->UpdateState( dt );
}

void Play::Render( sf::RenderWindow& win ) const {
    win.draw( PlayUI::getInst().get("bg"));
    win.draw( *F );

    if (ball->cd != -1)
        win.draw(
            PlayUI::getInst().get("cd", ball->cd)
        );

    win.draw( PlayUI::getInst().get("sc1", Utils::P1_SCORE) );
    win.draw( PlayUI::getInst().get("sc2", Utils::P2_SCORE) );
    
    win.draw( *P1 );
    win.draw( *P2 );
    win.draw( *ball );
}

State::Type Play::getType() const { return State::Type::Play; }

void Play::exit() {
    this->music.reset();
}

void Play::pause() {
    this->music->setVolume( 10 );
}