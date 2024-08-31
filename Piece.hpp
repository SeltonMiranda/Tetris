#pragma once

#include <array>
#include <memory>

#include "Constants.hpp"

namespace Tetris {
class Piece {
  private:
    int type, x, y;
  public:
    std::array<std::array<int, Tetris::Constants::PIECESIZE>, Tetris::Constants::PIECESIZE> shape;

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

    // Check if coordinates (x, y) in board are block type
    bool isBlock(std::array<std::array<int, Tetris::Constants::WIDTH>, Tetris::Constants::HEIGHT>& board, int x, int y) const;
    
    // Checks if (x, y) is within board grid
    bool isWithinBounds(int x, int y) const;

    // Checks if block can rotate in board
    bool canRotate(std::array<std::array<int, Tetris::Constants::WIDTH>, Tetris::Constants::HEIGHT>& board, std::array<std::array<int, Tetris::Constants::PIECESIZE>, Tetris::Constants::PIECESIZE>& rotated) const;

    // Rotates the block
    void rotate(std::array<std::array<int, Tetris::Constants::WIDTH>, Tetris::Constants::HEIGHT>& board);

    // Checks if block collided with a non-blank space
    bool collided(std::array<std::array<int, Tetris::Constants::WIDTH>, Tetris::Constants::HEIGHT>& board, int offx, int offy) const;
 
    // Overload the += operator for position adjustment
    Piece& operator+=(const std::pair<int, int>& offset);
};
}
