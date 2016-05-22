#include "fn.hpp"


void Pause()
{

  // Pause 0.1 seconds between frames
  const double kWaitTime = 0.1;

  // clock_t is a type which holds clock ticks.
  clock_t startTime = clock();

  /*
   * This loop does nothing except loop and check how much time is
   * left.  We have to typecast startTime from clock_t to double using
   * static_cast<double>(...) syntax so that the division is correct.
   */
  while(
	( static_cast<double>(clock() - startTime) / CLOCKS_PER_SEC ) <
	kWaitTime
	);
}

point_t make_point (int row, int col)
{
  point_t result;
  result.row = row;
  result.col = col;
  return result;
}

void print_world(game_t& game)
{
  int status = system(k_clear_command.c_str());
  if (!status) {
    std::cout<< "[Error]: unable to clear screen" << std::endl;
  }
  for(int row = 0; row < game.numRows; ++row) {
    std::cout << game.world[row] << std::endl;
  }
  std::cout << "Food eaten: " << game.numEaten << std::endl;
}


void display_result(game_t& game)
{
  print_world(game);
  if(game.numEaten == kMaxFood)
    std::cout << "The snake ate enough food and wins!" << std::endl;
  else
    std::cout << "Oh no! The snake crashed!" << std::endl;
  return;
}

void open_user_file (std::ifstream& input)
{
  int option = 0;

  while (option == 0)  {
    std::cout << "Options available:" << std::endl
	      << "   1: Level 01"     << std::endl
	      << "  99: Exit"         << std::endl;
    std::cin >> option;
    switch (option) {
    case 1:
      input.open (level01.c_str());
      break;
    case 99:
      std::cout << "Good bye!" << std::endl;
      exit (0);
      break;
    default:
      std::cout << "Invalid option, choose again ..." << std::endl;
    }

    if (input.is_open()) {
      break;
    } else {
      std::cout << "[Error]: Unable to load configuration file." << std::endl;
      input.clear();
    }
  }
  return;
}

void load_world (game_t& game, std::ifstream& input) {
  input >> game.numRows >> game.numCols;
  game.world.resize(game.numRows);

  input >> game.dx >> game.dy;

  // Read in the '\n' character waiting in the input buffer
  std::string buff;
  std::getline(input, buff);

  for ( int row = 0; row < game.numRows; ++row ) {
    std::getline(input, game.world[row]);

    int col = game.world[row].find(kSnakeTile);
    if(col != static_cast<int>(std::string::npos)) {
      game.snake.push_back(make_point(row, col));
    }
  }
  game.numEaten = 0;
  return;
}

void initialize_game (game_t& game)
{
  std::ifstream input;
  open_user_file(input);
  load_world (game, input);
  return;
}

void run_simulation (game_t& game)
{
  /* Keep looping while we haven't eaten too much. */
  while(game.numEaten < kMaxFood) {
    print_world(game);

    // TODO: implementation
    // Display the board
    perform_AI(game);

    // TODO: implementation
    // Have the AI choose an action
    if(!move_snake(game)) // Move the snake and stop if we crashed.
      break;

    // Pause so we can see what's going on.
    Pause();
  }

  // Tell the user what happened
  display_result(game);

  return;
}
