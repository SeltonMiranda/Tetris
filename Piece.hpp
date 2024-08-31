#pragma once

#include "TetrisTypes.hpp"
#include <memory>

namespace Tetris {
class Piece {
  private:
    int type, x, y;

  public:
    Tetris::Shape shape;

    // Constructor 
    Piece(int startType, int startX, int startY);
    // Destructor 
    virtual ~Piece() = default;

    // Creates a block, returns a unique_ptr
    static std::unique_ptr<Piece> createPiece(int type, int x, int y);

    // Draw piece color
    void draw(int t) const;

    int getX() const;
    void setX(int x);

    int getY() const;
    void setY(int y);

    int getType() const; 
    void setType(int type);

    // Check if coordinates (x, y) in board are block type
    bool isBlock(Tetris::Board& board, int x, int y) const;
    
    // Checks if (x, y) is within board grid
    bool isWithinBounds(int x, int y) const;

    // Checks if block can rotate in board
    bool canRotate(Tetris::Board& board, Tetris::Shape& rotated) const;

    // Rotates the block
    void rotate(Tetris::Board& board);

    // Checks if block collided with a non-blank space
    bool collided(Tetris::Board& board, int offx, int offy) const;
 
    // Overload the += operator for position adjustment
    Piece& operator+=(const std::pair<int, int>& offset);
};
}
