// Imagine++ project
// Project:  Puzzler
// Student(s): Anwar Kardid, Abdeladim

#include<iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
#include <vector>

using namespace Imagine;
using namespace std;

typedef Image<Color> Img;

const int w = 1000, h = 1000;

const int divs = 3;
float decal = 5;

Color BACKGROUND_COLOR = GREEN;

int displayMainMenu() {
    clearWindow();
    fillRect(0, 0, w, h, BACKGROUND_COLOR);

    drawString(w / 2 - 150, 100, "PUZZLER", BLACK, 36);
    drawString(w / 2 - 200, 150, "Un jeu de puzzle avec Imagine++", BLACK, 18);

    drawString(w / 2 - 100, 250, "1. Jouer", BLACK, 24);
    drawString(w / 2 - 100, 300, "2. Classement", BLACK, 24);
    drawString(w / 2 - 100, 350, "3. Quitter", BLACK, 24);

    drawString(w / 2 - 200, 450, "Appuyez sur un numéro pour choisir une option (1-3)", BLACK, 16);

        int choice = 0;
    Event e;
    do {
        getEvent(0, e);
        if (e.type == EVT_KEY_ON) {
            if (e.key >= '1' && e.key <= '3') {
                choice = e.key - '0';
            }
        }
    } while (choice == 0);

    return choice;// kanbghik ahbiba
}

int main() {
    // Importing new images for after

    Img img;
    if (!load(img,srcPath("image.jpg"))) return 0;

    //float square_dim = min(img.width(), img.height());
    //img = img.getSubImage(0, 0, square_dim, square_dim);

    openWindow(img.width()+decal*divs, img.height()+decal*divs, "Puzzler - Atprog");
    //openWindow(w, h, "Puzzler - Atprog");
    int option = displayMainMenu();
    if(option == 1)
    {
        clearWindow();
        //Subdivide the image
        Img puzzle_items[divs][divs];

        float subLen_x = img.width()/divs;
        float subLen_y = img.height()/divs;

        cout << "hello" << endl;
        for(int i = 0; i<divs; i++)
        {
            for(int j = 0; j<divs; j++){
                puzzle_items[i][j] = img.getSubImage(i*subLen_x, j*subLen_y, subLen_x, subLen_y);
            }
        }

        for(int i = 0; i<divs; i++)
        {
            for(int j = 0; j<divs; j++)
            {

                display(puzzle_items[i][j], i*(subLen_x+intRandom(decal/2, decal)), j*(subLen_y+intRandom(decal/2, decal)));
            }
        }

        // Some dummy tests

        //Img testExtract = img.getSubImage(0, 0, img.width()/4, img.width()/4);
        //display(img, 10, 10);
        //display(testExtract, 10, 10);



        //End game
        milliSleep(1000);
        endGraphics();
    }
    return 0;
}
