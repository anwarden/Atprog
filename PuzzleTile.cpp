#include "PuzzleTile.h"



void PuzzleTile::initTile(int cX, int cY, const Img& sub){
    correctX=cX;
    correctY=cY;
    currentX=cX;
    currentY=cY;
    subImage= sub;

}


int PuzzleTile::getcX() const{
    return correctX;
}
int PuzzleTile::getcY() const{
    return correctY;
}
int PuzzleTile::getX () const{
    return currentX;
}
int PuzzleTile::getY () const{
    return currentY;
}
const Img& PuzzleTile::img() const{
    return subImage;
}

// setter
void PuzzleTile::setPos(int x,int y){
    currentX=x;
    currentY=y;
}

void PuzzleTile::displayImage(){
    display(subImage, currentX, currentY);
}
bool PuzzleTile::isCorrect() const{
    return currentX==correctX && currentY==correctY;
}
