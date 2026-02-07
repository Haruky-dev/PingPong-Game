#include <cache/visuals/MenuUI.hpp>

#include <cache/TextureCache.hpp>
#include <engine/StateType.hpp>
#include <iostream>

MenuUI& MenuUI::getInst() {
    static MenuUI inst = MenuUI();

    return inst;
}

void MenuUI::Load( Progressive& prog ) {
    prog.addTotal( 6 );

    TextureCache& txtCache = TextureCache::getInst();

    // load bg1
    sf::Sprite bgSpr( txtCache.get("mm/bg") );
    this->bg = std::make_optional<sf::Sprite>( bgSpr );    

    for (int i{}; i < BTN_COUNT; i++) {
        std::string id;
        switch(i) {
            case 0: id = "mm/btn/play"; break;
            case 1: id = "mm/btn/set"; break;
            case 2: id = "mm/btn/q"; break;

            default:
                throw std::runtime_error("Invalid button index");
        }

        sf::Sprite btnSpr( txtCache.get(id) );
        this->btns[i] = std::make_optional<sf::Sprite>( btnSpr );

        this->btns[i]->setPosition({40.0f, 80.f*(i+1) + 10});
            // 100*(i+1): order in the Y axis.  +i*10   : 10px offset   
        this->btns[i]->setScale({1.5f, 1.5f});

        this->btnProp[i].second = Utils::getBound( this->btns[i].value() );
    }

    this->btnProp[0].first = StateType::Play;
    this->btnProp[1].first = StateType::Setting;
    this->btnProp[2].first = StateType::Quit;

    prog.incCount( 6 );
}

const sf::Sprite& MenuUI::get( const std::string& id, const int i ) const {
    if ( id == "bg" ) {
        if ( !this->bg.has_value())
            throw std::runtime_error("[MenuUI] Background sprite not loaded yet!");

        return this->bg.value();
    }

    else if ( id == "btn" ) {
        if ( i < 0 || i >= BTN_COUNT )
            throw std::runtime_error("[MenuUI] Invalid button index requested!");

        if ( !this->btns[i].has_value())
            throw std::runtime_error("[MenuUI] Button sprite not loaded yet!");

        return this->btns[i].value();
    }

    throw std::runtime_error("Invalid given [ID] for [Sprite] look-up!");
}

StateType MenuUI::btnLabel( const int id ) const {
    if ( id < 0 || id >= BTN_COUNT )
        throw std::runtime_error("Invalid given [ID] for 'Label' look-up.");

    return this->btnProp.at(id).first;
}

sf::IntRect MenuUI::btnBound( const int id ) const {
    if ( id < 0 || id >= BTN_COUNT )
        throw std::runtime_error("Invalid given [ID] for 'Button' look-up.");

    return this->btnProp.at( id ).second;
}