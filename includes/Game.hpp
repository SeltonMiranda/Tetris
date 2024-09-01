#pragma once

// System includes
#include <queue>

// Personal includes
#include "./Piece.hpp"
#include "./TetrisTypes.hpp"

namespace Tetris {
class Game {
  private:
    Tetris::Board board;
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
    const std::pair<int, int> getsTerminalSize() const; 

    // Gets the input from stdin
    int getch() const;

    // Checks if it's the fence of board
    bool isFence(const int x, const int y) const;

    // Shows the player's score when quit or lost
    void showScore() const;

    Tetris::Board& getBoard();
    
    // Checks if it's within grid board
    bool isInBoard(const int x, const int y) const;

    // Checks if it's a block
    bool isABlock(const int pos) const;

    // Checks if it's a blank space, i.e, == 0
    bool isBlankSpace(const int pos) const;

    // Rotates the block
    void rotate();

    // Moves block down
    void softDrop();

    // Places block at last possible row
    void hardDrop() const;

    // Clear rows that aren't fully blank space
    void clearFullRows();

    // Pull blocks that aren't in a full row
    void pullBlocksDown(const int startRow);

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

    bool collided(const int offx, const int offy) const;
    void movePiece(const int dx, const int dy);

    // Stamps block on board
    void lockPiece();

    // Renders block shadow
    void drawPieceShadow(const int shadowX, const int shadowY);

    // Removes block shadow
    void removePieceShadow(const int shadowX, const int shadowY);

    // Returns the coordinates of a block shadow
    const std::pair<int, int> calculateShadowPosition() const;
};
}
