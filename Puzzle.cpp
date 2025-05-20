// Puzzle.cpp — version nettoyée et fonctionnelle
// -------------------------------------------------
//  • Mélange Fisher‑Yates correct (uniforme, sans doublons ni cases vides)
//  • Affichage complet dès la création de l'objet
//  • Implémentations minimales de findPiece / swapPieces / isSolved
//  • En‑têtes manquants ajoutés

#include "Puzzle.h"
#include <algorithm>   // std::swap
#include <cstdlib>     // std::rand, std::srand
#include <ctime>       // std::time

//-------------------------------------------------------------------------
// Constructeur : découpe l'image, crée chaque tuile, puis mélange
//-------------------------------------------------------------------------
Puzzle::Puzzle(const Img& img, int dX, int dY)
    : Image(img), divX(dX), divY(dY) {

    tileW = img.width()  / divX;
    tileH = img.height() / divY;

    for (int col = 0; col < divX; ++col)
        for (int row = 0; row < divY; ++row) {
            Img sub = img.getSubImage(col * tileW,   // x (pixels)
                                      row * tileH,   // y (pixels)
                                      tileW, tileH);
            puzzleTiles[col][row].initTile(col, row, sub);
        }
    shuffle();   // l'objet est prêt‑à‑jouer dès sa construction
}

//-------------------------------------------------------------------------
// Fisher–Yates : mélange uniforme des indices 0 … nTiles‑1
//-------------------------------------------------------------------------
void Puzzle::shuffle() {
    const int total = divX * divY;

    int idx[maxXdiv * maxYdiv];           // tableau temporaire d'indices
    for (int i = 0; i < total; ++i)
        idx[i] = i;

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = total - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);
        std::swap(idx[i], idx[j]);
    }

    // On place chaque tuile mélangée à sa destination et on met à jour ses coords
    for (int n = 0; n < total; ++n) {
        int dstCol = n % divX;      // colonne destination
        int dstRow = n / divX;      // ligne destination

        int linSrc = idx[n];        // index linéaire mélangé
        int srcCol = linSrc % divX;
        int srcRow = linSrc / divX;

        std::swap(puzzleTiles[srcCol][srcRow],
                  puzzleTiles[dstCol][dstRow]);

        // mise à jour des positions courantes des deux tuiles échangées
        puzzleTiles[dstCol][dstRow].setPos(dstCol, dstRow);
        puzzleTiles[srcCol][srcRow].setPos(srcCol, srcRow);
    }
}

//-------------------------------------------------------------------------
// Dessine chaque tuile à sa position courante
//-------------------------------------------------------------------------
void Puzzle::show() const {
    clearWindow();
    for (int col = 0; col < divX; ++col)
        for (int row = 0; row < divY; ++row) {
            const PuzzleTile& t = puzzleTiles[col][row];
            display(t.img(), t.getX() * tileW, t.getY() * tileH);
        }
}

//-------------------------------------------------------------------------
// Retourne l'indice linéaire (row * divX + col) de la tuile située en (cx,cy)
//-------------------------------------------------------------------------
int Puzzle::findPiece(int cx, int cy) const {
    for (int col = 0; col < divX; ++col)
        for (int row = 0; row < divY; ++row)
            if (puzzleTiles[col][row].getX() == cx &&
                puzzleTiles[col][row].getY() == cy)
                return row * divX + col;
    return -1;
}

//-------------------------------------------------------------------------
// Échange deux tuiles désignées par leurs indices linéaires
//-------------------------------------------------------------------------
void Puzzle::swapPieces(int a, int b) {
    if (a == b) return;
    int colA = a % divX, rowA = a / divX;
    int colB = b % divX, rowB = b / divX;

    std::swap(puzzleTiles[colA][rowA], puzzleTiles[colB][rowB]);
    puzzleTiles[colA][rowA].setPos(colA, rowA);
    puzzleTiles[colB][rowB].setPos(colB, rowB);
}

//-------------------------------------------------------------------------
// Le puzzle est-il résolu ?
//-------------------------------------------------------------------------
bool Puzzle::isSolved() const {
    for (int col = 0; col < divX; ++col)
        for (int row = 0; row < divY; ++row)
            if (!puzzleTiles[col][row].isCorrect())
                return false;
    return true;
}
