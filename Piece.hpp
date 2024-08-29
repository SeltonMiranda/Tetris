#pragma once

#include <array>
#include <memory>

#include "Constants.hpp"

namespace Tetris {
class Piece {
  private:
    int type, x, y;
  public:
    std::array<std::array<int, Tetris::Constants::PIECESIZE>,
                            Tetris::Constants::PIECESIZE> shape;

    static std::unique_ptr<Tetris::Piece> createPiece(int type, int x, int y);

    // Constructor 
    Piece(int startType, int startX, int startY);
    // Destructor 
    virtual ~Piece() = default;

    // Draw piece color
    void draw(int t) const;

    int getX() const;
    void setX(int x);

    int getY() const;
    void setY(int y);

    int getType() const; 
    void setType(int type);

    // Overload the += operator for position adjustment
    Piece& operator+=(const std::pair<int, int>& offset);
};
}
