#include <engine/Loading.hpp>

#include <cache/TextureCache.hpp>
#include <cache/SoundCache.hpp>

#include <cache/visuals/MenuUI.hpp>
#include <cache/visuals/PlayUI.hpp>
#include <cache/visuals/SettingUI.hpp>

using namespace std::literals::chrono_literals;

Loading::Loading() : State(), fnt(), txt(fnt), progTxt(fnt) {
    if (!(fnt.openFromFile("assets/RasterForge.ttf")))
        throw std::runtime_error("UNABLE TO LOAD [FONT] in Loading State!");

    txt.setFont(fnt);
    progTxt.setFont(fnt);
    txt.setString("Loading..");
    txt.setOrigin(
        txt.getGlobalBounds().size / 2.f
    );
    txt.setPosition({360.f, 200.f});
    txt.setFillColor(sf::Color::White);

    progTxt.setFont(fnt);
    progTxt.setString("0 %");
    progTxt.setOrigin(
        progTxt.getGlobalBounds().size / 2.f
    );
    progTxt.setPosition({360.f, 240});
    progTxt.setFillColor(sf::Color::White);

    bg.setSize(sf::Vector2f(720.f, 480.f));
    bg.setFillColor(sf::Color::Black);

}

void Loading::Load() {
    try {
        loader = std::thread([this]()
        {
            // create OpenGL/SFML context
            sf::Context ctx;

            TextureCache::getInst().Load( *this );

            MenuUI::getInst().Load( *this );
            PlayUI::getInst().Load( *this );
            SettingUI::getInst().Load( *this );
            
            SoundCache::getInst().Load( *this );

            loadDone.store(true);

        });
    } catch (...) {
        throw std::runtime_error("Loading Thread Fail\n");   
    }
}

void Loading::Update(sf::Time &dt) {
    progTxt.setString(
        std::to_string(
            static_cast<int>( (currUnit.load() / static_cast<float>(loadCost.load()) ) * 100.0f )
        )
        + " %"
    );

    progTxt.setOrigin(
        progTxt.getGlobalBounds().size / 2.f
    );

    progTxt.setPosition({360.f, 240});
}

void Loading::Render(sf::RenderWindow &win) const {
    win.draw(bg);
    win.draw(txt);
    win.draw(progTxt);
}

State::Type Loading::getType() const { return State::Type::Loading; }

Loading::~Loading() {
    if (loader.joinable())
        loader.join();
}