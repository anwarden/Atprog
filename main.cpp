// Imagine++ project
// Project:  Mastermind
// Student(s): Anwar Kardid

#include<iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include <Imagine/Graphics.h>
#include <Imagine/Images.h>

using namespace Imagine;
using namespace std;

typedef Image<Color> Img;

const int w = 500, h = 500;

int main() {

    // Display Image
    Img img;
    if (!load(img,srcPath("image.jpg")))
        return 0;

    openWindow(img.width()+20, img.height()+20, "Puzzler - Atprog");

    display(img, 10, 10);

    endGraphics();
	return 0;
}
