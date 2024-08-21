#include <iostream>
#include "Tetris.hpp"
#include <cstdlib>
#include <ctime>


int main() {
  std::srand(std::time(nullptr));
  Tetris *game{new Tetris()};
  game->run();
  delete game;
  return 0;
}
