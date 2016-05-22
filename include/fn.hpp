#ifndef __FN_HPP_DEFINED
#define __FN_HPP_DEFINED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <ctime>
#include <cstdlib>

/*
 * Data structures of the game
 */

/*
 * Snake body
 */
struct point_t {
  int row;
  int col;
};

/*
 * Game data
 */
struct game_t {
  std::vector<std::string> world;
  int numRows;
  int numCols;

  std::deque<point_t> snake;
  int dx;
  int dy;

  int numEaten;
};


/* Number of food pellets that must be eaten to win. */
const int kMaxFood = 20;

/* Constants for the different tile types. */
const char kEmptyTile = ' ';
const char kWallTile  = '#';
const char kFoodTile  = '$';
const char kSnakeTile = '*';

/* Level 01 - configuration file*/
const std::string level01 = "resource/level01.txt";
const std::string k_clear_command = "clear";

void Pause();
point_t make_point (int row, int col);
void print_world(game_t& game);
void display_result(game_t& game);
void initialize_game (game_t& game);
void open_user_file (std::ifstream& input);
void load_world (game_t& game, std::ifstream& input);
void run_simulation (game_t& game);

#endif /*__FN_HPP_DEFINED*/
