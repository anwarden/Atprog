#include "Puzzle.h"
#include "PuzzleTile.h"



Puzzle::Puzzle(Img img, int dX, int dY ){
    Image = img;
    divX = dX;
    divY = dY;
    tileW = img.width()/dX;
    tileH = img.height()/dY;

    for(int i=0; i<divX; i++){
        for(int j=0; j<divY; j++){
            Img sub=img.getSubImage(i*divX,j*divY,tileW,tileH);
            puzzleTiles[i][j].initTile(i,j,sub);
        }
    }
    shuffle();
}

// To shuffle the tiles position randomly, we use the Fischer-Yates method
void Puzzle::shuffle(){
    int idx[maxXdiv*maxYdiv];
    for(int i=0;i<divX*divY;++i) idx[i]=i;

    srand(static_cast<unsigned>(time(nullptr)));//To make sure at every second we have a different seed

    for(int i=divX*divY-1;i>0;--i){
        int j = rand()%(i+1);
        swap(idx[i],idx[j]);
    }
    // Set the tiles with the current positions
    for(int k=0;k<divX;++k){
        for(int l=0;l<divY; l++){
            int currX = k%divX, currY = l/divX;
            puzzleTiles[idx[k]][idx[l]].setPos(currX,currY);
        }
    }
}
//-----------------------------------------------------------------
//  Dessin : chaque tuile à sa position courante
//-----------------------------------------------------------------
void Puzzle::show() const{
    clearWindow();
    for(int k=0;k<divX;++k){
        for(int l=0;l<divY; l++){
            const PuzzleTile& p = puzzleTiles[k][l];
            display(p.img(), p.getX()*tileW, p.getY()*tileH);
        }
    }
}
void Puzzle::userClick(int px,int py){

}
void Puzzle::displayPuzzle(){

}

int Puzzle::findPiece(int cx,int cy) const{

}
void Puzzle::swapPieces(int a,int b){

}
bool Puzzle::isSolved() const{

}
