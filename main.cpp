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
    game.version = 2;

    //Open file and confirm that it opened correctly.
    inputFile.open(inputFileName);
    if (!inputFile) return false;

    //Read number of rows and columns.
    inputFile >> game.numberRows >> game.numberColumns;
    //Check number of rows and columns.
    if (game.numberRows < 1 || game.numberRows > 50 || game.numberColumns < 1 || game.numberColumns > 50) {
        return false;
    }

    //Populate the char matrix.
    for (int r = 0; r < game.numberRows; r++) {
        for (int c = 0; c < game.numberColumns; c++) {
            inputFile >> game.puzzle[r][c];
        }
    }

    //Close file and exit readPuzzle.
    inputFile.close();
    return true;
}

void displayPuzzle(wordGame &game) {
    for (int r = 0; r < game.numberRows; r++) {
        for (int c = 0; c < game.numberColumns; c++) {
            cout << game.puzzle[r][c];
        }
        cout << endl;
    }
}

//bool searchInDirection(int rDiff, int cDiff, wordGame &game, string word) {
//    int r = 0;
//    int c = 0;
//
//    //Ensure the entire word will fit.
//    if (word.length() >= (c + game.numberColumns)) {
//        return false;
//    }
//
//    int charPos = 0;
//    while (charPos < word.length()) {
//        if (word.at(charPos) != game.puzzle[r][c]) {
//            return false;
//        }
//        r += rDiff;
//        c += cDiff;
//        charPos++;
//    }
//    if (charPos == word.length()) {
//        return true;
//    }
//}

void findWord(wordGame &game, wordFind &theFind) {
    theFind.found = false;
    theFind.foundCount = 0;

    //Search char matrix for string.
    for (int r = 0; r < game.numberRows; r++) {
        for (int c = 0; c < game.numberColumns; c++) {

            //Searches left to right.
            for (int charPos = 0; charPos < theFind.word.length(); charPos++) {
                //If characters do not match break for loop.
                if (theFind.word.at(charPos) != game.puzzle[r][c + charPos]) {
                    break;
                }
                //Mark as found is charPos reaches the end of the word.
                if (charPos == (theFind.word.length() - 1)) {
                    theFind.found = true;
                    theFind.where = LEFT_RIGHT;
                    theFind.row = r;
                    theFind.column = c;
                    theFind.foundCount++;
                    break;
                }
            }

        }
    }
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
    wordFind1->found = false;
    while (inputFile >> wordFind1->word) {
        findWord(*wordGame1,*wordFind1);

        //Output when a word is found.
        if (wordFind1->found) {
            //Output how many occurrences were found if it is greater than one.
            if (wordFind1->foundCount > 1) {
                cout << "The word " << wordFind1->word << " was found "
                << wordFind1->foundCount << " times" << endl;
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
