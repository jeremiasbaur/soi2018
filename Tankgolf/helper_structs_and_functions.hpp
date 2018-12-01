//
// #####    Helper structs and functions for Tankgolf bots   #######
//
// Check template_bot.cpp to see how to use these structs and functions.

#include <iostream>
#include <string>
#include <array>
#include <utility>
#include <cassert>
#include <tuple>

struct Orientation {
    float x, y, rot;
};

struct GameState {
    std::array<Orientation, 2> tanks;
    float last_impact_x, last_impact_y;
    std::array<int, 2> scores {{0, 0}};
};

enum class RoundType {Respawn, Shoot, GameOver};

// These operator<< and operator>> functions allow us to just write
//    std::cin >> game_state;
// so we don't have to read in all the individual floats every time.

std::ostream& operator<<(std::ostream& stream, Orientation const& orientation) {
    stream << orientation.x << ' ' << orientation.y << ' ' << orientation.rot;
    return stream;
}

std::istream& operator>>(std::istream& stream, Orientation& orientation) {
    stream >> orientation.x >> orientation.y >> orientation.rot;

    if (!stream)
        throw std::invalid_argument("Could not read tank orientation.");

    return stream;
}

std::istream& operator>>(std::istream& stream, GameState& state) {
    stream >> state.tanks[0] >> state.tanks[1] 
           >> state.last_impact_x >> state.last_impact_y 
           >> state.scores[0] >> state.scores[1];

    if (!stream)
        throw std::invalid_argument("Could not read game state.");

    return stream;
}

std::istream& operator>>(std::istream& stream, RoundType& round_type) {
    std::string str;
    stream >> str;

    if (!stream)
        throw std::invalid_argument("Could not read round type.");

    if (str == "startrespawn") round_type = RoundType::Respawn;
    else if (str == "startshoot") round_type = RoundType::Shoot;
    else if (str == "gameover") round_type = RoundType::GameOver;
    else throw std::invalid_argument("Unknown round type: " + str);

    return stream;
}

// Use these functions to send queries or your shoot/respawn instructions to
// the server. If you use these functions you never have to do anything with
// cin/cout yourself.

std::pair<RoundType, GameState> startRound() {
    RoundType round_type;
    std::cin >> round_type;

    GameState game_state;
    if (round_type != RoundType::GameOver)
        std::cin >> game_state;

    return {round_type, game_state};
}

GameState queryShoot(float angle, float intensity) {
    std::cout << "queryshoot " << angle << ' ' << intensity << std::endl;
    GameState state;
    std::string start_state_message;
    std::cin >> start_state_message;
    assert(start_state_message == "state");
    std::cin >> state;
    return state;
}

GameState queryRespawn(float x_position) {
    std::cout << "queryrespawn " << x_position << std::endl;
    GameState state;
    std::string start_state_message;
    std::cin >> start_state_message;
    assert(start_state_message == "state");
    std::cin >> state;
    return state;
}

GameState fullQueryShoot(std::array<Orientation, 2> tanks, float angle, float intensity) {
    std::cout << "fullqueryshoot " << tanks[0] << ' ' << tanks[1] 
              << ' ' << angle << ' ' << intensity << std::endl;
    GameState state;
    std::string start_state_message;
    std::cin >> start_state_message;
    assert(start_state_message == "state");
    std::cin >> state;
    return state;
}

GameState fullQueryRespawn(std::array<Orientation, 2> tanks, float x_position) {
    std::cout << "fullqueryrespawn " << tanks[0] << ' ' << tanks[1] 
              << ' ' << x_position << std::endl;
    GameState state;
    std::string start_state_message;
    std::cin >> start_state_message;
    assert(start_state_message == "state");
    std::cin >> state;
    return state;
}

void commitShoot(float angle, float intensity) {
    std::cout << "shoot " << angle << ' ' << intensity << std::endl;
}

void commitRespawn(float x_position) {
    std::cout << "respawn " << x_position << std::endl;
}
