#include <cache/SoundCache.hpp>

#include <engine/Loading.hpp>

#include <iostream>


SoundCache& SoundCache::getInst() {
    static SoundCache inst = SoundCache();

    return inst;
}

void SoundCache::Load( Progressive& prog ) {
    prog.addTotal( 1300 ); // 1kb -> .5 units, ~2.6mb -> 1300u

    this->cache["padHit"] = sf::SoundBuffer("assets/sfx/padHit.wav");
    prog.incCount( 20 );
    this->cache["wallHit"] = sf::SoundBuffer("assets/sfx/wallHit.wav");
    prog.incCount( 20 );

    this->cache["playM"] = sf::SoundBuffer("assets/musics/Toejam_and_Earl.ogg");
    prog.incCount( 600 );
    this->cache["bgM"] = sf::SoundBuffer("assets/musics/Yoshis_Story-Games_of_Happiness.ogg");
    prog.incCount( 700 );
}

const sf::SoundBuffer& SoundCache::get( const std::string& id ) const {
    if ( this->cache.find( id ) == this->cache.end() )
        throw std::runtime_error("Invalid given [ID] for 'Sound' look-up!");

    return this->cache.at( id );
}