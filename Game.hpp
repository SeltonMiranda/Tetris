#pragma once

#include <array>
#include <memory>
#include <queue>

#include "Piece.hpp"
#include "Constants.hpp"

namespace Tetris {
class Game {
  private:
    std::array<std::array<int, Tetris::Constants::WIDTH>, Tetris::Constants::HEIGHT> board;
    std::unique_ptr<Piece> piece;
    std::queue<std::unique_ptr<Piece>> blocks;
    bool gameOver;
    int fps;
    int score;
    int termWidth;
    int termHeight;

    // Creates a new block
    void startPiece();
    
    // Returns rows and columns, respectively, from terminal size
    std::pair<int, int> getsTerminalSize() const; 

    // Gets the input from stdin
    int getch() const;

    // Shows the player's score when quit or lost
    void showScore() const;
    
    // Checks if it's within grid board
    bool isInBoard(int x, int y) const;

    // Checks if it's a block
    bool isABlock(int pos) const;

    // Checks if it's a blank space, i.e, == 0
    bool isBlankSpace(int pos) const;

    // Rotates the block
    void rotate();

    // Moves block down
    void softDrop();

    // Places block at last possible row
    void hardDrop();

    // Clear rows that aren't fully blank space
    void clearFullRows();

    // Pull blocks that aren't in a full row
    void pullBlocksDown(int startRow);

  public:
    // Constructor
    Game();
    
    // Destructor
    virtual ~Game() = default;

    // Render the board
    void drawBoard();

    // Render block in board
    void placePieceOnBoard();

    // Removes block from board
    void removePieceFromBoard();

    // Game loop
    void run();

    bool collided(int offx, int offy);
    void movePiece(int dx, int dy);

    // Stamps block on board
    void lockPiece();

    // Renders block shadow
    void drawPieceShadow(int shadowX, int shadowY);

    // Removes block shadow
    void removePieceShadow(int shadowX, int shadowY);

    // Returns the coordinates of a block shadow
    std::pair<int, int> calculateShadowPosition();
    
};
}
