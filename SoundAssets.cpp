#include "SoundAssets.hpp"

#include "StateMachine/Loading.hpp"

using Sound = SoundAssets;


Sound& Sound::getInst() {
    static Sound inst = Sound();

    return inst;
}

void Sound::Load( Progressive& prog ) {
    prog.addTotal( 30 );

    Sound::paddHitBuff.loadFromFile("Resources/sfx/paddHit.wav");
    prog.incCount( 2 );
    Sound::wallHitBuff.loadFromFile("Resources/sfx/wallHit.wav");
    prog.incCount( 2 );
    Sound::music_0.loadFromFile("Resources/musics/Toejam_and_Earl.ogg");
    prog.incCount( 4 );
    Sound::music_1.loadFromFile("Resources/musics/Donkey_Kong_64.ogg");
    prog.incCount( 4 );
    Sound::playMusic_0.loadFromFile("Resources/musics/Yoshis_Story-Games_of_Happiness.ogg");
    prog.incCount( 4 );
    Sound::playMusic_1.loadFromFile("Resources/musics/Toejam_and_Earl.ogg");
    prog.incCount( 4 );

    Sound::sfx[0].setBuffer( Sound::paddHitBuff );
    Sound::sfx[1].setBuffer( Sound::wallHitBuff );

    Sound::music[0].setBuffer( Sound::music_0 );
    Sound::music[1].setBuffer( Sound::music_1 );
    Sound::music[2].setBuffer( Sound::playMusic_0 );
    Sound::music[3].setBuffer( Sound::playMusic_1 );

    prog.incCount( 5 );
}

sf::Sound& Sound::paddHit() {
    // Sound::s[0].setBuffer( Sound::paddHitBuff );
    return Sound::sfx[0];
}

sf::Sound& Sound::wallHit() {
    // Sound::s[1].setBuffer( Sound::wallHitBuff );
    return Sound::sfx[1];
}

sf::Sound& Sound::getMusic( const int id ) {
    if ( id < 0 || id > 4 )
        throw std::runtime_error("Given [ID] for [getMusic] Is inValid");

    return Sound::music[ id ];
}