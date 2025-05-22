#pragma once

#include <Imagine/Images.h>
#include <string>
#include <Imagine/Graphics.h>
#include <vector>


using namespace std;
using namespace Imagine;
typedef Image<Color> Img;


class PuzzlePiece
{
    int correctX, correctY;
    int currentX, currentY;
    Img subImage;

public:
    PuzzlePiece();
    void initPiece(int cX, int cY, const Img& sub);
    //getter
    int getcX() const;
    int getcY() const;
    int getX () const;
    int getY () const;
    Img getImg() const;

    // setter
    void setPos(int x,int y);
    void setcPos(int x, int y);
    void setImg(Img img);

    void displayImage();
    bool isCorrect() const;
};