#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cctype>
using namespace std;

enum direction {LEFT_RIGHT, RIGHT_LEFT, DOWN, UP, RIGHT_DOWN, RIGHT_UP, LEFT_DOWN, LEFT_UP};

const int MAX = 50;

struct wordGame
{
    int version;
    int numberRows;
    int numberColumns;
    char puzzle[MAX][MAX];

};

struct wordFind
{
    string word;
    bool found;
    int row;
    int column;
    direction where;
    int foundCount;

};


int main() {
    //cin >> inputFile1 >> inputFile2;
    return 0;
}

bool readPuzzle(wordGame &game, string inputFileName) {

}

//
void displayPuzzle(wordGame &game) {

}

//Searches character matrix for a word.
void findWord(wordGame &game) {

}
