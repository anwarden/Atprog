#include "Puzzle.h"



// Constructor: cut the image, set the tiles then shuffle the pack


Puzzle::Puzzle(const Img& img, int dX, int dY)
    : Image(img), divX(dX), divY(dY) {

    tileW = img.width()  / divX;
    tileH = img.height() / divY;

    for (int col = 0; col < divX; ++col)
        for (int row = 0; row < divY; ++row) {
            Img sub = img.getSubImage(col * tileW,   // x (pixels)
                                      row * tileH,   // y (pixels)
                                      tileW, tileH);
            puzzleTiles[col][row].initTile(col, row, sub);
        }
    shuffle();
}


// We use the Fisher-Yates method to shuffle

void Puzzle::shuffle() {
    const int total = divX * divY;

    int idx[maxXdiv * maxYdiv];
    for (int i = 0; i < total; ++i)
        idx[i] = i;

    srand(static_cast<unsigned>(std::time(nullptr)));// to make sure we have a different shuffle at every game
    for (int i = total - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);
        swap(idx[i], idx[j]);
    }

    // We put every tile at its destination and update its coordinates
    for (int n = 0; n < total; ++n) {
        int dstCol = n % divX;
        int dstRow = n / divX;

        int linSrc = idx[n];        // linear index
        int srcCol = linSrc % divX;
        int srcRow = linSrc / divX;

        swap(puzzleTiles[srcCol][srcRow],
                  puzzleTiles[dstCol][dstRow]);

        // mise à jour des positions courantes des deux tuiles échangées
        puzzleTiles[dstCol][dstRow].setPos(dstCol, dstRow);
        puzzleTiles[srcCol][srcRow].setPos(srcCol, srcRow);
    }
}


// Displaying tiles at their current positions

void Puzzle::show() const {
    clearWindow();
    for (int col = 0; col < divX; ++col)
        for (int row = 0; row < divY; ++row) {
            PuzzleTile t = puzzleTiles[col][row];
            display(t.img(), t.getX() * tileW, t.getY() * tileH);
        }
}


// Return the index (row * divX + col) of the tile in the position (cx,cy)

int Puzzle::findPiece(int cx, int cy) const {
    for (int col = 0; col < divX; ++col)
        for (int row = 0; row < divY; ++row)
            if (puzzleTiles[col][row].getX() == cx &&
                puzzleTiles[col][row].getY() == cy)
                return row * divX + col;
    return -1;
}


// swaping two tiles

void Puzzle::swapPieces(int a, int b) {
    if (a == b) return;
    int colA = a % divX, rowA = a / divX;
    int colB = b % divX, rowB = b / divX;

    swap(puzzleTiles[colA][rowA], puzzleTiles[colB][rowB]);
    puzzleTiles[colA][rowA].setPos(colA, rowA);
    puzzleTiles[colB][rowB].setPos(colB, rowB);
}


// checking if the puzzle is solved

bool Puzzle::isSolved() const {
    for (int col = 0; col < divX; ++col)
        for (int row = 0; row < divY; ++row)
            if (!puzzleTiles[col][row].isCorrect())
                return false;
    return true;
}
