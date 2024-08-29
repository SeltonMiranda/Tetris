#include "Game.hpp"
#include <cstdlib>
#include <ctime>


int main() {
  std::srand(std::time(nullptr));

  Tetris::Game game;
  game.run();

  return 0;
}
