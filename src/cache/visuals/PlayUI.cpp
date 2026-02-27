#include <cache/visuals/PlayUI.hpp>

#include <cache/TextureCache.hpp>
#include <cassert>
#include <tools/Tool.hpp>

#include <iostream>

PlayUI& PlayUI::getInst() {
    static PlayUI inst = PlayUI();

    return inst;
}

void PlayUI::Load( Progressive& prog ) {
    prog.addTotal( 10 );

    TextureCache& txtCache = TextureCache::getInst();

    sf::Sprite bgSpr( txtCache.get("play/bg") );
    this->bg = std::make_optional<sf::Sprite>( bgSpr );
    sf::Sprite padSpr( txtCache.get("play/pad") );
    this->pad = std::make_optional<sf::Sprite>( padSpr );
    sf::Sprite ballSpr( txtCache.get("play/ball") );
    this->ball = std::make_optional<sf::Sprite>( ballSpr );

    sf::Sprite cdSpr( txtCache.get("play/cd/3") );
    this->countD = std::make_optional<sf::Sprite>( cdSpr );

    sf::Sprite sc1Spr( txtCache.get("play/sc/0") );
    this->score_1 = std::make_optional<sf::Sprite>( sc1Spr );
    sf::Sprite sc2Spr( txtCache.get("play/sc/0") );
    this->score_2 =  std::make_optional<sf::Sprite>( sc2Spr );

    prog.incCount( 6 );

    // score sprites conf
    this->score_1->setOrigin(
        sf::Vector2f(this->score_1->getTexture().getSize()) / 2.f
    );
    this->score_1->setPosition( {300.0f, Tool::HEIGHT /2.0f} );
    this->score_1->setScale( {3.0f, 3.0f} );   

    this->score_2->setOrigin(
        sf::Vector2f(this->score_2->getTexture().getSize()) / 2.f
    );
    this->score_2->setPosition( {Tool::WIDTH - 300.0f, Tool::HEIGHT / 2.0f} );
    this->score_2->setScale( {3.0f, 3.0f} );   

    // countdown sprite conf
    this->countD->setOrigin(
        sf::Vector2f( this->countD->getTexture().getSize()) / 2.f
    );
    this->countD->setPosition({
        Tool::WIDTH /2.0f, 75.0f
    });

    this->countD->setScale( {4.f, 4.f} );

    prog.incCount( 4 );
}

const sf::Sprite& PlayUI::get( const std::string& id, int i ) {
    if ( id == "bg" ) {
        assert( this->bg.has_value() );

        return this->bg.value();
    }
    
    else if ( id == "pad" ) {
        assert( this->pad.has_value() );

        return this->pad.value();
    }

    else if ( id == "ball" ) {
        assert( this->ball.has_value() );

        return this->ball.value();
    }

    else if ( id == "cd" ) {
        if ( i < 3 && i >= 0 )
            this->countD->setTexture(
                TextureCache::getInst().get( "play/cd/" + std::to_string(3-i) )
            );

        assert( this->countD.has_value() );

        return this->countD.value();
    }

    else if ( id == "sc1" ) {
        if ( i < 6 && i >= 0 )
            this->score_1->setTexture(
                TextureCache::getInst().get( "play/sc/" + std::to_string(i) )
            );

        assert( this->score_1.has_value() );

        return this->score_1.value();
    }

    else if ( id == "sc2" ) {
        if ( i < 6 && i >= 0 )
            this->score_2->setTexture(
                TextureCache::getInst().get( "play/sc/" + std::to_string(i) )
            );
        assert( this->score_2.has_value() );

        return this->score_2.value();
    }

    throw std::runtime_error("Invalid given [ID] for [Sprite] look-up!");
}