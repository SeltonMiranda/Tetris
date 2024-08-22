#include "Tetris.hpp"
#include <iostream>
#include <unistd.h>

Tetris::Tetris() : gameOver{false}, fps{60}, score{0} {
  for (int y = 0; y < Tetris::HEIGHT; y++) {
    for (int x = 0; x < Tetris::WIDTH; x++) {
      if ( y == 0 || y == Tetris::HEIGHT - 1 ||
        x == 0 || x == Tetris::WIDTH  - 1 ) {
        this->board[y][x] = 1;
      } else {
        this->board[y][x] = 0;
      }
    }
  }  

  this->createPiece();
}

void Tetris::createPiece() {
  this->piece = new Piece(rand() % 7, Tetris::WIDTH/2 - 2, 1);
}

void Tetris::placePieceOnBoard() {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (this->piece->shape[y][x] == 1) {
        int boardY = this->piece->y + y;
        int boardX = this->piece->x + x;
        if (boardY >= 0 && boardY < Tetris::HEIGHT && boardX >= 0 && boardX < Tetris::WIDTH) {
          this->board[boardY][boardX] = 1;
        }
      }
    }
  }
}

void Tetris::removePieceFromBoard() {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (this->piece->shape[y][x] == 1) {
        int boardY{this->piece->y + y};
        int boardX{this->piece->x + x};
        if (boardY >= 0 && boardY < Tetris::HEIGHT && boardX >= 0 && boardX < Tetris::WIDTH) {
          this->board[boardY][boardX] = 0;
        }
      }
    }
  } }

void Tetris::drawBoard() {
  std::cout << "\033[2J\033[1;1H"; // Clears terminal screen

  auto [shadowX, shadowY]{this->calculateShadowPosition()};
  this->drawPieceShadow(shadowX, shadowY);
  this->placePieceOnBoard();

  for (int y = 0; y < Tetris::HEIGHT; y++) {
    for (int x = 0; x < Tetris::WIDTH; x++) {
      if (this->board[y][x] == 1) {
        std::cout << "#";
      } else if (this->board[y][x] == 2) {
        std::cout << "+";
      } else {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }
  this->removePieceFromBoard();
  this->removePieceShadow(shadowX, shadowY);
}

bool Tetris::canRotate(const std::array<std::array<int, 4>, 4>& rotatedPiece) const {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (rotatedPiece[y][x] == 1) {
        int boardx{this->piece->x + x};
        int boardy{this->piece->y + y};
        if (boardy < 0 || boardy >= Tetris::HEIGHT ||
          boardx < 0 || boardx >= Tetris::WIDTH || 
          this->board[boardy][boardx] == 1)
          return false;
      }
    }
  }

  return true;
}

void Tetris::rotate() {
  std::array<std::array<int, 4>, 4> rotated;

  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      rotated[x][3 - y] = this->piece->shape[y][x];
    }
  }

  if (canRotate(rotated)) {
    this->piece->shape = rotated;
  }
}

bool Tetris::collided(int offx, int offy) {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (this->piece->shape[y][x] == 1) {
        int px{this->piece->x};
        int py{this->piece->y};
        if (this->board[py + y + offy][px + x + offx] == 1) 
          return true;
      }
    }
  }
  return false;
}

void Tetris::lockPiece() {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      int px{this->piece->x};
      int py{this->piece->y};
      if (this->piece->shape[y][x] == 1) {
        this->board[py + y][px + x] = 1;
      }
    }
  }
}

void Tetris::movePiece(int dx, int dy) {
  if (!collided(dx, dy)) {
    this->piece->x += dx;
    this->piece->y += dy;
  } else if (dy > 0) { // Case when piece collided with last row
    lockPiece();
    delete this->piece;
    this->createPiece();
  }
}

void Tetris::run() {
  this->drawBoard();
  char key;
  while (!this->gameOver) {
    std::cin >> key;
    switch(key) {
      case 'w': this->rotate(); break;
      case 'q': this->gameOver = !this->gameOver; break;
      case 'a': this->movePiece(-1, 0); break;
      case 'd': this->movePiece( 1, 0); break;
      case 's': this->movePiece( 0, 1); break;
    }

    if (this->gameOver) {
      delete this->piece;
      break;
    }

    this->movePiece(0, 1);
    this->drawBoard();
    sleep(1);
  }
}

std::pair<int, int> Tetris::calculateShadowPosition() {
  int sY{this->piece->y};
  int sX{this->piece->x};

  while (!this->collided(0, sY + 1 - this->piece->y))
    sY++;

  return {sX, sY};
}


void Tetris::drawPieceShadow(int shadowX, int shadowY) {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (this->piece->shape[y][x] == 1) {
        int boardY{shadowY + y};
        int boardX{shadowX + x};
        if (boardY >= 0 && boardY < Tetris::HEIGHT && boardX >= 0 && boardX < Tetris::WIDTH) {
          this->board[boardY][boardX] = 2;
        }
      }
    }
  }
}

void Tetris::removePieceShadow(int shadowX, int shadowY) {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (this->piece->shape[y][x] == 1) {
        int boardY{shadowY + y};
        int boardX{shadowX + x};
        if (boardY >= 0 && boardY < Tetris::HEIGHT && boardX >= 0 && boardX < Tetris::WIDTH) {
          this->board[boardY][boardX] = 0;
        }
      }
    }
  } 
}
