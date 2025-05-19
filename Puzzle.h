#pragma once
#include <Imagine/Images.h>
#include <string>
#include <Imagine/Graphics.h>
#include <vector>


using namespace std;
using namespace Imagine;
typedef Image<Color> Img;

const int maxXdiv = 20, maxYdiv = 20;

//-----------------------------------------------------------------
//  Une tuile : position correcte  (goalX, goalY)
//              position courante (curX, curY)
//              image découpée    (tile)
//-----------------------------------------------------------------
class PuzzleTile
{
    int correctX, correctY;
    int X, Y;
    Img subImage;

public:
    PuzzleTile(int cX, int cY, int X, int Y, const Img& sub);
    //getter
    int getcX() const;
    int getcY() const;
    int getX () const;
    int getY () const;
    const Img& img() const;
    int getInitPos();
    int getnewPos();

    // setter
    void setPos(int x,int y);

    void displayImage();
    bool isCorrect() const;
};


class Puzzle{
    Img Image;
    int divX, divY;
    int tileW, tileH;
    PuzzleTile puzzleTiles[maxXdiv*maxYdiv];
    int findPiece(int cx,int cy) const;
    void swapPieces(int a,int b);
    bool isSolved() const;
public:
    Puzzle(Img Image, int dX, int dY ); // a constructor that cut the image and save the tiles
    void shuffle();
    void display() const;
    void userClick(int px,int py);
    void displayPuzzle();
};
