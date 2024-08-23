#include "Tetris.hpp"
#include <cstdlib>
#include <ctime>


int main() {
  std::srand(std::time(nullptr));

  Tetris *tetris{new Tetris()};
  tetris->run();

  delete tetris;
  return 0;
}
