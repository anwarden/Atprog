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
            PuzzlePieces[col][row].initPiece(col, row, sub);
        }
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

        swap(PuzzlePieces[srcCol][srcRow],
                  PuzzlePieces[dstCol][dstRow]);

        // mise à jour des positions courantes des deux tuiles échangées
        PuzzlePieces[dstCol][dstRow].setPos(dstCol, dstRow);
        PuzzlePieces[srcCol][srcRow].setPos(srcCol, srcRow);
    }
}


// Displaying tiles at their current positions
void Puzzle::show(string ui_text, int ui_x, int ui_y) const {
    const int x_decal = 1, y_decal = 1;
    const int x_margin = 1, y_margin = 1;
    clearWindow();
    for (int col = 0; col < divX; ++col)
        for (int row = 0; row < divY; ++row) {
            PuzzlePiece t = PuzzlePieces[col][row];
            display(t.getImg(), t.getX()*(x_margin + tileW)+x_margin, t.getY()*(y_margin+tileH)+y_margin);
        }
    drawString(ui_x, ui_y, ui_text, BLACK, 18, 0, false, true);
}


PuzzlePiece& Puzzle::getPiece(int row, int col)
{
    return PuzzlePieces[row][col];
}


void Puzzle::swapPieces(PuzzlePiece &piece1, PuzzlePiece &piece2)
{
    PuzzlePiece temp;
    temp.initPiece(piece1.getcX(), piece1.getcY(), piece1.getImg());
    temp.setPos(piece1.getX(), piece1.getY());

    //piece1.setcPos(piece2.getcX(), piece2.getcY());
    piece1.setPos(piece2.getX(), piece2.getY());
    piece1.setImg(piece2.getImg());

    //piece2.setcPos(temp.getcX(), temp.getcY());
    piece2.setPos(temp.getX(), temp.getY());
    piece2.setImg(temp.getImg());
}

// checking if the puzzle is solved
bool Puzzle::isSolved() const {
    for (int col = 0; col < divX; ++col)
        for (int row = 0; row < divY; ++row)
            if (!PuzzlePieces[col][row].isCorrect())
                return false;
    return true;
}
