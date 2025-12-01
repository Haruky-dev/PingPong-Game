#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <fstream>

#include "Json/json.hpp"

using json = nlohmann::json;
using str  = std::string;


class Json {
    private:
        static json confData;

        // helper for safe accessing into nested data
        static json getVal( const str& key );

        static void Load( const str& filePath = "conf.json" );

    public:
        static void reLoad();

        // special members

        // getters
            // Primitive types
        static int   getInt( const str& key );
        static float getFloat( const str& key);
        static bool  getBool( const str& key );
        static str   getString( const str& key );
        // json  getArray( const str& key )  const;
            // objects
        // sf::Vector2f getV2f( const json& arr ) const;

            // other accessing funcs

        // special getters
        // float playerSpeed()  const { return getFloat("player.speed"); }
        // float AIspeed()      const { return getFloat("ai.speed"); }
        // float ballSpeed()    const { return getFloat("ball.speed"); }
        // float ballRadius()   const { return getFloat("ball.radius"); }

        // check if config data has loaded seccussfully
        static bool inValid() {
            return (Json::confData.is_null() ||
                Json::confData.empty();)
        }
};
