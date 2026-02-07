#include <engine/Setting.hpp>

#include <cstdint>

#include <cache/visuals/SettingUI.hpp>
#include <entities/Utils.hpp>

Setting::Setting() : State(), bg(SettingUI::getInst().get("bg")),
    shad(SettingUI::getInst().get("shad")), shadClr(shad.getColor()),
    t(0.0f), elapsed(0.0f), duration(0.5f),
    initPos(Utils::HEIGHT + bg.getTexture().getSize().y / 2.f) {}

void Setting::Load() {
    // this->isOverlapping( true );

    // bg.setScale( {0.f, 0.f} );
}

void Setting::Update( sf::Time& dt ) {
    if (t <= 1.0f) {
        elapsed += dt.asSeconds();
        t = elapsed / duration;    

        shadClr.a = static_cast<std::uint8_t>( 255 * Utils::easeIn(t) );
        float y = Utils::Lerp( this->initPos, Utils::W_CTR.y, Utils::easeInOut(t) );

        shad.setColor( shadClr );
        bg.setPosition({ bg.getPosition().x, y });
        // bg.setScale( {s, s} );
    }
}

void Setting::Render( sf::RenderWindow& win ) const {
    win.draw( shad );
    win.draw( bg );
}

StateType Setting::getType() const { return StateType::Setting; }