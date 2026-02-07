#include <cache/TextureCache.hpp>

#include <engine/Loading.hpp>

#include <iostream>

TextureCache& TextureCache::getInst() {
    static TextureCache inst = TextureCache();
    
    return inst;
}


void TextureCache::Load( Progressive& prog ) {
    prog.addTotal( 210 ); // 1kb -> .5 units, ~400kb -> 200u

    //-- [MainMenu] State
    if (!(this->cache["mm/bg"] = std::make_unique<sf::Texture>( "assets/MMbg.jpg" )))         //-- general
        throw std::runtime_error("Cannot load [Texture] 'MainMenu/bg'!");

    prog.incCount( 120 );


    if (!(this->cache["mm/btn/play"] = std::make_unique<sf::Texture>( "assets/play.png" )))   //-- buttons
        throw std::runtime_error("Cannot load [Texture] 'MainMenu/Button/play'!");
    prog.incCount( 2 );

    if (!(this->cache["mm/btn/set"] = std::make_unique<sf::Texture>( "assets/setting.png" )))
        throw std::runtime_error("Cannot load [Texture] 'MainMenu/Button/Setting'!");
    prog.incCount( 2 );

    if (!(this->cache["mm/btn/q"] = std::make_unique<sf::Texture>( "assets/quit.png" )))
        throw std::runtime_error("Cannot load [Texture] 'MainMenu/Button/Quit'!");
    prog.incCount( 2 );

    //-- [Setting] State
    if (!(this->cache["set/bg"] = std::make_unique<sf::Texture>( "assets/menu.png" )))
        throw std::runtime_error("Cannot load [Texture] 'Setting/bg'!");
    prog.incCount( 19 );

    if (!(this->cache["set/shad"] = std::make_unique<sf::Texture>( "assets/shadow.png" )))
        throw std::runtime_error("Cannot load [Texture] 'Setting/Shadow'!");
    prog.incCount( 19 );

    //-- [Play] State
    if (!(this->cache["play/bg"] = std::make_unique<sf::Texture>( "assets/gameBg.png" )))     //-- general
        throw std::runtime_error("Cannot load [Texture] 'play/bg'!");
    prog.incCount( 35 );

    if (!(this->cache["play/pad"] = std::make_unique<sf::Texture>( "assets/paddle.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/pad'!");
    prog.incCount( 1 );

    if (!(this->cache["play/ball"] = std::make_unique<sf::Texture>( "assets/ball.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/ball'!");
    prog.incCount( 1 );

    if (!(this->cache["play/sc/0"] = std::make_unique<sf::Texture>( "assets/zero.png" )))     //-- scores
        throw std::runtime_error("Cannot load [Texture] 'play/score/0'!");
    prog.incCount( 1 );

    if (!(this->cache["play/sc/1"] = std::make_unique<sf::Texture>( "assets/one.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/score/1'!");
    prog.incCount( 1 );

    if (!(this->cache["play/sc/2"] = std::make_unique<sf::Texture>( "assets/two.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/score/2'!");
    prog.incCount( 1 );

    if (!(this->cache["play/sc/3"] = std::make_unique<sf::Texture>( "assets/three.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/score/3'!");
    prog.incCount( 1 );

    if (!(this->cache["play/sc/4"] = std::make_unique<sf::Texture>( "assets/four.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/score/4'!");
    prog.incCount( 1 );

    if (!(this->cache["play/sc/5"] = std::make_unique<sf::Texture>( "assets/five.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/score/5'!");
    prog.incCount( 1 );

    if (!(this->cache["play/cd/1"] = std::make_unique<sf::Texture>( "assets/cOne.png" )))     //-- countdown
        throw std::runtime_error("Cannot load [Texture] 'play/countD/1'!");
    prog.incCount( 1 );

    if (!(this->cache["play/cd/2"] = std::make_unique<sf::Texture>( "assets/cTwo.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/countD/2'!");
    prog.incCount( 1 );

    if (!(this->cache["play/cd/3"] = std::make_unique<sf::Texture>( "assets/cThree.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/countD/3'!");
    prog.incCount( 1 );
}

const sf::Texture& TextureCache::get( const std::string& id ) const {

    if ( this->cache.find( id ) == this->cache.end() )
        throw std::runtime_error("Invalid given [ID] for 'Texture' look-up!");

    return *( this->cache.at( id ) );
}