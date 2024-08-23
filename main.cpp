#include "Tetris.hpp"
#include <cstdlib>
#include <ctime>


int main() {
  std::srand(std::time(nullptr));

  Tetris tetris;
  tetris.run();

  return 0;
}
