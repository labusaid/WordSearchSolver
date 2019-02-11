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

            //Searches right to left.
            for (int charPos = 0; charPos < theFind.word.length(); charPos++) {
                //If characters do not match break for loop.
                if (theFind.word.at(charPos) != game.puzzle[r][c - charPos]) {
                    break;
                }
                //Mark as found is charPos reaches the end of the word.
                if (charPos == (theFind.word.length() - 1)) {
                    theFind.found = true;
                    theFind.where = RIGHT_LEFT;
                    theFind.row = r;
                    theFind.column = c;
                    theFind.foundCount++;
                    break;
                }
            }

            //Searches up.
            for (int charPos = 0; charPos < theFind.word.length(); charPos++) {
                //If characters do not match break for loop.
                if (theFind.word.at(charPos) != game.puzzle[r - charPos][c]) {
                    break;
                }
                //Mark as found is charPos reaches the end of the word.
                if (charPos == (theFind.word.length() - 1)) {
                    theFind.found = true;
                    theFind.where = UP;
                    theFind.row = r;
                    theFind.column = c;
                    theFind.foundCount++;
                    break;
                }
            }

            //Searches down.
            for (int charPos = 0; charPos < theFind.word.length(); charPos++) {
                //If characters do not match break for loop.
                if (theFind.word.at(charPos) != game.puzzle[r + charPos][c]) {
                    break;
                }
                //Mark as found is charPos reaches the end of the word.
                if (charPos == (theFind.word.length() - 1)) {
                    theFind.found = true;
                    theFind.where = DOWN;
                    theFind.row = r;
                    theFind.column = c;
                    theFind.foundCount++;
                    break;
                }
            }

            //Searches diagonal to top right.
            for (int charPos = 0; charPos < theFind.word.length(); charPos++) {
                //If characters do not match break for loop.
                if (theFind.word.at(charPos) != game.puzzle[r - charPos][c + charPos]) {
                    break;
                }
                //Mark as found is charPos reaches the end of the word.
                if (charPos == (theFind.word.length() - 1)) {
                    theFind.found = true;
                    theFind.where = RIGHT_UP;
                    theFind.row = r;
                    theFind.column = c;
                    theFind.foundCount++;
                    break;
                }
            }

            //Searches diagonal to bottom right.
            for (int charPos = 0; charPos < theFind.word.length(); charPos++) {
                //If characters do not match break for loop.
                if (theFind.word.at(charPos) != game.puzzle[r + charPos][c + charPos]) {
                    break;
                }
                //Mark as found is charPos reaches the end of the word.
                if (charPos == (theFind.word.length() - 1)) {
                    theFind.found = true;
                    theFind.where = RIGHT_DOWN;
                    theFind.row = r;
                    theFind.column = c;
                    theFind.foundCount++;
                    break;
                }
            }

            //Searches diagonal to top left.
            for (int charPos = 0; charPos < theFind.word.length(); charPos++) {
                //If characters do not match break for loop.
                if (theFind.word.at(charPos) != game.puzzle[r - charPos][c - charPos]) {
                    break;
                }
                //Mark as found is charPos reaches the end of the word.
                if (charPos == (theFind.word.length() - 1)) {
                    theFind.found = true;
                    theFind.where = LEFT_UP;
                    theFind.row = r;
                    theFind.column = c;
                    theFind.foundCount++;
                    break;
                }
            }

            //Searches diagonal to bottom left.
            for (int charPos = 0; charPos < theFind.word.length(); charPos++) {
                //If characters do not match break for loop.
                if (theFind.word.at(charPos) != game.puzzle[r + charPos][c - charPos]) {
                    break;
                }
                //Mark as found is charPos reaches the end of the word.
                if (charPos == (theFind.word.length() - 1)) {
                    theFind.found = true;
                    theFind.where = LEFT_DOWN;
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

    //Error and exit if puzzle file was not opened.
    if (!readPuzzle(*wordGame1,puzzleFileName)) {
        cerr << "The puzzle file \"" << puzzleFileName << "\" could not be opened or is invalid" << endl;
        return 1;
    }

    //Display puzzle if successfully read.
    cout << "The puzzle from file \"" << puzzleFileName  << "\"" << endl;
    displayPuzzle(*wordGame1);

    //Read in second file name and open second file.
    cin >> wordListFileName;
    inputFile.open(wordListFileName);

    //Error and exit if words file was not opened.
    if (!inputFile) {
        cerr << "The puzzle file \"" << wordListFileName << "\" could not be opened or is invalid" << endl;
        return 1;
    }

    //Get word from file and search for word.
    wordFind *wordFind1 = new wordFind;
    while (inputFile >> wordFind1->word) {
        //Reset wordFind1.
        wordFind1->found = false;
        wordFind1->foundCount = 0;

        findWord(*wordGame1,*wordFind1);

        //Output when a word is found.
        if (wordFind1->found) {
            //Output how many occurrences were found if it is greater than one.
            if (wordFind1->foundCount > 1) {
                cout << "The word " << wordFind1->word << " was found "
                     << wordFind1->foundCount << " times" << endl;
            }
                //Output where word was found.
            else if (wordFind1->foundCount == 1){
                cout << "The word " << wordFind1->word << " was found at (" << wordFind1->row+1 << ", "
                     << wordFind1->column+1 << ") - " ;
                switch (wordFind1->where) {
                    case LEFT_RIGHT: cout << "right";
                        break;
                    case RIGHT_LEFT: cout << "left";
                        break;
                    case DOWN: cout << "down";
                        break;
                    case UP: cout << "up";
                        break;
                    case RIGHT_DOWN: cout << "right/down";
                        break;
                    case RIGHT_UP: cout << "right/up";
                        break;
                    case LEFT_DOWN: cout << "left/down";
                        break;
                    case LEFT_UP: cout << "left/up";
                        break;
                }
                cout << endl;
            }
        }
        //Output if word is not found.
        else cout << "The word " << wordFind1->word << " was not found" << endl;
    }

    return 0;
}
