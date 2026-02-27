#include <cache/TextureCache.hpp>

#include <engine/states/Loading.hpp>


TextureCache& TextureCache::getInst() {
    static TextureCache inst = TextureCache();
    
    // This func
    return inst;
}


void TextureCache::Load( Progressive& prog ) {
    prog.addTotal( 210 ); // 1kb -> .5 units, ~400kb -> 200u

    //-- [MainMenu] State
    this->cache["mm/bg"] = std::make_unique<sf::Texture>();
    if (!(this->cache["mm/bg"]->loadFromFile("assets/MMbg.jpg")))
        throw std::runtime_error("Cannot load [Texture] 'MainMenu/bg'!");
    prog.incCount( 120 );

    this->cache["mm/btn/play"] = std::make_unique<sf::Texture>();
    if (!(this->cache["mm/btn/play"]->loadFromFile( "assets/play.png" )))   //-- buttons
        throw std::runtime_error("Cannot load [Texture] 'MainMenu/Button/play'!");
    prog.incCount( 2 );

    this->cache["mm/btn/set"] = std::make_unique<sf::Texture>();
    if (!(this->cache["mm/btn/set"]->loadFromFile( "assets/set.png" )))
        throw std::runtime_error("Cannot load [Texture] 'MainMenu/Button/Setting'!");
    prog.incCount( 2 );

    this->cache["mm/btn/q"] = std::make_unique<sf::Texture>();
    if (!(this->cache["mm/btn/q"]->loadFromFile( "assets/quit.png" )))
        throw std::runtime_error("Cannot load [Texture] 'MainMenu/Button/Quit'!");
    prog.incCount( 2 );

    //= [Setting] State
    this->cache["set/bg"] = std::make_unique<sf::Texture>();
    if (!(this->cache["set/bg"]->loadFromFile( "assets/menu.png" )))
        throw std::runtime_error("Cannot load [Texture] 'Setting/bg'!");
    prog.incCount( 19 );

    this->cache["set/shad"] = std::make_unique<sf::Texture>();
    if (!(this->cache["set/shad"]->loadFromFile( "assets/shadow.png" )))
        throw std::runtime_error("Cannot load [Texture] 'Setting/Shadow'!");
    prog.incCount( 19 );

    //= [Play] State
    this->cache["play/bg"] = std::make_unique<sf::Texture>();
    if (!(this->cache["play/bg"]->loadFromFile( "assets/gameBg.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/bg'!");
    prog.incCount( 35 );

    this->cache["play/pad"] = std::make_unique<sf::Texture>();
    if (!(this->cache["play/pad"]->loadFromFile( "assets/paddle.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/pad'!");
    prog.incCount( 1 );

    this->cache["play/ball"] = std::make_unique<sf::Texture>();
    if (!(this->cache["play/ball"]->loadFromFile( "assets/ball.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/ball'!");
    prog.incCount( 1 );

    this->cache["play/sc/0"] = std::make_unique<sf::Texture>();
    if (!(this->cache["play/sc/0"]->loadFromFile( "assets/zero.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/score/0'!");
    prog.incCount( 1 );

    this->cache["play/sc/1"] = std::make_unique<sf::Texture>();
    if (!(this->cache["play/sc/1"]->loadFromFile( "assets/one.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/score/1'!");
    prog.incCount( 1 );

    this->cache["play/sc/2"] = std::make_unique<sf::Texture>();
    if (!(this->cache["play/sc/2"]->loadFromFile( "assets/two.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/score/2'!");
    prog.incCount( 1 );

    this->cache["play/sc/3"] = std::make_unique<sf::Texture>();
    if (!(this->cache["play/sc/3"]->loadFromFile( "assets/three.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/score/3'!");
    prog.incCount( 1 );

    this->cache["play/sc/4"] = std::make_unique<sf::Texture>();
    if (!(this->cache["play/sc/4"]->loadFromFile( "assets/four.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/score/4'!");
    prog.incCount( 1 );

    this->cache["play/sc/5"] = std::make_unique<sf::Texture>();
    if (!(this->cache["play/sc/5"]->loadFromFile( "assets/five.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/score/5'!");
    prog.incCount( 1 );

    this->cache["play/cd/1"] = std::make_unique<sf::Texture>();
    if (!(this->cache["play/cd/1"]->loadFromFile( "assets/cOne.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/countD/1'!");
    prog.incCount( 1 );

    this->cache["play/cd/2"] = std::make_unique<sf::Texture>();
    if (!(this->cache["play/cd/2"]->loadFromFile( "assets/cTwo.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/countD/2'!");
    prog.incCount( 1 );

    this->cache["play/cd/3"] = std::make_unique<sf::Texture>();
    if (!(this->cache["play/cd/3"]->loadFromFile( "assets/cThree.png" )))
        throw std::runtime_error("Cannot load [Texture] 'play/countD/3'!");
    prog.incCount( 1 );
}

const sf::Texture& TextureCache::get( const std::string& id ) const {

    if ( this->cache.find( id ) == this->cache.end() )
        throw std::runtime_error("Invalid given [ID] for 'Texture' look-up!");

    return *( this->cache.at( id ) );
}