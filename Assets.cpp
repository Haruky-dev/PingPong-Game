#include "Assets.hpp"

Assets& Assets::getInstance() {
    static Assets inst;
    return inst;
}

// std::string Assets::FONT = "Resources/arialFont.ttf";
std::string Assets::BG   = "Resources/gameBg.png";
// std::string Assets::BALL = "Resources/ball2.png";

void Assets::loadResources() {
    // // load font
    // if (!font.loadFromFile(FONT))
    //     throw std::runtime_error("UNABLE TO LOAD [FONT]!");   

    // init pointers
    bgText = std::make_unique<sf::Texture>();
    // padText = std::make_unique<sf::Texture>();
    // ballText = std::make_unique<sf::Texture>();

    bgSprite = std::make_unique<sf::Sprite>();
    // // padSprite = std::make_unique<sf::Sprite>();
    // ballSprite = std::make_unique<sf::Sprite>();
    

    // load bg txt
    if ( !(bgText->loadFromFile(Assets::BG)) )
        throw std::runtime_error("UNABLE TO LOAD [BACKGROUND] TEXTURE!");

    // // load paddle
    // if ( !(padText->loadFromFile(PAD)) )
    //     throw std::runtime_error("UNABLE TO LOAD [PADDLE] TEXTURE!");

    // load ball txt
    // if ( !(ballText->loadFromFile(BALL)) )
    //     throw std::runtime_error("UNABLE TO LOAD [BALL] TEXTURE!");

    // // set Sprites
    // bgSprite->setTexture( *bgText );
    // // padSprite->setTexture( *padText );
    // ballSprite->setTexture( *ballText );

    // ballSprite->setPosition( 200.0f, 200.0f );
    // ballSprite->setScale( 1.5f, 1.5f );
}

sf::Sprite& Assets::getBg()  const  { return *bgSprite; }
// sf::Sprite& Assets::getPad() const  { return *padSprite; }
// sf::Sprite& Assets::getBall() const { return *ballSprite; }