#include "Piece.hpp"
#include "TetrisTypes.hpp"

namespace Tetris {

Piece::Piece(int startType, int startX, int startY)
: type{startType + 2}, x{startX}, y{startY},
  shape{Tetris::Constants::tetrominos[startType]} {}

std::unique_ptr<Tetris::Piece> Tetris::Piece::createPiece(int type, int x, int y) {
  return std::make_unique<Tetris::Piece>(type, x, y);
}

void Piece::draw(int type) const {
  switch(type) {
    case 2: std::cout << Tetris::Constants::LIGHTBLUE; break;
    case 3: std::cout << Tetris::Constants::GREEN; break;
    case 4: std::cout << Tetris::Constants::YELLOW; break;
    case 5: std::cout << Tetris::Constants::BLUE; break;
    case 6: std::cout << Tetris::Constants::MAGENTA; break;
    case 7: std::cout << Tetris::Constants::RED; break;
    case 8: std::cout << Tetris::Constants::CYAN; break;
  }
  std::cout << "#" << Tetris::Constants::RESET;
}

int Piece::getX() const { return this->x; }
void Piece::setX(int x) { this->x = x; }

int Piece::getY() const { return this->y; }
void Piece::setY(int y) { this->y = y; }

int Piece::getType() const { return this->type; }
void Piece::setType(int type) { this->type = type; }

bool Piece::isBlock(Tetris::Board& board, int x, int y) const {
  return (board.at(y).at(x) >= 1 && board.at(y).at(x) <= 8);
}

bool Piece::isWithinBounds(int x, int y) const {
  return (x > 0 || x < Tetris::Constants::WIDTH  - 1 ||
          y > 0 || y < Tetris::Constants::HEIGHT - 1  );
}

bool Piece::canRotate(Tetris::Board& board, Tetris::Shape& rotated) const {
  for (int y = 0; y < Tetris::Constants::PIECESIZE; y++) {
    for (int x = 0; x < Tetris::Constants::PIECESIZE; x++) {
      if (rotated.at(y).at(x) >= 2 && rotated.at(y).at(x) <= 8) {
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

void Piece::rotate(Tetris::Board& board) {
  Tetris::Shape rotated;
  for (int y = 0; y < Tetris::Constants::PIECESIZE; y++) {
    for (int x = 0; x < Tetris::Constants::PIECESIZE; x++) {
      rotated[x][3 - y] = this->shape[y][x];
    }
  }

  if (this->canRotate(board, rotated)) this->shape = rotated;
}

bool Piece::collided(Tetris::Board& board, int offx, int offy) const {
  for (int y = 0; y < Tetris::Constants::PIECESIZE; y++) {
    for (int x = 0; x < Tetris::Constants::PIECESIZE; x++) {
      if (2 <= this->shape[y][x] && this->shape[y][x] <= 8) {
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
