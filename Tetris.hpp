#ifndef TETRIS_HPP
#define TETRIS_HPP


// TODO: Arrumar a funçao drawBoard(), para imprimir 0 -> " " e 1 -> "#" 
// TODO: Configurar o tabuleiro para bordas com 1 e interior 0

#include <array>
#include "Piece.hpp"

class Tetris {
  private:
    // Constants
    static constexpr int HEIGHT = 20; 
    static constexpr int WIDTH = 20; 

    std::array<std::array<int, Tetris::WIDTH>, Tetris::HEIGHT> board;
    Piece* piece;
    bool gameOver;
    int fps;
    int score;

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

    void createPiece();
};
#endif // TETRIS_HPP
