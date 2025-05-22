#include "PuzzlePiece.h"

PuzzlePiece::PuzzlePiece()
    : correctX(0), correctY(0), currentX(0), currentY(0) {}


void PuzzlePiece::initPiece(int cX, int cY, const Img& sub){
    correctX=cX;
    correctY=cY;
    currentX=cX;
    currentY=cY;
    subImage= sub;

}


int PuzzlePiece::getcX() const{
    return correctX;
}
int PuzzlePiece::getcY() const{
    return correctY;
}
int PuzzlePiece::getX () const{
    return currentX;
}
int PuzzlePiece::getY () const{
    return currentY;
}
Img PuzzlePiece::getImg() const{
    return subImage;
}

// setter
void PuzzlePiece::setPos(int x,int y){
    currentX=x;
    currentY=y;
}
// setter
void PuzzlePiece::setcPos(int x,int y){
    correctX=x;
    correctY=y;
}
// setter
void PuzzlePiece::setImg(Img img){
    subImage = img;
}

void PuzzlePiece::displayImage(){
    display(subImage, currentX, currentY);
}
bool PuzzlePiece::isCorrect() const{
    return currentX==correctX && currentY==correctY;
}
