//David Deng
//UID: 305-382-790
//plot.cpp

#include <iostream>
#include "grid.h"
#include <cassert>
#include <cctype>
using namespace std;

void plotHorizontalLine(int r, int c, int distance, char plotChar, int fgbg); //function to plot horizontal line

void plotVerticalLine(int r, int c, int distance, char ch, int fgbg); //function to plot vertical line

int distanceStringToInt(string conversionString, bool negative); //function to convert distance from string form to int form

bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg); //function to make appropriate line plotting commands

int performCommands(string commandString, char& plotChar, int& mode, int& badPos); //function to run and check all commands

bool findDistance(int& pos, string commandString, int& distance); //function to find distanc

const int HORIZ = 0;
const int VERT = 1;

const int FG = 0;
const int BG = 1;

int main()
{
    setSize(20, 30);
    char currentChar = '*';
    int currentMode = FG;
    for (;;)
    {
        cout << "Enter a command string: ";
        string cmd;
        getline(cin, cmd);
        if (cmd == "")
            break;
        int position;
        int status = performCommands(cmd, currentChar, currentMode, position);
        switch (status)
        {
          case 0:
            draw();
            break;
          case 1:
                cout << "Syntax error at position " << position+1 << endl;
            break;
          case 2:
                cout << "Cannot perform command at position " << position+1 << endl;
            break;
          default:
              // It should be impossible to get here.
                cerr << "performCommands returned " << status << "!" << endl;
        }
    }
    
}

void plotHorizontalLine(int r, int c, int distance, char plotChar, int fgbg) {
    for (;;) {
        if (fgbg == FG || (fgbg == BG && getChar(r, c) == ' ')) {
            setChar(r, c, plotChar);
        }
        if (distance < 0) {
            distance++;
            c--;
            continue;
        }
        if (distance > 0) {
            distance--;
            c++;
            continue;
        }
        break;
        //break only executed when distance = 0, meaning the position is at its final point
    }
}

void plotVerticalLine(int r, int c, int distance, char plotChar, int fgbg) {
    for (;;) {
        if (fgbg == FG || (fgbg == BG && getChar(r, c) == ' ')) {
            setChar(r, c, plotChar);
        }
        if (distance < 0) {
            distance++;
            r--;
            continue;
        }
        if (distance > 0) {
            distance--;
            r++;
            continue;
        }
        break;
        //break only executed when distance = 0, meaning the position is at its final point
    }
}

bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg) {
    //checks for valid inputs
    if (dir != HORIZ && dir != VERT) {
        return false;
    }
    if (fgbg != FG && fgbg != BG) {
        return false;
    }
    if (dir == HORIZ) {
        if (c + distance < 1 || c + distance > getCols()) {
            return false;
        }
    }
    if (dir == VERT) {
        if (r + distance < 1 || r + distance > getRows()) {
            return false;
        }
    }
    if (!(isprint(plotChar))) {
        return false;
    }
    
    //if valid input, plots
    if (dir == HORIZ) {
        plotHorizontalLine(r, c, distance, plotChar, fgbg);
    }
    
    if (dir == VERT) {
        plotVerticalLine(r, c, distance, plotChar, fgbg);
    }
    
    return true;
}

int performCommands(string commandString, char& plotChar, int& mode, int& badPos) {
    int pos = 0;
    int r = 1;
    int c = 1;
    bool perfError = false;
    int charStart; //indicates position of the starting command, this value is set as the bad position when there is a performance error
    
    while (pos != commandString.size()) {
        int distance;
        charStart = pos; //set charStart to current position, which is first element of the command string
        if (toupper(commandString[pos]) == 'H') {
            if (!findDistance(pos, commandString, distance)) {
                //if false, then there were no digits after plotting command – syntax error
                badPos = pos;
                return 1;
            }
            if (plotLine(r, c, distance, HORIZ, plotChar, mode)) {
                c = c + distance; //changes distance if it would be within bounds
            }
            //if plotLine returns false, there's a performance error
            else if (!perfError) {
                //condition stops value of bad position from updating multiple times if multiple performance errors found
                
                //updates position if first performance error found
                perfError = true;
                badPos = charStart; //change later to proper value
            }
        }
        else if (toupper(commandString[pos]) == 'V') {
            //see comments at the if statement preceding this else if, same logic applies
            if (!findDistance(pos, commandString, distance)) {
                badPos = pos;
                return 1;
            }
            if (plotLine(r, c, distance, VERT, plotChar, mode)) {
                r = r + distance;
            }
            else if (!perfError) {
                perfError = true;
                badPos = charStart;
            }
        }
        else if (toupper(commandString[pos]) == 'B') {
            pos++;
            if (pos == commandString.size() || !isprint(commandString[pos])) {
                //returns syntax error if no input after B or unprintable character after B
                badPos = pos;
                return 1;
            }
            plotChar = commandString[pos];
            pos++;
            mode = BG;
        }
        else if (toupper(commandString[pos]) == 'F') {
            //see comments in preceding elif, same logic applies
            pos++;
            if (pos == commandString.size() || !isprint(commandString[pos])) {
                badPos = pos;
                return 1;
            }
            plotChar = commandString[pos];
            pos++;
            mode = FG;
        }
        else if (toupper(commandString[pos]) == 'C') {
            //resets to default values
            clearGrid();
            r = 1;
            c = 1;
            plotChar = '*';
            mode = FG;
            pos++;
        }
        else {
            //returns syntax error if nonvalid command start character
            badPos = pos;
            return 1;
        }
    }
    if (perfError) {
        return 2;
    }
    return 0;
}

bool findDistance(int& pos, string commandString, int& distance) {
    bool negative = false;
    pos++;
    
    if (commandString[pos] == '-') {
        negative = true;
        pos++;
    }
    
    int intStart = pos; //starting point of the substring that gives us the integer value, stored in form of a string
    
    for (size_t k = 0; k < 2; k++) { //2 digits is maximum for a plot command
        if (isdigit(commandString[pos])) {
            pos++;
        }
        else if (pos - intStart == 0) {
            return false; //gives false if there is no numerical input after the command
        }
        else {
            break; //breaks if only one digit before another command
        }
    }
    
    string conversionString = commandString.substr(intStart, pos - intStart);
    //conversionString consists of digit(s) that follow the command in commandString
    distance = distanceStringToInt(conversionString, negative);
    return true;
}

int distanceStringToInt(string conversionString, bool negative) {
     int multiplier = 1;
     int result = 0;
    
    //iterates through string, converting chars to ints and multiplying by 10 for left digit and by 1 for right digit
     for (size_t i = 0; i != conversionString.size(); i++) {
         result += (conversionString[conversionString.size() - 1 - i] - '0') * multiplier;
         multiplier *= 10;
     }
     
     if (negative) {
         result = result * -1;
     }
     return result;
}

