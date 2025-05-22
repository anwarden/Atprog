#include "PuzzlePiece.h"

PuzzlePiece::PuzzlePiece()
    : correctX(0), correctY(0){}

void PuzzlePiece::initPiece(int cX, int cY, const Img& sub){
    correctX=cX;
    correctY=cY;
    subImage= sub;
}


int PuzzlePiece::getcX() const{
    return correctX;
}
int PuzzlePiece::getcY() const{
    return correctY;
}

Img PuzzlePiece::getImg() const{
    return subImage;
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