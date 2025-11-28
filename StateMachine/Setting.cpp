#include "Setting.hpp"

#include "../Assets.hpp"

Setting::Setting() : State() {}

void Setting::Load() {
    bg = Assets::getInst().getSettingMenu();
    shad = Assets::getInst().getShadow();
    // this->isOverlapping( true );
}

void Setting::Update( sf::Time& dt ) {}

void Setting::Render( sf::RenderWindow& win ) const {
    win.draw( shad );
    win.draw( bg );
}

StateType Setting::getType() const { return StateType::Setting; }