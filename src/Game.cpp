// System includes
#include <iostream>
#include <stdexcept>
#include <termios.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

// Personal includes
#include "../includes/Game.hpp"
#include "../includes/Constants.hpp"
#include "../includes/Piece.hpp"

namespace Tetris {

Game::Game() : gameOver{false}, fps{60}, score{0} {
  auto [rows, cols] = this->getsTerminalSize();
  this->termWidth = cols;
  this->termHeight = rows;

  std::cout << Tetris::Constants::HIDECURSOR;

  for (int y = 0; y < Constants::HEIGHT; y++) {
    for (int x = 0; x < Constants::WIDTH; x++) {
      if (this->isFence(x, y)) {
        this->getBoard().at(y).at(x) = 1;
      } else {
        this->getBoard().at(y).at(x) = 0;
      }
    }
  }  
  this->startPiece();
}

void Game::startPiece() {
  while (this->blocks.size() < 5) {
    int type;

    do {
      type = rand() % Tetris::Constants::TYPES;
    } while (!this->blocks.empty() && type == this->blocks.back()->getType());

    this->blocks.push(Tetris::Piece::createPiece(type, Tetris::Constants::WIDTH/2 - 2, 1));
  }

  this->piece = std::move(this->blocks.front());
  this->blocks.pop();

  if (this->collided(0, 0)) { // If it spawns and already collided it's game over
    this->gameOver = !this->gameOver;
    this->showScore();
  } 
}

bool Game::isFence(const int x, const int y) const {
  return x == 0 || x == Tetris::Constants::WIDTH - 1 || y == 0 || y == Tetris::Constants::HEIGHT - 1;
}

bool Game::isABlock(const int pos) const { return 2 <= pos && pos <= 8; }

void Game::rotate() { this->piece->rotate(this->board); }

bool Game::isBlankSpace(const int pos) const { return pos == 0; }

bool Game::collided(const int offx, const int offy) const { return this->piece->collided(this->board, offx, offy); }

bool Game::isInBoard(const int x, const int y) const {
  return (x > 0 && x < Tetris::Constants::WIDTH - 1 && y > 0 && y < Tetris::Constants::HEIGHT - 1);
}

Tetris::Board& Game::getBoard() { return this->board; }

void Game::placePieceOnBoard() {
  for (int y = 0; y < Tetris::Constants::PIECESIZE; y++) {
    for (int x = 0; x < Tetris::Constants::PIECESIZE; x++) {
      if (this->isABlock(this->piece->shape[y][x])) {
        int boardY{this->piece->getY() + y};
        int boardX{this->piece->getX() + x};

        if (this->isInBoard(boardX,  boardY))
          this->getBoard().at(boardY).at(boardX) = this->piece->getType();
      }
    }
  }
}

void Game::removePieceFromBoard() {
  for (int y = 0; y < Tetris::Constants::PIECESIZE; y++) {
    for (int x = 0; x < Tetris::Constants::PIECESIZE; x++) {
      if (this->isABlock(this->piece->getShape().at(y).at(x))) {
        int boardY{this->piece->getY() + y};
        int boardX{this->piece->getX() + x};

        if (this->isInBoard(boardX, boardY))
          this->getBoard().at(boardY).at(boardX) = 0;
      }
    }
  } 
}

void Game::drawBoard() {
  std::cout << Tetris::Constants::CLEARSCREEN; 

  auto [shadowX, shadowY]{this->calculateShadowPosition()};
  this->drawPieceShadow(shadowX, shadowY);
  this->placePieceOnBoard();

  int startX{(this->termWidth - Tetris::Constants::WIDTH) / 2};

  // Moves cursor to half terminal screen
  std::cout << "\033[" << 2 << ";" << startX << "H";

  for (int y = 0; y < Constants::HEIGHT; y++) {
    std::cout << "\033[" << (2 + y) << ";" << startX << "H";

    for (int x = 0; x < Constants::WIDTH; x++) {
      if (this->getBoard().at(y).at(x) == 1) {
        std::cout << Tetris::Constants::BLOCK;
      } else if (this->getBoard().at(y).at(x) == 9) {
        std::cout << Tetris::Constants::LIGHTGRAY;
        std::cout << Tetris::Constants::SHADOW << Tetris::Constants::RESET;
      } else if (this->isABlock(this->getBoard().at(y).at(x))) {
        this->piece->draw(this->getBoard().at(y).at(x));
      } else {
        std::cout << Tetris::Constants::EMPTY;
      }
    }
    std::cout << std::endl;
  }

  this->removePieceFromBoard();
  this->removePieceShadow(shadowX, shadowY);
}

void Game::lockPiece() {
  for (int y = 0; y < Tetris::Constants::PIECESIZE; y++) {
    for (int x = 0; x < Tetris::Constants::PIECESIZE; x++) {

      int px{this->piece->getX()};
      int py{this->piece->getY()};

      if (this->isABlock(this->piece->getShape().at(y).at(x))) 
        this->getBoard().at(py + y).at(px + x) = this->piece->getType();
    }
  }
}

void Game::movePiece(const int dx, const int dy) {
  if (!this->collided(dx, dy)) {
    *this->piece += std::make_pair(dx, dy);
  } else if (dy > 0) { // Case when piece collided with last row
    lockPiece();
    this->startPiece();
  }
}

void Game::softDrop() { this->movePiece(0, 1); }

void Game::hardDrop() const { 
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
      case 'q': this->gameOver = !this->gameOver; break;
    }

    if (this->gameOver) {
      this->showScore();
      break;
    }

    this->clearFullRows();
    this->movePiece(0, 1);
    this->drawBoard();
    usleep(3500 * 1000 / (this->fps / 10));
  }
}

const std::pair<int, int> Game::calculateShadowPosition() const {
  int sY{this->piece->getY()};
  int sX{this->piece->getX()};

  while (!this->collided(0, sY + 1 - this->piece->getY())) sY++;
  return {sX, sY};
}


void Game::drawPieceShadow(const int shadowX, const int shadowY) {
  for (int y = 0; y < Tetris::Constants::PIECESIZE; y++) {
    for (int x = 0; x < Tetris::Constants::PIECESIZE; x++) {
      if (this->isABlock(this->piece->getShape().at(y).at(x))) {
        int boardY{shadowY + y};
        int boardX{shadowX + x};
        if (this->isInBoard(boardX, boardY)) this->getBoard().at(boardY).at(boardX) = 9;
      }
    }
  }
}

void Game::removePieceShadow(const int shadowX, const int shadowY) {
  for (int y = 0; y < Tetris::Constants::PIECESIZE; y++) {
    for (int x = 0; x < Tetris::Constants::PIECESIZE; x++) {
      if (this->isABlock(this->piece->getShape().at(y).at(x))) {
        int boardY{shadowY + y};
        int boardX{shadowX + x};
        if (this->isInBoard(boardX, boardY)) this->getBoard().at(boardY).at(boardX) = 0;
      }
    }
  } 
}

void Game::pullBlocksDown(const int startRow) {
  for (int y = startRow; y > 0; y--) {
    for (int x = 1; x <= Constants::WIDTH - 2; x++) {
      if (this->isABlock(this->getBoard().at(y).at(x))) {
        this->getBoard().at(y + 1).at(x) = this->getBoard().at(y).at(x);
        this->getBoard().at(y).at(x) = 0;
      }
    }
  } 
}

void Game::clearFullRows() {
  for (int y = Constants::HEIGHT - 2; y > 0; y--) {
    bool full{true};
    for (int x = 1; x < Constants::WIDTH - 2; x++) {
      if (this->isBlankSpace(this->getBoard().at(y).at(x))) {
        full = false;
        break;
      }
    }

    if (full) {
      // Erase the blocks which are in a full row
      for (int x = 1; x <= Constants::WIDTH - 2; x++)
        this->getBoard().at(y).at(x) = 0;
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

const std::pair<int, int> Game::getsTerminalSize() const {
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

  // Minimun number of characters for non-blocking read
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
