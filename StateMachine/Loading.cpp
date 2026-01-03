#include "Loading.hpp"

#include "../Assets.hpp"
#include "../SoundAssets.hpp"

using namespace std::literals::chrono_literals;

Loading::Loading() : State() {
    if (!(fnt.loadFromFile("Resources/RasterForge.ttf")))
        throw std::runtime_error("UNABLE TO LOAD [FONT] in Loading State!");

    txt.setFont(fnt);
    progTxt.setFont(fnt);
    txt.setString("Loading..");
    txt.setOrigin(
        txt.getGlobalBounds().width / 2.f,
        txt.getGlobalBounds().height / 2.f);
    txt.setPosition(360.f, 200.f);
    txt.setFillColor(sf::Color::White);

    progTxt.setFont(fnt);
    progTxt.setString("0 %");
    progTxt.setOrigin(
        progTxt.getGlobalBounds().width / 2.f,
        progTxt.getGlobalBounds().height / 2.f);
    progTxt.setPosition(360.f, 240);
    progTxt.setFillColor(sf::Color::White);

    bg.setSize(sf::Vector2f(720.f, 480.f));
    bg.setFillColor(sf::Color::Black);
}

void Loading::Load() {
    std::println("Loading State");

    loader = std::thread([this]()
                         {
        Assets::getInst().Load( *this );
        SoundAssets::getInst().Load( *this );
        
        loadDone = true;
        std::println("Finished Loading"); });

    std::println("{}, {}", loadCost.load(), currUnit.load());
}

void Loading::Update(sf::Time &dt) {
    progTxt.setString(
        std::to_string(
            static_cast<int>((currUnit.load() / static_cast<float>(loadCost.load())) * 100.0f)) +
        " %");

    progTxt.setOrigin(
        progTxt.getGlobalBounds().width / 2.f,
        progTxt.getGlobalBounds().height / 2.f);

    progTxt.setPosition(360.f, 240);
}

void Loading::Render(sf::RenderWindow &win) const {
    win.draw(bg);
    win.draw(txt);
    win.draw(progTxt);
}

StateType Loading::getType() const { return StateType::Loading; }

Loading::~Loading() {
    if (loader.joinable())
        loader.join();
}