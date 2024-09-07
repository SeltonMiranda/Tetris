#include "../includes/Piece.hpp"
#include "../includes/Constants.hpp"
#include "../includes/TetrisTypes.hpp"

namespace Tetris {

Piece::Piece(const int startType, const int startX, const int startY)
: type{startType + 2}, x{startX}, y{startY},
  shape{Tetris::Constants::tetrominos[startType]} {}

std::unique_ptr<Tetris::Piece> Piece::createPiece(const int type, const int x, const int y) {
  return std::make_unique<Tetris::Piece>(type, x, y);
}

void Piece::draw(const int type) const {
  switch(type) {
    case 2: std::cout << Tetris::Constants::LIGHTBLUE; break;
    case 3: std::cout << Tetris::Constants::GREEN; break;
    case 4: std::cout << Tetris::Constants::YELLOW; break;
    case 5: std::cout << Tetris::Constants::BLUE; break;
    case 6: std::cout << Tetris::Constants::MAGENTA; break;
    case 7: std::cout << Tetris::Constants::RED; break;
    case 8: std::cout << Tetris::Constants::CYAN; break;
  }
  std::cout << Tetris::Constants::BLOCK << Tetris::Constants::RESET;
}

int Piece::getX() const { return this->x; }
void Piece::setX(const int x) { this->x = x; }

int Piece::getY() const { return this->y; }
void Piece::setY(const int y) { this->y = y; }

int Piece::getType() const { return this->type; }
void Piece::setType(const int type) { this->type = type; }

bool Piece::isBlockType(const Tetris::Shape& shape, const int x, const int y) const {
  return (shape.at(y).at(x) >= 2 && shape.at(y).at(x) <= 8);
}

bool Piece::isBlock(const Tetris::Board& board, const int x, const int y) const {
  return (board.at(y).at(x) >= 1 && board.at(y).at(x) <= 8);
}

const Tetris::Shape& Piece::getShape() const { return this->shape; }

void Piece::setShape(const Tetris::Shape& shape) { this->shape = shape; }

bool Piece::isWithinBounds(const int x, const int y) const {
  return (x > 0 || x < Tetris::Constants::WIDTH  - 1 ||
          y > 0 || y < Tetris::Constants::HEIGHT - 1  );
}

bool Piece::canRotate(const Tetris::Board& board, const Tetris::Shape& rotated) const {
  for (int y = 0; y < Tetris::Constants::PIECESIZE; y++) {
    for (int x = 0; x < Tetris::Constants::PIECESIZE; x++) {
      if (this->isBlockType(rotated, x, y)) {
        int boardx{this->getX() + x};
        int boardy{this->getY() + y};
        if (!this->isWithinBounds(boardx, boardy) ||
            this->isBlock(board, boardx, boardy))
          return false;
      }
    }
  }
  return true;
}

void Piece::rotate(const Tetris::Board& board) {
  Tetris::Shape rotated;
  for (int y = 0; y < Tetris::Constants::PIECESIZE; y++) {
    for (int x = 0; x < Tetris::Constants::PIECESIZE; x++) {
      rotated[x][3 - y] = this->getShape().at(y).at(x);
    }
  }

  if (this->canRotate(board, rotated)) this->setShape(rotated);
}

bool Piece::collided(const Tetris::Board& board, const int offx, const int offy) const {
  for (int y = 0; y < Tetris::Constants::PIECESIZE; y++) {
    for (int x = 0; x < Tetris::Constants::PIECESIZE; x++) {
      if (this->isBlockType(this->getShape(), x, y)) {
        int px{this->getX() + x + offx};
        int py{this->getY() + y + offy};

        if (!this->isWithinBounds(px, py)) return true;
        if (board[py][px] != 0) return true;
      }
    }
  }
  return false;
}

Piece& Piece::operator+=(const std::pair<int, int>& offset) {
  this->x += offset.first;
  this->y += offset.second;
  return *this;
}
}
