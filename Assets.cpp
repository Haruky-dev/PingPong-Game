#include "Assets.hpp"

#include "Utils.hpp"

#include <print>

// returns pointer to the singleton instance
Assets& Assets::getInst() {
    static Assets inst = Assets();
    
    return inst;
}

// std::string Assets::FONT = "Resources/arialFont.ttf";
std::string Assets::BG  = "Resources/gameBg2.png";
std::string Assets::PAD = "Resources/paddle.png";
std::string Assets::BALL = "Resources/ball3.png";

std::string Assets::SCORE[6] = {
    "Resources/0.png",
    "Resources/1.png",
    "Resources/2.png",
    "Resources/3.png",
    "Resources/4.png",
    "Resources/5.png"    
};

// Assets::SCORE = std::make_unique<std::string[]>(6);

// for (int i = 0; i<6; ++i)
//     Assets::SCORE[i] = "Resources/" + std::to_string(i) + ".png";
// Assets::SCORE = {
//     "Resources/zero.png",
//     "Resources/one.png",
//     "Resources/two.png",
//     "Resources/three.png",
//     "Resources/four.png",
//     "Resources/five.png"
// };


void Assets::loadResources() {
    // // load font
    // if (!font.loadFromFile(FONT))
    //     throw std::runtime_error("UNABLE TO LOAD [FONT]!");   

    // init pointers
    bgText    = std::make_unique<sf::Texture>();
    padText   = std::make_unique<sf::Texture>();
    ballText  = std::make_unique<sf::Texture>();

    bgSprite    = std::make_unique<sf::Sprite>();
    padSprite   = std::make_unique<sf::Sprite>();
    ballSprite  = std::make_unique<sf::Sprite>();
    scoreSprite = std::make_unique<sf::Sprite>();
    scoreSprite1 = std::make_unique<sf::Sprite>();

    // load bg txt
    if ( !(bgText->loadFromFile(Assets::BG)) )
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
    // bgSprite->setOrigin( bgText->getSize().x/2.f, bgText->getSize().y/2.f);
    // bgSprite->setPosition( Utils::WIDTH/2.f, Utils::HEIGHT/2.f );

    padSprite->setTexture( *padText );
    ballSprite->setTexture( *ballText );


    // scoreSprite->setTexture( *scoreText );
    scoreSprite->setOrigin(
        scoreSprite->getTexture()->getSize().x / 2.0f,
        scoreSprite->getTexture()->getSize().y / 2.0f
    );
    scoreSprite->setPosition(
        300.0f, Utils::HEIGHT /2.0f
    );
    scoreSprite->setScale( 3.0f, 3.0f );

    // scoreSprite1->setTexture( *scoreText1 );
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
    // if (id == 1)
    //     return *(this->scoreSprite);
    // else
    //     return *(this->scoreSprite1);

    
    if (id == 1) {
            // this->scoreText->loadFromFile( Assets::SCORE[Utils::P1_SCORE] );
            this->scoreSprite->setTexture( *(SCORE_TEXTS[Utils::P1_SCORE]) );

        return *scoreSprite;
    } else if (id == 2) {
            // this->scoreText1->loadFromFile( Assets::SCORE[Utils::P2_SCORE] );
            this->scoreSprite1->setTexture( *(SCORE_TEXTS[Utils::P2_SCORE]) );

        return *scoreSprite1;
    }

    throw std::runtime_error( "Invalid Player ID Given ");
}


/* 

    func
        sf::Spr& getPlayerScoreSpr( id ) {
            if (id == 1)
                updateScoreText()
                return scoreSprite;

            else if (id == 2)
                updateScoreText1()
                return scoreSprite;
        }

    func
        void updateScoreText( id, score ) {
            if (id == 1) {
                scoreText->loadFromFile( Assets::SCORE[score] );
                scoreSprite->setTexture( scoreText );
            } else if (id == 2) {
                scoreText1->loadFromFile( Assets::SCORE[score] );
                scoreSprite1->setTexture( scoreText1 );
            }
        }
*/
// sf::Sprite& Assets::getScore( const int id ) const {
//     if (id == 1)
//         return *scoreSprite;
//     else
//         return *scoreSprite1;
// }

// sf::Sprite& Assets::setScore( const int id, const int score ) const {
//     if (id == 1) {
//         this->scoreText->loadFromFile( Assets::SCORE[score] );
//         this->scoreSprite->setTexture( this->scoreText );
//     } else if (id == 2) {
//         this->scoreText1->loadFromFile( Assets::SCORE[score] );
//         this->scoreSprite1->setTexture( this->scoreText1 );
//     }
// }