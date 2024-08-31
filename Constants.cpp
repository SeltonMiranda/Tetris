#include "Constants.hpp"

namespace Tetris {

const std::string Tetris::Constants::CLEARSCREEN{"\033[2J\033[1;1H"};
const std::string Tetris::Constants::HIDECURSOR{"\033[?25l"};
const std::string Tetris::Constants::SHOWCURSOR{"\033[?25h"};

const std::string Tetris::Constants::RESET{"\033[0m"};
const std::string Tetris::Constants::RED{"\033[31m"};
const std::string Tetris::Constants::GREEN{"\033[32m"};
const std::string Tetris::Constants::YELLOW{"\033[33m"};
const std::string Tetris::Constants::BLUE{"\033[34m"};
const std::string Tetris::Constants::MAGENTA{"\033[35m"};
const std::string Tetris::Constants::CYAN{"\033[36m"};
const std::string Tetris::Constants::WHITE{"\033[37m"};
const std::string Tetris::Constants::LIGHTGRAY{"\033[90m"};
const std::string Tetris::Constants::LIGHTBLUE{"\033[94m"};

const std::array<std::array<std::array<int, 4>, 4>, 7> Tetris::Constants::tetrominos = {{
  // Tetromino I
  {{
    {0, 0, 0, 0},
    {2, 2, 2, 2},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  }},
  // Tetromino T
  {{
    {3, 3, 3, 0},
    {0, 3, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  }},
  // Tetromino O
  {{
    {0, 0, 0, 0},
    {0, 4, 4, 0},
    {0, 4, 4, 0},
    {0, 0, 0, 0}
  }},
  // Tetromino S
  {{
    {0, 5, 5, 0},
    {5, 5, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0} }},
  // Tetromino Z
  {{
    {6, 6, 0, 0},
    {0, 6, 6, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  }},
  // Tetromino L
  {{
    {7, 7, 7, 0},
    {7, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  }},
  // Tetromino J
  {{
    {8, 8, 8, 0},
    {0, 0, 8, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  }}
}};

}
