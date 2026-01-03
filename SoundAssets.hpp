// "Helper" for Assets class

#pragma once

#include <SFML/Audio.hpp>
    
#include <memory>

class Progressive;


class SoundAssets {
    private:
        SoundAssets() = default;
        SoundAssets& operator=( SoundAssets& other ) = delete;

  
        // Unique Buffers
        sf::SoundBuffer paddHitBuff;
        sf::SoundBuffer wallHitBuff;
        sf::SoundBuffer music_0;
        sf::SoundBuffer music_1;
        sf::SoundBuffer playMusic_0;
        sf::SoundBuffer playMusic_1;

        // Buffer managers
        sf::Sound sfx[3];
        sf::Sound music[4];

    public:
        static SoundAssets& getInst();

        void Load( Progressive& prog );
        sf::Sound& paddHit();
        sf::Sound& wallHit();
        sf::Sound& getMusic( const int id );
};