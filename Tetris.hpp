#ifndef TETRIS_HPP
#define TETRIS_HPP

#include <array>
#include <memory>

#include "Piece.hpp"

class Tetris {
  private:
    // Constants
    static constexpr int HEIGHT = 22; 
    static constexpr int WIDTH = 16; 

    std::array<std::array<int, Tetris::WIDTH>, Tetris::HEIGHT> board;
    std::unique_ptr<Piece> piece;
    bool gameOver;
    int fps;
    int score;
    
    int getch();
  public:
    Tetris();
    void drawBoard();
    void drawPiece();
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
    
    void softDrop();
    void hardDrop();
    void clearFullRows();
    void pullBlocksDown(int startRow);
    std::pair<int, int> calculateShadowPosition();

    void createPiece();
};
#endif // TETRIS_HPP
