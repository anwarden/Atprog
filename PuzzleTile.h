#pragma once

#include <Imagine/Images.h>
#include <string>
#include <Imagine/Graphics.h>
#include <vector>


using namespace std;
using namespace Imagine;
typedef Image<Color> Img;


class PuzzleTile
{
    int correctX, correctY;
    int currentX, currentY;
    Img subImage;

public:
    PuzzleTile();
    void initTile(int cX, int cY, const Img& sub);
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
