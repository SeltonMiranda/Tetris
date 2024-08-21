#include "Piece.hpp"
#include <iostream>

const std::array<std::array<std::array<int, 4>, 4>, 7> Piece::tetrominos = {{
    // Tetromino I
    {{
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }},
    // Tetromino T
    {{
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }},
    // Tetromino O
    {{
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }},
    // Tetromino S
    {{
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0} }},
    // Tetromino Z
    {{
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }},
    // Tetromino L
    {{
        {1, 1, 1, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }},
    // Tetromino J
    {{
        {1, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }}
}};

Piece::Piece(int startType, int startX, int startY)
            : type{startType}, x{startX}, y{startY} 
{
  for (int dy = 0; dy < 4; dy++) {
    for (int dx = 0; dx < 4; dx++) {
      this->shape[dy][dx] = tetrominos[type][dy][dx];
    }
  } 
}
