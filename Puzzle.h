#pragma once
#include "PuzzleTile.h"
#include <string>

const int maxXdiv = 20, maxYdiv = 20;


class Puzzle{
    Img Image;
    int divX, divY;
    int tileW, tileH;
    int findPiece(int cx,int cy) const;
    // void swapPieces(int a,int b);
    
    public:
    PuzzleTile puzzleTiles[maxXdiv][maxYdiv];
    
    Puzzle(const Img& Image, int dX, int dY ); // a constructor that cut the image and save the tiles
    void shuffle();
    
    void swapPieces(PuzzleTile &tile1, PuzzleTile &tile2);
    bool isSolved() const;
    void show(string ui_text, int ui_x, int ui_y) const;
};
