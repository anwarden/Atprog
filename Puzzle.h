#pragma once
#include "PuzzlePiece.h"
#include <string>

const int maxXdiv = 20, maxYdiv = 20;

class Puzzle{
    Img Image;
    int divX, divY;
    int tileW, tileH;
    int findPiece(int cx,int cy) const;
    PuzzlePiece PuzzlePieces[maxXdiv][maxYdiv];
    // void swapPieces(int a,int b);
    
    public:
    Puzzle(const Img& Image, int dX, int dY ); // a constructor that cut the image and save the tiles
    PuzzlePiece& getPiece(int row, int col);
    void shuffle();
    
    void swapPieces(int c1, int r1, int c2, int r2);
    bool isSolved() const;
    void show(string ui_text, int ui_x, int ui_y) const;
};
