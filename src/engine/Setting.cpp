#include <engine/Setting.hpp>

#include <cstdint>

#include <cache/visuals/SettingUI.hpp>
#include <tools/Tool.hpp>
#include <tools/Math.hpp>

Setting::Setting() : State(), bg(SettingUI::getInst().get("bg")),
    shad(SettingUI::getInst().get("shad")), shadClr(shad.getColor()),
    t(0.0f), elapsed(0.0f), duration(0.5f),
    initPos(Tool::HEIGHT + bg.getTexture().getSize().y / 2.f) {}

void Setting::Load() {
    // this->isOverlapping( true );

    // bg.setScale( {0.f, 0.f} );
    this->setRequest({
        { sf::Keyboard::Key::Enter, Action::dropOverlap }
    });
}

void Setting::Update( sf::Time& dt ) {
    if (t < 1.0f) {
        elapsed += dt.asSeconds();
        t = elapsed / duration;    

        if ( t > 1.0f ) t = 1.0f;

        shadClr.a = static_cast<std::uint8_t>( 255 * Math::easeIn(t) );
        float y = Math::Lerp( this->initPos, Tool::W_CTR.y, Math::easeInOut(t) );

        shad.setColor( shadClr );
        bg.setPosition({ bg.getPosition().x, y });
        // bg.setScale( {s, s} );
    }
}

void Setting::Render( sf::RenderWindow& win ) const {
    win.draw( shad );
    win.draw( bg );
}

State::Type Setting::getType() const { return State::Type::Setting; }