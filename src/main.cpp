#include "../includes/Game.hpp"
#include <cstdlib>
#include <ctime>


int main() {
  std::srand(std::time(nullptr));
  Tetris::Game game;

  try {
    game.run();
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
