// Imagine++ project
// Project:  Mastermind
// Student(s): Anwar Kardid

#include<iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int nbcases = 5;
const int nbcol = 4;
const int nbtrials = 10;

// Get combination from keyboard
// (nbcases digits in a sequence)
// Beware: add check length and values
bool getCombination(int trial, int combi[nbcases]) {
    cout << "Your trial #" << trial <<" : ";
    string s;
    cin >> s;

    if((int)s.length() != nbcases)
    {
        cout << "Error combination. Try again!" << endl;
        return false;
    }

    for(char c : s)
    {
        if((int)c < (int)'0' || (int)c >= '5')
        {
            cout << "Error combination. Try again!" << endl;
            return false;
        }
    }

    for(int i=0; i<nbcases; i++)
        combi[i]=s[i]-'0';

    return true;
}

void generate_comination(int combin[nbcases])
{
    for(int i = 0; i < nbcases; i++)
    {
        combin[i] = rand()%nbcol;
    }
}

bool equal_combinations(int combin_ref[nbcases], int combin_usr[nbcases])
{
    for(int i=0; i<nbcases; i++)
    {
        if(combin_ref[i] != combin_usr[i])
        {
            return false;
        }
    }
    return true;
}

void display_combination(int combin[nbcases])
{
    for(int i = 0; i < nbcases; i++)
    {
        cout << combin[i] << ' ';
    }
    cout << endl;
}

void debrief_comb(int combin_ref[nbcases], int combin_usr[nbcases])
{
    int correct_places = 0;
    int correct_colors = 0;
    for(int i = 0; i < nbcases; i++)
    {
        correct_places += (int)(combin_ref[i] == combin_usr[i]);

    }
    for(int i = 0; i < nbcases; i++)
    {
        cout << combin_usr[i];
    }
    cout << " - " << correct_places << ", " << correct_colors << endl;
}

int main() {
	cout << "MASTERMIND" << endl;
    cout << "The combination to guess is 5 digits long." << endl;
    cout << "You have 10 trials" << endl;

    int combin_ref[nbcases];
    int combin_usr[nbcases];

    srand((unsigned int)time(0));
    generate_comination(combin_ref);

    for(int i = 0; i < nbcases; i++)
    {
        cout << combin_ref[i] << ' ';
    }
    cout << endl;

    int trial = 1;
    bool equal_comb = false;
    bool good_input = false;

    do
    {
        good_input = getCombination(trial, combin_usr);
        equal_comb = equal_combinations(combin_ref, combin_usr);
        if(good_input)
        {
            debrief_comb(combin_ref, combin_usr);
            trial++;
        }
    }
    while(trial <= nbtrials && !equal_comb);

    cout << "You won !!";

	return 0;
}
