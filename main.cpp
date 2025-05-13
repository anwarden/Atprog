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

const int w = 500, h = 500;

const int divs = 3;
float decal = 10;

int main() {
    // Importing new images for after
    Img img;
    if (!load(img,srcPath("image.jpg"))) return 0;

    float square_dim = min(img.width(), img.height());
    img = img.getSubImage(0, 0, square_dim, square_dim);
    openWindow(img.width()+decal*divs, img.height()+decal*divs, "Puzzler - Atprog");
    //Subdivide the image
    Img puzzle_items[divs][divs];

    float subLen = square_dim/divs;

    cout << "hello" << endl;
    for(int i = 0; i<divs; i++)
    {
        for(int j = 0; j<divs; j++)
            puzzle_items[i][j] = img.getSubImage(i*subLen, j*subLen, subLen, subLen);
    }


    for(int i = 0; i<divs; i++)
    {
        for(int j = 0; j<divs; j++)
        {
            display(puzzle_items[i][j], i*subLen+intRandom(2, decal), j*subLen+intRandom(2, decal));
        }
    }

    // Some dummy tests
    //Img testExtract = img.getSubImage(0, 0, img.width()/4, img.width()/4);
    //display(img, 10, 10);
    //display(testExtract, 10, 10);



    //End game
    milliSleep(1000);
    endGraphics();
    return 0;
}
