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
  //ofstream test;
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
            //test.open("test.txt", ios::app);
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
            //test.close();
            break;
        } case RoundType::GameOver: {
            running = false;
            break;
        }}
    }
}