#pragma once

#include "State.hpp"
#include "StateType.hpp"
#include "Progressive.hpp"

#include <SFML/Graphics.hpp>

#include <thread>
#include <atomic>

#include <print>

class Loading : public State, public Progressive {
    private:
        sf::Font fnt;
        sf::Text txt;
        sf::Text progTxt;
        sf::RectangleShape bg;
        std::thread loader;

        std::atomic<int> loadCost {0}; // total n of work units
        std::atomic<int> currUnit {0}; // track curr n of work units

    public:
        // Add into total work units
        void addTotal( int units ) override {
            // loadCost.fetch_add( units, std::memory_order_relaxed );
            loadCost += units;
            std::println("loadCost={}", loadCost.load());
        }
        // increment the curr counter of work units
        void incCount( int units=1 ) override {
            // currUnit.fetch_add( units, std::memory_order_release );
            currUnit += units;
            std::println("currUnit={}", currUnit.load());
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