#pragma once
#include "PuzzleTile.h"

const int maxXdiv = 20, maxYdiv = 20;


class Puzzle{
    Img Image;
    int divX, divY;
    int tileW, tileH;
    PuzzleTile puzzleTiles[maxXdiv][maxYdiv];
    int findPiece(int cx,int cy) const;
    void swapPieces(int a,int b);
    bool isSolved() const;
public:
    Puzzle(Img Image, int dX, int dY ); // a constructor that cut the image and save the tiles
    void shuffle();
    void show() const;
    void userClick(int px,int py);
    void displayPuzzle();
};
