#pragma once

#include "Constants.hpp"
#include <array>

namespace Tetris {

  using Board = std::array<std::array<int, Tetris::Constants::WIDTH>, Tetris::Constants::HEIGHT>;
  using Shape = std::array<std::array<int, Tetris::Constants::PIECESIZE>, Tetris::Constants::PIECESIZE>;

}

