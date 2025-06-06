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

int w = 1280, h = 802;

int divsX = 2, divsY = 2;
int imageIndex = 1;
float decal = 5;
float ui_decal = 70;

Color BACKGROUND_COLOR = Color(180, 180, 180);

void displayImageMenu()
{
    clearWindow();
    // drawString(w/2, h/2, "Select an image", BLACK, 40);
    Image<Color> menu;
    load(menu, srcPath("Media/imageSelectionMenu.jpg"));   //Images selection menu
    display(menu, 0, 0);

    int choice = 0;
    Event e;
    do
    {
        getEvent(0, e);
        if (e.type == EVT_KEY_ON)
        {
            if (e.key >= '1' && e.key <= '9')
            {
                choice = e.key - '0';
            }
        }
    } while (choice == 0);    
    imageIndex = choice;
}

//Displays the main menu, the difficulties menu and the rules menu
int displayMainMenu(int &divsX, int &divsY)
{
    clearWindow();
    fillRect(0, 0, w, h, BACKGROUND_COLOR);
    Image<Color> menu;
    load(menu, srcPath("Media/menu.png"));
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

    // If the user starts the game, then choose the difficulty
    if (choice == 1)
    {
        clearWindow();
        Image<Color> difficulties;
        load(difficulties, srcPath("Media/difficulties.png"));
        display(difficulties, 0, 0);
        int diff = 0;
        do
        {
            getEvent(0, e);
            if (e.type == EVT_KEY_ON)
            {
                if (e.key >= '1' && e.key <= '5')
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
        case 5:
            divsX = 10;
            divsY = 10;
            break;
        }
        displayImageMenu();
    }

    return choice;
}

//Displays howToPlay Menu
void displayHowToPlayMenu() {
    clearWindow();
    Image<Color> menu;
    if (!load(menu, srcPath("Media/HowToPlayMenu.png"))) return;
    display(menu, 0, 0);

    Event e;
    // wait until the user presses '0'
    do {
        getEvent(0, e);
    } while (!(e.type == EVT_KEY_ON && e.key == '0'));
}

// Selects the Puzzle tile
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

// Displays the selected tiles and highlights them
void mouseControl(int &cellX1, int &cellY1, int &cellX2, int &cellY2, Img img)
{
    while (true)
    {
        mouse2cell(img, cellX1, cellY1);
        if (cellX1 != -1)
            break;
    }
    drawString(3 * w / 10, h - ui_decal / 4, "Cell 1, ", WHITE, 14, 0, false, true);
    AlphaColor transCol(255, 255, 255, 158);
    fillRect(cellX1 * (img.width()/divsX+2), cellY1 * (img.height()/divsY+2), img.width()/divsX, img.height()/divsY, transCol);
    
    while (true)
    {
        mouse2cell(img, cellX2, cellY2);
        if (cellX2 != -1)
        break;
    }
    drawString(3 * w / 10 + 70, h - ui_decal / 4, "Cell 2", WHITE, 14, 0, false, true);
    fillRect(cellX2 * (img.width()/divsX+2), cellY2 * (img.height()/divsY+2), img.width()/divsX, img.height()/divsY, transCol);
    milliSleep(100);
 }

int main()
{
    // Importing new images for after
    
    // w = img.width() + decal * divsX;
    // h = img.height() + decal * divsY + ui_decal;
    openWindow(w, h, "Puzzler - Atprog");

    int option;
    do {
        option = displayMainMenu(divsX, divsY);  // existing menu (1=Play, 2=HowToPlay, 3=Quit)

        if (option == 2) {
        displayHowToPlayMenu();
        }
    } while (option == 2);
    
    switch (option)
    {
        // If the user chooses to play the game
        case 1:
        {
        Img img;
        if (!load(img, srcPath("Media/image"+to_string(imageIndex)+".jpg")))
            return 0;
        img = reduce(img, 1.5);
        // Initialising the puzzle
        Puzzle puzzleGame(img, divsX, divsY);
        clearWindow();

        puzzleGame.show("This is the original image !!, Get ready ...", w / 10, h - ui_decal / 2 );
        milliSleep(4000);

        // Game mechanics
        puzzleGame.shuffle();
        puzzleGame.show("Go !", w / 10, h - ui_decal / 2);

        milliSleep(400);

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
                // puzzleGame.show("You Win !! After " + to_string(swap_counter) + " swaps.", w / 10, h - ui_decal / 2);
                clearWindow();
                Image<Color> winBanner;
                load(winBanner, srcPath("Media/winBanner.png"));
                display(winBanner, 0, 0);
                drawString(w / 2-300, h/2, "You Win !! After " + to_string(swap_counter) + " swaps.", WHITE, 30, 0, false, true);
                break;
            }
        }

        // End game*/
        milliSleep(4000);
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
