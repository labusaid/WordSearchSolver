#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cctype>
using namespace std;

enum direction {LEFT_RIGHT, RIGHT_LEFT, DOWN, UP, RIGHT_DOWN, RIGHT_UP, LEFT_DOWN, LEFT_UP};

ifstream inputFile;
const int MAX = 50;
string puzzleFileName;
string wordListFileName;

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

bool readPuzzle(wordGame &game, string inputFileName) {
    game.version = 1;

    //Open file and confirm that it opened correctly.
    inputFile.open(inputFileName);
    if (!inputFile) return false;

    //Read number of rows and columns, then populate char matrix.
    inputFile >> game.numberRows >> game.numberColumns;
    for (int r = 0; r < game.numberRows; r++) {
        for (int c = 0; c < game.numberColumns; c++) {
            //TODO: read file into char array
        }
    }

    //Close file and exit readPuzzle.
    inputFile.close();
    return true;
}

void displayPuzzle(wordGame &game) {
    //TODO: display contents of puzzle to cout
}

//Searches character matrix for a word.
void findWord(wordGame &game, wordFind &theFind) {
    //TODO: search for word within puzzle
}

int main() {
    wordGame *wordGame1 = new wordGame;
    cin >> puzzleFileName;

    //Error and exit if file was not opened.
    if (!readPuzzle(*wordGame1,puzzleFileName)) {
        cerr << "File could not be opened." << endl;
        return 1;
    }

    //Display puzzle if successfully read.
    cout << "Puzzle was read." << endl;
    displayPuzzle(*wordGame1);

    //Read in second file name and open second file.
    cin >> wordListFileName;
    inputFile.open(wordListFileName);

    //Get word from file and search for word.
    wordFind *wordFind1 = new wordFind;
    while (inputFile >> wordFind1->word) {
        findWord(*wordGame1,*wordFind1);

        //Output when a word is found.
        if (wordFind1->found) {
            //Output how many occurrences were found if it is greater than one.
            if (wordFind1->foundCount > 1) {
                cout << "The word " << wordFind1->word << " was found "
                << wordFind1->foundCount << "times" << endl;
            }
            //Output where word was found.
            else{
                cout << "The word " << wordFind1->word << " was found at (" << wordFind1->row << ", "
                << wordFind1->column << ") - " << wordFind1->where << endl;
            }

        }
    }

    return 0;
}
