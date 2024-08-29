#include "Piece.hpp"
#include "Constants.hpp"

namespace Tetris {

Piece::Piece(int startType, int startX, int startY)
: type{startType + 2}, x{startX}, y{startY},
  shape{Tetris::Constants::tetrominos[startType]} {}

std::unique_ptr<Tetris::Piece> Tetris::Piece::createPiece(int type, int x, int y) {
  return std::make_unique<Tetris::Piece>(type, x, y);
}

void Piece::draw(int t) const {
  switch(t) {
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

Piece& Piece::operator+=(const std::pair<int, int>& offset) {
  this->x += offset.first;
  this->y += offset.second;
  return *this;
}
}
