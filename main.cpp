// Imagine++ project
// Project:  Puzzler
// Student(s): Anwar Kardid, Abdeladim

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Imagine/Graphics.h>
#include <vector>

#include "PuzzlePiece.h"
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
    Image<Color> menu;
    load(menu, srcPath("menu.png"));
    display(menu, 0, 0);

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
        Image<Color> difficulties;
        load(difficulties, srcPath("difficulties.png"));
        display(difficulties, 0, 0);
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
            divsX = 3;
            divsY = 3;
            break;
        case 2:
            divsX = 4;
            divsY = 4;
            break;
        case 3:
            divsX = 6;
            divsY = 6;
            break;
        case 4:
            divsX = 8;
            divsY = 8;
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
    cellY = mouseY / cellHeight;

    // Clamp to valid range if needed
    if (cellX < 0 || cellX >= divsX || cellY < 0 || cellY >= divsY)
    {
        cellX = -1;
        cellY = -1;
    }

    // cout << "Mouse in : " << mouseX << " , " << mouseY << " to : " << cellX << " , " << cellY << endl;
}

void mouseControl(int &cellX1, int &cellY1, int &cellX2, int &cellY2, Img img)
{
    while (true)
    {
        mouse2cell(img, cellX1, cellY1);
        if (cellX1 != -1)
            break;
    }
    drawString(3 * w / 10, h - ui_decal / 4, "Cell 1, ", WHITE, 14, 0, false, true);
    AlphaColor transCol(255, 0, 0, 128);
    fillRect(cellX1 * img.width()/divsX, cellY1 * img.height()/divsY, img.width()/divsX, img.height()/divsY, transCol);
    
    while (true)
    {
        mouse2cell(img, cellX2, cellY2);
        if (cellX2 != -1)
        break;
    }
    drawString(3 * w / 10 + 70, h - ui_decal / 4, "Cell 2", WHITE, 14, 0, false, true);
    fillRect(cellX2 * (img.width()/divsX+1), cellY2 * (img.height()/divsY+1), img.width()/divsX, img.height()/divsY, transCol);
    milliSleep(150);
 }

int main()
{
    // Importing new images for after
    Img img;
    if (!load(img, srcPath("image.jpg")))
        return 0;

    img = reduce(img, 1.5);
    w = img.width() + decal * divsX;
    h = img.height() + decal * divsY + ui_decal;
    openWindow(w, h, "Puzzler - Atprog");

    int option = displayMainMenu(divsX, divsY);

    switch (option)
    {
    case 1:
    {
        // Initialising the puzzle
        Puzzle puzzleGame(img, divsX, divsY);
        clearWindow();

        puzzleGame.show("This is the original image !!, Get ready ...", w / 10, h - ui_decal / 2);
        milliSleep(2000);

        // Game mechanics
        puzzleGame.shuffle();
        puzzleGame.show("Go !", w / 10, h - ui_decal / 2);

        milliSleep(500);

        int swap_counter = 0;
        puzzleGame.show("Puzzle swaps: " + to_string(swap_counter), w / 10, h - ui_decal / 2);
        // Game loop
        while (true)
        {
            drawString(w / 10, h - ui_decal / 4, "Click a cell ..", WHITE, 10, 0, false, true);

            int cellX1, cellY1, cellX2, cellY2;
            mouseControl(cellX1, cellY1, cellX2, cellY2, img);
            puzzleGame.swapPieces(cellX1, cellY1, cellX2, cellY2);
            swap_counter++;

            puzzleGame.show("Puzzle swaps: " + to_string(swap_counter), w / 10, h - ui_decal / 2);
            if (puzzleGame.isSolved())
            {
                puzzleGame.show("You Win !! After " + to_string(swap_counter) + " swaps.", w / 10, h - ui_decal / 2);
                milliSleep(1000);
                break;
            }
        }

        // End game*/
        milliSleep(2000);
        endGraphics();
        // break;
    }
    case 3:
    {
        // Quit the game;
        break;
    }
    }
    return 0;
}
