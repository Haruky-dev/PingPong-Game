#include <algorithm>
#include <engine/states/Setting.hpp>

#include <cstdint>

#include <tools/Tool.hpp>
#include <tools/Math.hpp>
#include <cache/visuals/SettingUI.hpp>


Setting::Setting() : State(), Animated(), bg(SettingUI::getInst().get("bg")),
    shad(SettingUI::getInst().get("shad")), shadClr(shad.getColor()),
    t(0.0f), elapsed(0.0f), duration(1.f), direc(1),
    initPos(Tool::HEIGHT + bg.getTexture().getSize().y / 2.f) {}

void Setting::Load() {
    this->setRequest({
        { sf::Keyboard::Key::Enter, Action::dropOverlap }
    });
}

void Setting::Update( sf::Time& dt ) {
    if ( this->quit() ) {
        direc = -1;
    } else {
        direc = 1;
    }

    elapsed += direc * dt.asSeconds();
    elapsed = std::clamp( elapsed, 0.f, duration);
    
    t = elapsed / duration;    
    
    if ( elapsed <= 0.f && direc == -1 ) {
        this->done( true );
    }
    // if ( t > 1.0f ) t = 1.0f;

    shadClr.a = static_cast<std::uint8_t>( 255 * Math::easeIn(t) );
    float y = Math::Lerp( this->initPos, Tool::W_CTR.y, Math::easeInOut(t) );

    shad.setColor( shadClr );
    bg.setPosition({ bg.getPosition().x, y });
    // bg.setScale( {s, s} );
}

void Setting::Render( sf::RenderWindow& win ) const {
    win.draw( shad );
    win.draw( bg );
}

void Setting::requestExit() { this->quit( true ); }
bool Setting::animated() const { return true; }
bool Setting::exitDone() const { return this->done(); }

State::Type Setting::getType() const { return State::Type::Setting; }