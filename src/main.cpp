// Snake Game simulation as implemented from the PDF file.

#include "main.hpp"

// ------------------------------------------------------------------------

/* The main program. Initializes the world, then runs the simulation. */
int main (int argc, char* argv[])
{
  game_t game;
  InitializeGame(game);
  RunSimulation(game);
  return 0;
}
// ------------------------------------------------------------------------
