// This bot is meant to get you started if you know how C++ structs work and
// you don't want to spend time with the parsing of objects.

// Some useful stuff is provided in this header file. Have a look at the main
// function below first to see how they are used, then maybe check out the code
// in "helper_structs_and_functions.hpp" later.
#include "helper_structs_and_functions.hpp"
#include <iostream>
#include <fstream>
using namespace std;
#include <math.h>

// ######## Actual bot code ###########
// The bot just shoots in the same direction every time, so it's not a very
// good bot, it's just here to show you how to use the provided helper
// functions.

void shoot(float angle, float intensity){
  commitShoot(angle, intensity);
}

float normalize(float intensity){
  if (intensity/16.45 > 1){
    intensity = 16.45;
  }
  return intensity/16.45;
}

int main() {
  ofstream test;
    bool running = true;

    while (running) {
        RoundType round_type;
        GameState game_state;

        std::tie(round_type, game_state) = startRound();

        switch (round_type) {
          case RoundType::Respawn: {
              float spawn_position = 5;

              // Check the current opponent position (opponent is always at tanks[1])
              if (game_state.tanks[1].x == -1) {
                  // Position of -1 means, that the opponent is currently not on
                  // the map, so the opponent probably fell off the map or we are
                  // spawning first and this is the beginning of the game.
                  spawn_position = 15.6;
              } else {
                  // spawn next to the opponent
                  if (game_state.tanks[1].x < 10){
                    spawn_position = 15.6;
                  } else{
                    spawn_position = 4;
                  }
              }

              /*GameState preview_state = queryRespawn(spawn_position);

              if (preview_state.scores[1] > game_state.scores[1]) {
                  // score of opponent would increase, this means we fall off
                  // the map if we spawn at this location, so we change the
                  // location.

                  spawn_position = 5;
              }*/

              commitRespawn(spawn_position);

              break;
        } case RoundType::Shoot: {
            float intensity, shoot_intensity;
            test.open("test.txt", ios::app);
            test << game_state.tanks[0].rot << "\n";
            if (game_state.tanks[0].rot > 0.2){
              float rad = 1.4;
              float pwr = 1;
        			for (int i = 1; i < 7; ++i){
        				rad = rad * 0.9;
        				GameState preview_state = queryShoot(rad, pwr);
        				if (preview_state.scores[0] >= game_state.scores[0]){
                  break;
        				}
                commitShoot(rad, pwr);
            }
          }

            // Shoot with the same angle and intensity every time.
            if (game_state.tanks[1].x < game_state.tanks[0].x){
              shoot_intensity = normalize(sqrt(20*(game_state.tanks[0].x-game_state.tanks[1].x)));
              for(int i = 1; i<=4; ++i){
                intensity = normalize(sqrt(20*(game_state.tanks[0].x-game_state.tanks[1].x+1.5-i*0.5)));
                GameState preview_state = queryShoot(0.8, intensity);
                if (preview_state.scores[0] > game_state.scores[0] && preview_state.scores[1] == game_state.scores[1]){
                  shoot_intensity = intensity;
                }
              }
              shoot(0.8, shoot_intensity);

            } else{
              shoot_intensity = normalize(sqrt(20*(game_state.tanks[1].x-game_state.tanks[0].x)));
              for(int i = 1; i<=4; ++i){
                intensity = normalize(sqrt(20*(game_state.tanks[1].x-game_state.tanks[0].x+1.5-i*0.5)));
                GameState preview_state = queryShoot(-0.8, intensity);
                if (preview_state.scores[0] > game_state.scores[0] && preview_state.scores[1] == game_state.scores[1]){
                  shoot_intensity = intensity;
                }
              }
              shoot(-0.8, shoot_intensity);
            }
            //test << shoot_intensity/13.45 <<  " " << shoot_intensity << "\n";
            test.close();
            break;
        } case RoundType::GameOver: {
            running = false;
            break;
        }}
    }
}

/*

// This bot is meant to get you started if you know how C++ structs work and
// you don't want to spend time with the parsing of objects.

// Some useful stuff is provided in this header file. Have a look at the main
// function below first to see how they are used, then maybe check out the code
// in "helper_structs_and_functions.hpp" later.
#include "helper_structs_and_functions.hpp"
#include <iostream>
#include <fstream>
using namespace std;
#include <math.h>

#define PI 3.14159265
// ######## Actual bot code ###########
// The bot just shoots in the same direction every time, so it's not a very
// good bot, it's just here to show you how to use the provided helper
// functions.

void shoot(float intensity, float angle){
  if (intensity/16.4 > 1){
    intensity = 16.4;
  }
  commitShoot(angle, intensity/16.4);
}

int main() {
  ofstream test;
    bool running = true;

    while (running) {
        RoundType round_type;
        GameState game_state;

        std::tie(round_type, game_state) = startRound();

        switch (round_type) {
          case RoundType::Respawn: {
              float spawn_position = 5;

              // Check the current opponent position (opponent is always at tanks[1])
              if (game_state.tanks[1].x == -1) {
                  // Position of -1 means, that the opponent is currently not on
                  // the map, so the opponent probably fell off the map or we are
                  // spawning first and this is the beginning of the game.
                  spawn_position = 15.6;
              } else {
                  // spawn next to the opponent
                  if (game_state.tanks[1].x > 4.5 && game_state.tanks[1].x < 10){
                    spawn_position = 2;
                  } else if (game_state.tanks[1].x > 10){
                    spawn_position = 4;
                  } else{
                    spawn_position = 15.6;
                  }
                    /*if (game_state.tanks[1].x>15){
                      spawn_position = 13;
                    } else{
                      spawn_position = 15.6;
                    }
                  }*/

              /*GameState preview_state = queryRespawn(spawn_position);

              if (preview_state.scores[1] > game_state.scores[1]) {
                  // score of opponent would increase, this means we fall off
                  // the map if we spawn at this location, so we change the
                  // location.

                  spawn_position = 5;
              }*/
/*
              commitRespawn(spawn_position);

              break;
        } case RoundType::Shoot: {
            float intensity, max_intensity;
            test.open("test.txt", ios::app);
            // Shoot with the same angle and intensity every time.
            if (game_state.tanks[1].x < game_state.tanks[0].x){

              float distance = game_state.tanks[0].x-game_state.tanks[1].x-0.2;
              intensity = sqrt((20*distance)/(sin(0.7854*2*PI/180)));
              float angle = asin((20*distance)/(2*intensity*intensity)) *180/PI;
              shoot(intensity, angle*(0.5/45));

              //max_intensity = sqrt(20*())

              test << intensity/16.4 <<  " " << intensity << "\n";
            } else{
              float distance = game_state.tanks[1].x-game_state.tanks[0].x-0.2;
              intensity = sqrt((20*distance)/(sin(0.7854*2*PI/180)));
              float angle = asin((20*distance)/(2*intensity*intensity)) *180/PI;
              shoot(intensity, -angle*(0.5/45));
              test << "v2 "<< intensity/16.4 <<  " " << intensity << "\n";
            }
            test.close();
            break;
        } case RoundType::GameOver: {
            running = false;
            break;
        }
      }
    }
}
*/

/*#include <iostream>
#include <string>
#include <random>

const int seed = std::random_device()();

const float min_x_pos = 2.f;
const float max_x_pos = 15.5f;

void ignoreGameState() {
    float devnull;
    std::cin >> devnull >> devnull >> devnull; // Tank A
    std::cin >> devnull >> devnull >> devnull; // Tank B
    std::cin >> devnull >> devnull; // Bullet Impact pos
    std::cin >> devnull >> devnull; // scores
}

int main() {
    std::mt19937 rng (seed);

    std::uniform_real_distribution<float> angle_dist (-M_PI/2 + 0.05, M_PI/2 - 0.05);
    std::uniform_real_distribution<float> intensity_dist (0.1, 1);
    std::uniform_real_distribution<float> x_pos_dist (min_x_pos, max_x_pos);

    std::string command;
    while (std::cin >> command) {
        ignoreGameState();

        if (command == "startshoot") {
            if (rng() & 1) {
                std::cout << "queryshoot " << angle_dist(rng) << ' ' << intensity_dist(rng) << std::endl;
                std::string devnull; std::cin >> devnull;
                ignoreGameState();
            }

            std::cout << "shoot " << angle_dist(rng) << ' ' << intensity_dist(rng) << std::endl;
        } else if (command == "startrespawn") {
            if (rng() & 1) {
                std::cout << "queryrespawn " << x_pos_dist(rng) << std::endl;
                std::string devnull; std::cin >> devnull;
                ignoreGameState();
            }

            std::cout << "respawn " << x_pos_dist(rng) << std::endl;
        } else if (command == "gameover") {
            break;
        }
    }

    std::cerr << "Random Bot: exiting.\n";





/*#include <iostream>
#include <string>
#include <random>

const int seed = std::random_device()();

const float min_x_pos = 2.f;
const float max_x_pos = 15.5f;

void ignoreGameState() {
    float devnull;
    std::cin >> devnull >> devnull >> devnull; // Tank A
    std::cin >> devnull >> devnull >> devnull; // Tank B
    std::cin >> devnull >> devnull; // Bullet Impact pos
    std::cin >> devnull >> devnull; // scores
}

int main() {
    std::mt19937 rng (seed);

    std::uniform_real_distribution<float> angle_dist (-M_PI/2 + 0.05, M_PI/2 - 0.05);
    std::uniform_real_distribution<float> intensity_dist (0.1, 1);
    std::uniform_real_distribution<float> x_pos_dist (min_x_pos, max_x_pos);

    std::string command;
    while (std::cin >> command) {
        ignoreGameState();

        if (command == "startshoot") {
            if (rng() & 1) {
                std::cout << "queryshoot " << angle_dist(rng) << ' ' << intensity_dist(rng) << std::endl;
                std::string devnull; std::cin >> devnull;
                ignoreGameState();
            }

            std::cout << "shoot " << angle_dist(rng) << ' ' << intensity_dist(rng) << std::endl;
        } else if (command == "startrespawn") {
            if (rng() & 1) {
                std::cout << "queryrespawn " << x_pos_dist(rng) << std::endl;
                std::string devnull; std::cin >> devnull;
                ignoreGameState();
            }

            std::cout << "respawn " << x_pos_dist(rng) << std::endl;
        } else if (command == "gameover") {
            break;
        }
    }

    std::cerr << "Random Bot: exiting.\n";
}
*/
