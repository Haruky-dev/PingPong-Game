#include <cache/SoundCache.hpp>

#include <engine/Loading.hpp>

#include <iostream>


SoundCache& SoundCache::getInst() {
    static SoundCache inst = SoundCache();

    return inst;
}

void SoundCache::Load( Progressive& prog ) {
    prog.addTotal( 50 );

    this->cache["padHit"] = sf::SoundBuffer("assets/sfx/padHit.wav");
    prog.incCount( 20 );
    this->cache["wallHit"] = sf::SoundBuffer("assets/sfx/wallHit.wav");
    prog.incCount( 20 );
}

const sf::SoundBuffer& SoundCache::get( const std::string& id ) const {
    if ( this->cache.find( id ) == this->cache.end() )
        throw std::runtime_error("Invalid given [ID] for 'SFX' look-up!");

    return this->cache.at( id );
}