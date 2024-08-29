#pragma once

#include <array>
#include <memory>

#include "Piece.hpp"
#include "Constants.hpp"

namespace Tetris {
class Game {
  private:
    std::array<std::array<int, Constants::WIDTH>,
      Constants::HEIGHT> board;
    std::unique_ptr<Piece> piece;
    bool gameOver;
    int fps;
    int score;
    
    int getch();
    void showScore() const;
  public:
    Game();
    void drawBoard();
    void placePieceOnBoard();
    void removePieceFromBoard();

    bool canRotate(const std::array<std::array<int, 4>, 4>& rotatedPiece) const;
    void rotate();
    void run();
    bool collided(int offx, int offy);
    void movePiece(int dx, int dy);
    void lockPiece();

    void drawPieceShadow(int shadowX, int shadowY);
    void removePieceShadow(int shadowX, int shadowY);
    std::pair<int, int> calculateShadowPosition();
    
    void softDrop();
    void hardDrop();
    void clearFullRows();
    void pullBlocksDown(int startRow);

    void startPiece();
};
}
