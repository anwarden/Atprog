#pragma once

const int maxXdiv = 20, maxYdiv = 20;

class PuzzleItem
{
    int initX, initY;
    int newX, newY;
public:
    PuzzleItem(int initX, int initY, int newX, int newY);
    int getInitPos();
    int getnewPos();
    void displayImage();

};

class Puzzle{
    int divsX, divsY;
    int puzzleItems[maxXdiv*maxYdiv];
public:
    Puzzle(int divX, int divY);
    void displayPuzzle();
};
