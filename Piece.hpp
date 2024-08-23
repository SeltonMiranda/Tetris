#ifndef PIECE_HPP
#define PIECE_HPP

#include <array>

class Piece {
  private:
    // Constants
    static const std::array<std::array<std::array<int, 4>, 4>, 7> tetrominos;
    static constexpr int TYPES = 7;

  public:
    int type;
    int x;
    int y;
    std::array<std::array<int, 4>, 4> shape;
    Piece(int startType, int startX, int startY);
    ~Piece() = default;

};
#endif // PIECE_HPP
