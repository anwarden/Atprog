#include "Puzzle.h"

// Constructor: cut the image, set the tiles then shuffle the pack
Puzzle::Puzzle(const Img &img, int dX, int dY)
    : Image(img), divX(dX), divY(dY)
{

    tileW = img.width() / divX;
    tileH = img.height() / divY;

    for (int col = 0; col < divX; ++col)
        for (int row = 0; row < divY; ++row)
        {
            Img sub = img.getSubImage(col * tileW, // x (pixels)
                                      row * tileH, // y (pixels)
                                      tileW, tileH);
            PuzzlePieces[col][row].initPiece(col, row, sub);
        }
}

// We use the Fisher-Yates method to shuffle
void Puzzle::shuffle()
{
    const int total = divX * divY;

    int idx[maxXdiv * maxYdiv];
    for (int i = 0; i < total; ++i)
        idx[i] = i;

    srand(static_cast<unsigned>(std::time(nullptr))); // to make sure we have a different shuffle at every game
    for (int i = total - 1; i > 0; --i)
    {
        int j = std::rand() % (i + 1);
        swap(idx[i], idx[j]);
    }

    //  We put every tile at its destination and update its coordinates
    for (int n = 0; n < total; ++n)
    {
        int dstCol = n % divX;
        int dstRow = n / divX;

        int linSrc = idx[n]; // linear index
        int srcCol = linSrc % divX;
        int srcRow = linSrc / divX;

        swap(PuzzlePieces[srcCol][srcRow],
             PuzzlePieces[dstCol][dstRow]);

        // // mise à jour des positions courantes des deux tuiles échangées
        // PuzzlePieces[dstCol][dstRow].setPos(dstCol, dstRow);
        // PuzzlePieces[srcCol][srcRow].setPos(srcCol, srcRow);
    }
}

// Displaying tiles at their current positions
void Puzzle::show(string ui_text, int ui_x, int ui_y) const
{
    const int x_decal = 1, y_decal = 1;
    const int x_margin = 1, y_margin = 1;
    clearWindow();
    ::Image<Color> gamemenu;
    load(gamemenu, srcPath("gamemenu.png"));
    display(gamemenu,   0,   0);
    for (int col = 0; col < divX; ++col)
        for (int row = 0; row < divY; ++row)
        {
            PuzzlePiece t = PuzzlePieces[col][row];
            display(t.getImg(), col * (x_margin + tileW) + x_margin, row * (y_margin + tileH) + y_margin);
        }
    drawString(ui_x, ui_y, ui_text, WHITE, 27, 0, false, true);
}

PuzzlePiece &Puzzle::getPiece(int row, int col)
{
    return PuzzlePieces[row][col];
}

void Puzzle::swapPieces(int c1, int r1, int c2, int r2)
{
    swap(PuzzlePieces[c1][r1],
         PuzzlePieces[c2][r2]);
}

// checking if the puzzle is solved
bool Puzzle::isSolved() const
{
    for (int col = 0; col < divX; ++col)
        for (int row = 0; row < divY; ++row)
            if (!(PuzzlePieces[col][row].getcX() == col && PuzzlePieces[col][row].getcY() == row))
                return false;
    return true;
}
