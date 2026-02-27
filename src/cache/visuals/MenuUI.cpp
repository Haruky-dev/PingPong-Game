#include <cache/visuals/MenuUI.hpp>

#include <cache/TextureCache.hpp>
#include <cassert>
#include <tools/Tool.hpp>

#include <SFML/Graphics.hpp>

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

        this->btns[i]->setOrigin( sf::Vector2f(this->btns[i]->getTexture().getSize()) / 2.f );
        this->btns[i]->setPosition({ Tool::W_CTR.x, Tool::W_CTR.y - 90.f * (1-i) });
        this->btns[i]->setScale( {2.f, 2.f} );

        this->b_bounds[i] = Tool::getBound( this->btns[i].value() );
    }

    prog.incCount( 6 );
}

const sf::Sprite& MenuUI::get( const std::string& id, const int i ) const {
    if ( !(id.compare("bg")) ) {
        assert( this->bg.has_value() );

        return this->bg.value();
    }

    else if ( !(id.compare("btn")) ) {
        assert( i >= 0 && i < BTN_COUNT );
        assert( this->btns[i].has_value() );

        return this->btns[i].value();
    }

    throw std::runtime_error("Invalid given [ID] for [Sprite] look-up!");
}

const sf::Rect<int>& MenuUI::btnBound( const int id ) const {
    assert( id >= 0 && id < BTN_COUNT );
    
    return this->b_bounds[id];
}