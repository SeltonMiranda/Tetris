#include <asm-generic/ioctls.h>
#include <iostream>
#include <stdexcept>
#include <termios.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include "Game.hpp"
#include "Constants.hpp"

namespace Tetris {

Game::Game() : gameOver{false}, fps{60}, score{0} {
  auto [rows, cols] = this->getsTerminalSize();
  this->termWidth = rows;
  this->termHeight = cols;

  std::cout << Tetris::Constants::HIDECURSOR;

  for (int y = 0; y < Constants::HEIGHT; y++) {
    for (int x = 0; x < Constants::WIDTH; x++) {
      if (y == 0 || y == Constants::HEIGHT - 1 ||
        x == 0 || x == Constants::WIDTH  - 1 ) {
        this->board[y][x] = 1;
      } else {
        this->board[y][x] = 0;
      }
    }
  }  
  this->startPiece();
}

void Game::startPiece() {
  this->piece = Tetris::Piece::createPiece(rand() % 7, Tetris::Constants::WIDTH/2 - 2, 1);
  if (this->collided(0, 0)) this->gameOver = !this->gameOver;
}

bool Game::isABlock(int pos) const { return 2 <= pos && pos <= 8; }

void Game::rotate() { this->piece->rotate(this->board); }

bool Game::isBlankSpace(int pos) const { return pos == 0; }

bool Game::isInBoard(int x, int y) const {
  return (x > 0 && x < Tetris::Constants::WIDTH - 1 && y > 0 && y < Tetris::Constants::HEIGHT - 1);
}

void Game::placePieceOnBoard() {
  for (int y = 0; y < Tetris::Constants::PIECESIZE; y++) {
    for (int x = 0; x < Tetris::Constants::PIECESIZE; x++) {
      if (this->isABlock(this->piece->shape[y][x])) {
        int boardY{this->piece->getY() + y};
        int boardX{this->piece->getX() + x};
        if (this->isInBoard(boardX,  boardY)) this->board.at(boardY).at(boardX) = this->piece->getType();
      }
    }
  }
}

void Game::removePieceFromBoard() {
  for (int y = 0; y < Tetris::Constants::PIECESIZE; y++) {
    for (int x = 0; x < Tetris::Constants::PIECESIZE; x++) {
      if (this->isABlock(this->piece->shape[y][x])) {
        int boardY{this->piece->getY() + y};
        int boardX{this->piece->getX() + x};

        if (this->isInBoard(boardX, boardY)) this->board[boardY][boardX] = 0;
      }
    }
  } 
}

void Game::drawBoard() {
  std::cout << Tetris::Constants::CLEARSCREEN; 

  auto [shadowX, shadowY]{this->calculateShadowPosition()};
  this->drawPieceShadow(shadowX, shadowY);
  this->placePieceOnBoard();

  int startX{this->termWidth  / 2 + Tetris::Constants::WIDTH};
  int startY{this->termHeight / 2 + Tetris::Constants::HEIGHT};

  // Moves cursor to half terminal screen
  std::cout << "\033[" << startY << ";" << startX << "H";

  for (int y = 0; y < Constants::HEIGHT; y++) {
    std::cout << "\033[" << (startY + y) << ";" << startX << "H";

    for (int x = 0; x < Constants::WIDTH; x++) {
      if (this->board[y][x] == 1) {
        std::cout << "#";
      } else if (this->board[y][x] == 9) {
        std::cout << Tetris::Constants::LIGHTGRAY;
        std::cout << "+" << Tetris::Constants::RESET;
      } else if (this->isABlock(this->board[y][x])) {
        this->piece->draw(this->board[y][x]);
      } else {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }

  this->removePieceFromBoard();
  this->removePieceShadow(shadowX, shadowY);
}

bool Game::collided(int offx, int offy) {
  for (int y = 0; y < Tetris::Constants::PIECESIZE; y++) {
    for (int x = 0; x < Tetris::Constants::PIECESIZE; x++) {
      if (this->isABlock(this->piece->shape[y][x])) {
        int px{this->piece->getX() + x + offx};
        int py{this->piece->getY() + y + offy};

        if (!this->isInBoard(px, py)) return true;
        if (!this->isBlankSpace(this->board[py][px])) return true;
      }
    }
  }
  return false;
}

void Game::lockPiece() {
  for (int y = 0; y < Tetris::Constants::PIECESIZE; y++) {
    for (int x = 0; x < Tetris::Constants::PIECESIZE; x++) {

      int px{this->piece->getX()};
      int py{this->piece->getY()};

      if (this->isABlock(this->piece->shape[y][x])) 
        this->board[py + y][px + x] = this->piece->getType();
    }
  }
}

void Game::movePiece(int dx, int dy) {
  if (!collided(dx, dy)) {
    *this->piece += std::make_pair(dx, dy);
  } else if (dy > 0) { // Case when piece collided with last row
    lockPiece();
    this->startPiece();
  }
}

void Game::softDrop() { this->movePiece(0, 1); }

void Game::hardDrop() { 
  auto [shadowX, shadowY]{this->calculateShadowPosition()};
  this->piece->setX(shadowX);
  this->piece->setY(shadowY);
}

void Game::run() {
  this->drawBoard();
  char key;
  while (!this->gameOver) {
    key = this->getch();
    switch(key) {
      case 'w': this->rotate(); break;
      case 'a': this->movePiece(-1, 0); break;
      case 's': this->softDrop(); break;
      case 'd': this->movePiece( 1, 0); break;
      case 'e': this->hardDrop(); break;
      case 'q': this->gameOver = !this->gameOver;
        this->showScore();
      break;
    }

    if (this->gameOver) {
      break;
    }

    this->clearFullRows();
    this->movePiece(0, 1);
    this->drawBoard();
    usleep(4000 * 1000 / (this->fps / 10));
  }
}

std::pair<int, int> Game::calculateShadowPosition() {
  int sY{this->piece->getY()};
  int sX{this->piece->getX()};

  while (!this->collided(0, sY + 1 - this->piece->getY())) sY++;
  return {sX, sY};
}


void Game::drawPieceShadow(int shadowX, int shadowY) {
  for (int y = 0; y < Tetris::Constants::PIECESIZE; y++) {
    for (int x = 0; x < Tetris::Constants::PIECESIZE; x++) {
      if (this->isABlock(this->piece->shape[y][x])) {
        int boardY{shadowY + y};
        int boardX{shadowX + x};
        if (this->isInBoard(boardX, boardY)) this->board[boardY][boardX] = 9;
      }
    }
  }
}

void Game::removePieceShadow(int shadowX, int shadowY) {
  for (int y = 0; y < Tetris::Constants::PIECESIZE; y++) {
    for (int x = 0; x < Tetris::Constants::PIECESIZE; x++) {
      if (this->isABlock(this->piece->shape[y][x])) {
        int boardY{shadowY + y};
        int boardX{shadowX + x};
        if (this->isInBoard(boardX, boardY)) this->board[boardY][boardX] = 0;
      }
    }
  } 
}

void Game::pullBlocksDown(int startRow) {
  for (int y = startRow; y > 0; y--) {
    for (int x = 1; x <= Constants::WIDTH - 2; x++) {
      if (this->isABlock(this->board[y][x])) {
        this->board[y + 1][x] = this->board[y][x];
        this->board[y][x] = 0;
      }
    }
  } 
}

void Game::clearFullRows() {
  for (int y = Constants::HEIGHT - 2; y > 0; y--) {
    bool full{true};
    for (int x = 1; x < Constants::WIDTH - 2; x++) {
      if (this->isBlankSpace(this->board[y][x])) {
        full = false;
        break;
      }
    }

    if (full) {
      // Erase the blocks which are in a full row
      for (int x = 1; x <= Constants::WIDTH - 2; x++)
        this->board[y][x] = 0;
      this->pullBlocksDown(y);
      this->score += 100;
    }
  }
}

void Game::showScore() const {
  std::cout << Tetris::Constants::CLEARSCREEN;
  std::cout << "Your final score: " << this->score << std::endl;
  std::cout << Tetris::Constants::SHOWCURSOR;
}

std::pair<int, int> Game::getsTerminalSize() const {
  struct winsize w;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
    throw std::runtime_error{"Failed to get terminal size"};

  return {w.ws_row, w.ws_col};
}

int Game::getch() const {
  int ch;
  struct termios oldattr, newattr;

  // Save current terminal attributes
  tcgetattr(STDIN_FILENO, &oldattr);
  newattr = oldattr;

  // Set terminal to no buffer or echo mode
  newattr.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

  newattr.c_cc[VMIN] = 0;
  // Make reading non-bloking
  int oldFlags = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldFlags | O_NONBLOCK);

  // Read input
  int lastChar;
  while ((lastChar = getchar()) != EOF) {
    ch = lastChar;
  }

  // Restore old attributes
  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
  fcntl(STDIN_FILENO, F_SETFL, oldFlags);

  return ch; 
}
}
