// Imagine++ project
// Project:  Puzzler
// Student(s): Anwar Kardid, Abdeladim

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Imagine/Graphics.h>
#include <vector>

#include "PuzzleTile.h"
#include "Puzzle.h"

int w = 1000, h = 1000;

int divsX = 2, divsY = 2;
float decal = 5;
float ui_decal = 70;

Color BACKGROUND_COLOR = Color(180, 180, 180);

int displayMainMenu(int &divsX, int &divsY)
{
    clearWindow();
    fillRect(0, 0, w, h, BACKGROUND_COLOR);

    drawString(w / 2 - 150, 100, "PUZZLER", BLACK, 36, 1, 0, 1);
    drawString(w / 2 - 200, 150, "Un jeu de puzzle avec Imagine++", BLACK, 18);

    drawString(w / 2 - 100, 250, "1. Jouer", BLACK, 20);
    drawString(w / 2 - 100, 300, "2. Classement", BLACK, 20);
    drawString(w / 2 - 100, 350, "3. Quitter", BLACK, 20);

    drawString(w / 2 - 200, 450, "Appuyez sur un numéro pour choisir une option (1-3)", BLACK, 12);

    int choice = 0;
    Event e;
    do
    {
        getEvent(0, e);
        if (e.type == EVT_KEY_ON)
        {
            if (e.key >= '1' && e.key <= '3')
            {
                choice = e.key - '0';
            }
        }
    } while (choice == 0);

    // Si Jouer, demander la difficulté
    if (choice == 1)
    {
        clearWindow();
        fillRect(0, 0, w, h, BACKGROUND_COLOR);
        drawString(w / 2 - 150, 100, "Choisissez la difficulté :", BLACK, 28, 1, 0, 1);
        drawString(w / 2 - 100, 200, "1. Facile (2x2)", BLACK, 20);
        drawString(w / 2 - 100, 250, "2. Moyen (3x3)", BLACK, 20);
        drawString(w / 2 - 100, 300, "3. Difficile (4x4)", BLACK, 20);
        drawString(w / 2 - 100, 350, "4. Master (6x6)", BLACK, 20);
        drawString(w / 2 - 200, 450, "Appuyez sur un numéro pour choisir la difficulté (1-4)", BLACK, 12);

        int diff = 0;
        do
        {
            getEvent(0, e);
            if (e.type == EVT_KEY_ON)
            {
                if (e.key >= '1' && e.key <= '4')
                {
                    diff = e.key - '0';
                }
            }
        } while (diff == 0);

        switch (diff)
        {
        case 1:
            divsX = 2;
            divsY = 2;
            break;
        case 2:
            divsX = 3;
            divsY = 3;
            break;
        case 3:
            divsX = 4;
            divsY = 4;
            break;
        case 4:
            divsX = 6;
            divsY = 6;
            break;
        }
    }

    return choice;
}

void mouse2cell(Img img, int &cellX, int &cellY)
{
    int mouseX, mouseY;
    getMouse(mouseX, mouseY);
    
    // Suppose img.width() and img.height() are the puzzle image dimensions
    int cellWidth = img.width() / divsX;
    int cellHeight = img.height() / divsY;
    
    // Convert mouse coordinates to cell indices
    cellX = mouseX / cellWidth;
    cellY = mouseX / cellHeight;
    
    // Clamp to valid range if needed
    if (cellX < 0) cellX = 0;
    if (cellX >= divsX) cellX = divsX - 1;
    if (cellY < 0) cellY = 0;
    if (cellY >= divsY) cellY = divsY - 1;
}

int main()
{
    // Importing new images for after

    Img img;
    if (!load(img, srcPath("image.jpg")))
        return 0;

    w = img.width() + decal * divsX;
    h = img.height() + decal * divsY + ui_decal;
    openWindow(w, h, "Puzzler - Atprog");

    
    int option = displayMainMenu(divsX, divsX);
    switch (option)
    {
    case 1:
        // Initialising the puzzle
        Puzzle puzzleGame(img, divsX, divsY);
        clearWindow();
        puzzleGame.show("This is the original image !!, Get ready ...", w / 10, h - ui_decal / 2);
        milliSleep(2500);
        
        // Game mechanics
        puzzleGame.shuffle();
        puzzleGame.show("Go !", w / 10, h - ui_decal / 2);
        milliSleep(1000);
        
        while (true)
        {
            drawString(w / 10, h - ui_decal / 4, "Click a cell ..", BLACK, 10, 1, false, true);
            
            // int x1 = intRandom(0, divsX - 1), y1 = intRandom(0, divsY - 1);
            // int x2 = intRandom(0, divsX - 1), y2 = intRandom(0, divsY - 1);
            
            int cellX1, cellY1, cellX2, cellY2;
            mouse2cell(img, cellX1, cellY1);
            drawString(3 * w / 10, h - ui_decal / 4, "cell 1", BLACK, 10, 1, false, true);
            mouse2cell(img, cellX2, cellY2);
            drawString(5 * w / 10, h - ui_decal / 4, "cell 2", BLACK, 10, 1, false, true);
            milliSleep(500);

            
            puzzleGame.swapPieces(puzzleGame.puzzleTiles[cellX1][cellY1], puzzleGame.puzzleTiles[cellX2][cellY2]);
            puzzleGame.show("Time : 999 , Score: 999", w / 10, h - ui_decal / 2);
        }

        // End game*/
        milliSleep(2000);
        endGraphics();
        break;
    }

    return 0;
}
