#include "Assets.hpp"

#include "Utils.hpp"

#include <print>

// returns reff to the singleton instance
Assets& Assets::getInst() {
    static Assets inst = Assets();
    
    return inst;
}

// std::string Assets::FONT = "Resources/arialFont.ttf";
std::string Assets::BG  = "Resources/gameBg2.png";
std::string Assets::PAD = "Resources/paddle.png";
std::string Assets::BALL = "Resources/ball3.png";

std::string Assets::SCORE[6] = {
    "Resources/zero.png",
    "Resources/one.png",
    "Resources/two.png",
    "Resources/three.png",
    "Resources/four.png",
    "Resources/five.png"    
};

void Assets::loadResources() {
    // // load font
    // if (!font.loadFromFile(FONT))
    //     throw std::runtime_error("UNABLE TO LOAD [FONT]!");   

    // init pointers
    bgText    = std::make_unique<sf::Texture>();
    padText   = std::make_unique<sf::Texture>();
    ballText  = std::make_unique<sf::Texture>();

    bgSprite     = std::make_unique<sf::Sprite>();
    padSprite    = std::make_unique<sf::Sprite>();
    ballSprite   = std::make_unique<sf::Sprite>();
    scoreSprite  = std::make_unique<sf::Sprite>();
    scoreSprite1 = std::make_unique<sf::Sprite>();

    // load bg txt
    if ( !(bgText->loadFromFile(BG)) )
        throw std::runtime_error("UNABLE TO LOAD [BACKGROUND] TEXTURE!");

    // load paddle
    if ( !(padText->loadFromFile(PAD)) )
        throw std::runtime_error("UNABLE TO LOAD [PADDLE] TEXTURE!");

    // load ball txt
    if ( !(ballText->loadFromFile(BALL)) )
        throw std::runtime_error("UNABLE TO LOAD [BALL] TEXTURE!");


    for (int i = 0; i<6; ++i) {
        Assets::SCORE_TEXTS[i] = std::make_unique<sf::Texture>();
        if ( !(Assets::SCORE_TEXTS[i]->loadFromFile( Assets::SCORE[i] )) )
            throw std::runtime_error( "Cannot load Score Textures #" + std::to_string(i+1) );
    }

    Assets::scoreSprite->setTexture( *(Assets::SCORE_TEXTS[0]) );
    Assets::scoreSprite1->setTexture( *(Assets::SCORE_TEXTS[0]) );

    // set Sprites
    bgSprite->setTexture( *bgText );

    padSprite->setTexture( *padText );
    ballSprite->setTexture( *ballText );

    // p1 score sprite
    scoreSprite->setOrigin(
        scoreSprite->getTexture()->getSize().x / 2.0f,
        scoreSprite->getTexture()->getSize().y / 2.0f
    );
    scoreSprite->setPosition(
        300.0f, Utils::HEIGHT /2.0f
    );
    scoreSprite->setScale( 3.0f, 3.0f );

    // p2 score sprite
    scoreSprite1->setOrigin(
        scoreSprite1->getTexture()->getSize().x / 2.0f,
        scoreSprite1->getTexture()->getSize().y / 2.0f
    );
    scoreSprite1->setPosition(
        Utils::WIDTH - 300.0f, Utils::HEIGHT /2.0f
    );
    scoreSprite1->setScale( 3.0f, 3.0f );

}

sf::Sprite& Assets::getBg()  const  { return *bgSprite; }
sf::Sprite& Assets::getPad() const  { return *padSprite; }
sf::Sprite& Assets::getBall() const { return *ballSprite; }

sf::Sprite& Assets::getScore( const int id ) const {
    
    if (id == 1) {
        this->scoreSprite->setTexture( *(SCORE_TEXTS[Utils::P1_SCORE]) );
        return *scoreSprite;

    } else if (id == 2) {
        this->scoreSprite1->setTexture( *(SCORE_TEXTS[Utils::P2_SCORE]) );
        return *scoreSprite1;
    }

    throw std::runtime_error( "Invalid Player ID Given ");
}