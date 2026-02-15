#include <cache/visuals/SettingUI.hpp>

#include <cache/TextureCache.hpp>
#include <tools/Tool.hpp>

#include <iostream>

SettingUI& SettingUI::getInst() {
    static SettingUI inst = SettingUI();

    return inst;
}

void SettingUI::Load( Progressive& prog ) {
    prog.addTotal( 5 );

    TextureCache& txtCache = TextureCache::getInst();

    // load bg
    sf::Sprite bgSpr( txtCache.get("set/bg") );
    this->bg = std::make_optional<sf::Sprite>( bgSpr );    
    sf::Sprite shadSpr( txtCache.get("set/shad") );
    this->shad = std::make_optional<sf::Sprite>( shadSpr );

    this->bg->setOrigin(
        sf::Vector2f(this->bg->getTexture().getSize()) / 2.f
    );

    this->bg->setPosition({
        Tool::W_CTR.x,
        Tool::HEIGHT + (bg->getTexture().getSize().y / 2.f)
    });

    this->shad->setOrigin(
        sf::Vector2f(this->shad->getTexture().getSize()) / 2.f
    );
    this->shad->setPosition( Tool::W_CTR );
    
    prog.incCount( 5 );
}

const sf::Sprite& SettingUI::get( const std::string& id, const int i ) const {
    if ( id == "bg" ) {
        if ( !this->bg.has_value())
            throw std::runtime_error("[SettingUI] Background sprite not loaded yet!");

        return this->bg.value();
    }

    else if ( id == "shad" ) {
        if ( !this->shad.has_value())
            throw std::runtime_error("[SettingUI] Shadow sprite not loaded yet!");

        return this->shad.value();
    }

    throw std::runtime_error("Invalid given [ID] for [Sprite] look-up!");
}