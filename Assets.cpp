#include "Assets.hpp"

#include "Utils.hpp"
#include "StateMachine/Loading.hpp"

// returns reff to the singleton instance
Assets& Assets::getInst() {
    static Assets inst = Assets();
    
    return inst;
}

std::unordered_map<int, StateType> Assets::buttonLabels = {
    {0, StateType::Play}, // 'Play' in MainMenu
    {1, StateType::Setting}, // 'Menu' (Setting) in MainMenu
    {2, StateType::Quit}, // 'Quit' in MainMenu
};

// std::string Assets::FONT = "Resources/arialFont.ttf";
std::string Assets::BG        = "Resources/gameBg2.png";
std::string Assets::PAD       = "Resources/paddle.png";
std::string Assets::BALL      = "Resources/ball3.png";
std::string Assets::MAIN_MENU = "Resources/MMbg1.jpg";
std::string Assets::SETT      = "Resources/menu.png";
std::string Assets::SHAD      = "Resources/shadow.png";

std::string Assets::SCORE[6] = {
    "Resources/zero.png",
    "Resources/one.png",
    "Resources/two.png",
    "Resources/three.png",
    "Resources/four.png",
    "Resources/five.png"    
};

std::string Assets::CD[3] = {
    "Resources/cThree.png",
    "Resources/cTwo.png",
    "Resources/cOne.png"
};

std::string Assets::MM_BTNS[6] = {
    "Resources/play.png",
    "Resources/setting.png",
    "Resources/quit.png",
    "Resources/play1.png",
    "Resources/setting1.png",
    "Resources/quit1.png"
};

void Assets::Load( Progressive& prog ) {

    prog.addTotal( 60 );

    // load font
    // if (!font.loadFromFile(FONT))
    //     throw std::runtime_error("UNABLE TO LOAD [FONT]!");   

    // init pointers
        // [PLAY] State
    bgText    = std::make_unique<sf::Texture>();
    padText   = std::make_unique<sf::Texture>();
    ballText  = std::make_unique<sf::Texture>();
    bgSprite     = std::make_unique<sf::Sprite>();
    padSprite    = std::make_unique<sf::Sprite>();
    ballSprite   = std::make_unique<sf::Sprite>();
    scoreSprite  = std::make_unique<sf::Sprite>();
    scoreSprite1 = std::make_unique<sf::Sprite>();
    countDSprite = std::make_unique<sf::Sprite>();

        // [MAINMENU] State
    MainMenuTxt = std::make_unique<sf::Texture>();
    MainMenuSpr = std::make_unique<sf::Sprite>();
    for (int i = 0; i<3; i++) {
        Assets::BTN_TXT[i]   = std::make_unique<sf::Texture>();
        Assets::BTN_TXT[i+3] = std::make_unique<sf::Texture>();
        Assets::BTN_SPR[i]   = std::make_unique<sf::Sprite>(); // normal

        Assets::BTN_SPR[i]->setPosition( 40.0f, 80*(i+1) + 10);
        Assets::BTN_SPR[i]->setScale( 1.5f, 1.5f );
            // 100*(i+1): order in the Y axis
            // + i*10   : 10px offset   

        if ((!(Assets::BTN_TXT[i]->loadFromFile(Assets::MM_BTNS[i])))
            || (!(Assets::BTN_TXT[i+3]->loadFromFile(Assets::MM_BTNS[i+3]))))
                throw std::runtime_error("UNABLE TO LOAD [BUTTON]s TEXTUREs!");

        prog.incCount( 6 );
    }

        // [SETTING] State
    SettTxt = std::make_unique<sf::Texture>();
    SettSpr = std::make_unique<sf::Sprite>();
    if ( !(Assets::SettTxt->loadFromFile( SETT )))
        throw std::runtime_error("UNABLE TO LOAD [SETTING] TEXTURE!");
    
    prog.incCount( 3 );

    ShadTxt = std::make_unique<sf::Texture>();
    ShadSpr = std::make_unique<sf::Sprite>();
    if ( !(Assets::ShadTxt->loadFromFile( Assets::SHAD )))
        throw std::runtime_error("UNABLE TO LOAD [SHADOW] TEXTURE!");

    prog.incCount( 3 );

    // load bg txt
    if ( !(bgText->loadFromFile(BG)) )
        throw std::runtime_error("UNABLE TO LOAD [BACKGROUND] TEXTURE!");

    prog.incCount( 3 );

    // load paddle
    if ( !(padText->loadFromFile(PAD)) )
        throw std::runtime_error("UNABLE TO LOAD [PADDLE] TEXTURE!");

    prog.incCount( 3 );

    // load ball txt
    if ( !(ballText->loadFromFile(BALL)) )
        throw std::runtime_error("UNABLE TO LOAD [BALL] TEXTURE!");

    prog.incCount( 3 );

    for (int i = 0; i<6; ++i) {
        Assets::SCORE_TEXTS[i] = std::make_unique<sf::Texture>();
        if ( !(Assets::SCORE_TEXTS[i]->loadFromFile( Assets::SCORE[i] )) )
            throw std::runtime_error( "Cannot load Score Textures #" + std::to_string(i+1) );

        prog.incCount( 3 );
    }

    for (int i = 0; i<3; ++i) {
        Assets::CD_TEXTS[i] = std::make_unique<sf::Texture>();
        if ( !(Assets::CD_TEXTS[i]->loadFromFile( Assets::CD[i] )) )
            throw std::runtime_error( "Cannot load Score Textures #" + std::to_string(i+1) );

        prog.incCount( 3 );
    }

    // load main menu txt
    if ( !(Assets::MainMenuTxt->loadFromFile( MAIN_MENU )) )
        throw std::runtime_error( "Cannot load [MAIN_MENU] TEXTURE!" );

    prog.incCount( 3 );

    Assets::scoreSprite->setTexture( *(Assets::SCORE_TEXTS[0]) );
    Assets::scoreSprite1->setTexture( *(Assets::SCORE_TEXTS[0]) );

    Assets::countDSprite->setTexture( *(Assets::CD_TEXTS[2]) );

    // set Sprites
    bgSprite->setTexture( *bgText );

    padSprite->setTexture( *padText );
    ballSprite->setTexture( *ballText );

    // conf p1 score sprite
    scoreSprite->setOrigin(
        scoreSprite->getTexture()->getSize().x / 2.0f,
        scoreSprite->getTexture()->getSize().y / 2.0f
    );
    scoreSprite->setPosition(
        300.0f, Utils::HEIGHT /2.0f
    );
    scoreSprite->setScale( 3.0f, 3.0f );

    // conf p2 score sprite
    scoreSprite1->setOrigin(
        scoreSprite1->getTexture()->getSize().x / 2.0f,
        scoreSprite1->getTexture()->getSize().y / 2.0f
    );
    scoreSprite1->setPosition(
        Utils::WIDTH - 300.0f,
        Utils::HEIGHT / 2.0f
    );
    scoreSprite1->setScale( 3.0f, 3.0f );

    // conf Countdown Sprite
    countDSprite->setOrigin(
        countDSprite->getTexture()->getSize().x / 2.0f,
        countDSprite->getTexture()->getSize().y / 2.0f
    );
    countDSprite->setPosition(
        Utils::WIDTH /2.0f, 75.0f
    );

    countDSprite->setScale( 4.f, 4.f );

    // [MainMenu] conf
    MainMenuSpr->setTexture( *MainMenuTxt );
    // this->

    // [SETTING] conf
    SettSpr->setTexture( *SettTxt );
    SettSpr->setOrigin( SettTxt->getSize().x/2.0f, SettTxt->getSize().y/2.0f );
    SettSpr->setPosition( Utils::W_CTR );

    ShadSpr->setTexture( *ShadTxt );
    ShadSpr->setOrigin( ShadTxt->getSize().x/2.0f, ShadTxt->getSize().y/2.0f );
    ShadSpr->setPosition( Utils::W_CTR );

    // configuring textures surely takes some work lol
    prog.incCount( 10 );
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
    
    throw std::runtime_error( "Invalid Player ID Given" );
}

sf::Sprite& Assets::getCD( const int n ) const {
    this->countDSprite->setTexture( *(CD_TEXTS[n]) );
    return *countDSprite;
}

sf::Sprite& Assets::getMainBg() const { return *MainMenuSpr; }

sf::Sprite& Assets::getMMBtn( const int id, bool hover ) const {
    // id: 1-3 play-set-quit respectivelly
    // if (hover) return BTN_SPR[i+3]
    if ( id < 0 || id > 3)
        throw std::runtime_error("Invalid ID given in func 'Assets::getMMBtn'.");

    Assets::BTN_SPR[ id ]->setTexture( *(Assets::BTN_TXT[ id + (3*hover) ]) );

    return *( Assets::BTN_SPR[ id ] );
}

sf::Rect<int> Assets::getButtonBound( const int id ) const {
    if ( id < 0 || id > 3 )
        throw std::runtime_error("Invalid ID given in func 'Assets::getMMBtnBound'.");

    sf::Sprite* btnPtr = Assets::BTN_SPR[ id ].get();

    return sf::Rect<int>(
        static_cast<int>( btnPtr->getPosition().x ),
        static_cast<int>( btnPtr->getPosition().y ),
        static_cast<int>( btnPtr->getGlobalBounds().width ),
        static_cast<int>( btnPtr->getGlobalBounds().height )
    );
}

StateType Assets::getButtonLabel( const int id ) const {
    return Assets::buttonLabels.at( id );
}

sf::Sprite& Assets::getSettingMenu() const { return *(Assets::SettSpr); }

sf::Sprite& Assets::getShadow() const { return *ShadSpr; }

// func setMMBtnHover