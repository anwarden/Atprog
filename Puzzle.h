#pragma once

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
    int puzzleItems[divsX*divsY];
};
