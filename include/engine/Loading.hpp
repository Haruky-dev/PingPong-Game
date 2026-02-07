#pragma once

#include <engine/State.hpp>
#include <engine/StateType.hpp>
#include <engine/Progressive.hpp>

#include <SFML/Graphics.hpp>

#include <thread>
#include <atomic>

#include <iostream>

class Loading : public State, public Progressive {
    private:
        sf::Font fnt;
        sf::Text txt;
        sf::Text progTxt;
        sf::RectangleShape bg;
        std::thread loader;

        std::atomic<int> loadCost {1}; // total n of work units (avoid /0)
        std::atomic<int> currUnit {0}; // track curr n of work units

    public:
        // Add into total work units
        void addTotal( int units ) override {
            loadCost += units;
        }

        // increment the curr counter of work units
        void incCount( int units=1 ) override {
            currUnit += units;
        }

    public:
        Loading();

        void Load() override;
        void Update(sf::Time &dt) override;
        void Render(sf::RenderWindow &win) const override;

        StateType getType() const override;

        std::atomic<bool> loadDone {false};

        ~Loading();
};