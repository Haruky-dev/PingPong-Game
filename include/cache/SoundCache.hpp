#pragma once

#include <SFML/Audio.hpp>

#include <unordered_map>
#include <string>

class Progressive;


class SoundCache {
    private:
        SoundCache() = default;

        SoundCache( const SoundCache& ) = delete;
        SoundCache( SoundCache&& ) = delete;

        SoundCache& operator=( SoundCache& other ) = delete;
        SoundCache& operator=( SoundCache&& ) = delete;

  
        std::unordered_map<std::string, sf::SoundBuffer> cache;

    public:
        static SoundCache& getInst();

        void Load( Progressive& prog );

        const sf::SoundBuffer& get( const std::string& id ) const;
};