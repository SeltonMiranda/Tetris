#pragma once

// System includes
#include <memory>

// Personal includes
#include "TetrisTypes.hpp"

namespace Tetris {
class Piece {
  private:
    int type, x, y;

  public:
    Tetris::Shape shape;

    // Constructor 
    Piece(const int startType, const int startX, const int startY);

    // Destructor 
    virtual ~Piece() = default;

    // Creates a block, returns a unique_ptr
    static std::unique_ptr<Piece> createPiece(const int type, const int x, const int y);

    // Draw piece color
    void draw(const int type) const;

    int getX() const;
    void setX(int x);

    int getY() const;
    void setY(const int y);

    int getType() const; 
    void setType(const int type);

    const Tetris::Shape& getShape() const;
    void setShape(const Tetris::Shape& shape);

    // Check if coordinates (x, y) in shape are block type
    bool isBlockType(const Tetris::Shape& shape, const int x, const int y) const;

    // Check if coordinates (x, y) in board are any kind of block
    bool isBlock(const Tetris::Board& board, const int x, const int y) const;
    
    // Checks if (x, y) is within board grid
    bool isWithinBounds(const int x, const int y) const;

    // Checks if block can rotate in board
    bool canRotate(const Tetris::Board& board, const Tetris::Shape& rotated) const;

    // Rotates the block
    void rotate(const Tetris::Board& board);

    // Checks if block collided with a non-blank space
    bool collided(const Tetris::Board& board, const int offx, const int offy) const;
 
    // Overload the += operator for position adjustment
    Piece& operator+=(const std::pair<int, int>& offset);
};
}
