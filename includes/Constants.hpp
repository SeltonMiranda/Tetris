#pragma once

#include <iostream>
#include <array>

namespace Tetris {
class Constants {
public:
  // Grid size
  static constexpr int HEIGHT = 22; 
  static constexpr int WIDTH = 16; 
  
  // Block types
  static constexpr int TYPES = 7;
  static const std::string SHADOW;
  static const std::string BLOCK;
  static const std::string EMPTY;

  // Grid block size
  static constexpr int PIECESIZE = 4;

  // Escape sequences
  static const std::string CLEARSCREEN;
  static const std::string HIDECURSOR;
  static const std::string SHOWCURSOR;

  // Colors
  static const std::string RESET;
  static const std::string RED;
  static const std::string GREEN;
  static const std::string YELLOW;
  static const std::string BLUE;
  static const std::string MAGENTA;
  static const std::string CYAN;
  static const std::string WHITE;
  static const std::string LIGHTGRAY;
  static const std::string LIGHTBLUE;

  // Blocks shape
  static const std::array<std::array<std::array<int, 4>, 4>, 7> tetrominos;
};
}
