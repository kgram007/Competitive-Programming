//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : UVa Online Judge
// Problem ID/title : 403 - Postscript
//********************************************************************************

#define __cplusplus 201103L

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <math.h>
#include <limits>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <algorithm>
#include <bitset>

//***************** Debug ******************//
// - Defined with -D flag during compile time
// - undef to disable definition
//
#undef CHECK_RUN_TIME
//#undef INPUT_FROM_FILE
//#undef OUTPUT_TO_FILE
//******************************************//

using namespace std;

// Helper Class: Input Stream
class InputStream
{
public:
    template<typename T>
    void get(T& x) { cin >> x; }

    template<typename T>
    void getArray(T& x, int size) { for(int i=0; i<size; ++i) cin >> x[i]; }

    string getLine() { string s; getline(cin, s); return s; }

    string getNonEmptyLine() { string s; getline(cin >> ws, s); return s; }
};

// Input Stream variable
InputStream in;

// Helper: Timer
#ifdef CHECK_RUN_TIME
#include "Timer.h"
Timer _run_timer;
#endif

void programEntry()
{
#ifdef INPUT_FROM_FILE
    freopen("test.txt", "r", stdin);
#endif
#ifdef OUTPUT_TO_FILE
    freopen("out.txt", "w", stdout);
#endif
#ifdef CHECK_RUN_TIME
    _run_timer.start();
#endif
}

void programExit()
{
#ifdef CHECK_RUN_TIME
    _run_timer.printTimeMilliSec("====================\nRun Time");
#endif
}
//****************************************************************//

// Definitions and constants
#define PAGE_WIDTH      (60)
#define PAGE_HEIGHT     (60)
#define CHAR_SET_SIZE   (27)
#define CHAR_WIDTH      (6)
#define CHAR_HEIGHT     (5)

#define isAlphabet(x)   (x >= 'A' && x <= 'Z')

enum FontType {FONT_C1, FONT_C5};

const char CHAR_SET [CHAR_SET_SIZE][CHAR_HEIGHT][CHAR_WIDTH] = {
        { {'.','*','*','*','.','.'}, {'*','.','.','.','*','.'}, {'*','*','*','*','*','.'}, {'*','.','.','.','*','.'}, {'*','.','.','.','*','.'} },
        { {'*','*','*','*','.','.'}, {'*','.','.','.','*','.'}, {'*','*','*','*','.','.'}, {'*','.','.','.','*','.'}, {'*','*','*','*','.','.'} },
        { {'.','*','*','*','*','.'}, {'*','.','.','.','*','.'}, {'*','.','.','.','.','.'}, {'*','.','.','.','.','.'}, {'.','*','*','*','*','.'} },
        { {'*','*','*','*','.','.'}, {'*','.','.','.','*','.'}, {'*','.','.','.','*','.'}, {'*','.','.','.','*','.'}, {'*','*','*','*','.','.'} },
        { {'*','*','*','*','*','.'}, {'*','.','.','.','.','.'}, {'*','*','*','.','.','.'}, {'*','.','.','.','.','.'}, {'*','*','*','*','*','.'} },
        { {'*','*','*','*','*','.'}, {'*','.','.','.','.','.'}, {'*','*','*','.','.','.'}, {'*','.','.','.','.','.'}, {'*','.','.','.','.','.'} },
        { {'.','*','*','*','*','.'}, {'*','.','.','.','.','.'}, {'*','.','.','*','*','.'}, {'*','.','.','.','*','.'}, {'.','*','*','*','.','.'} },
        { {'*','.','.','.','*','.'}, {'*','.','.','.','*','.'}, {'*','*','*','*','*','.'}, {'*','.','.','.','*','.'}, {'*','.','.','.','*','.'} },
        { {'*','*','*','*','*','.'}, {'.','.','*','.','.','.'}, {'.','.','*','.','.','.'}, {'.','.','*','.','.','.'}, {'*','*','*','*','*','.'} },
        { {'.','.','*','*','*','.'}, {'.','.','.','*','.','.'}, {'.','.','.','*','.','.'}, {'*','.','.','*','.','.'}, {'.','*','*','.','.','.'} },
        { {'*','.','.','.','*','.'}, {'*','.','.','*','.','.'}, {'*','*','*','.','.','.'}, {'*','.','.','*','.','.'}, {'*','.','.','.','*','.'} },
        { {'*','.','.','.','.','.'}, {'*','.','.','.','.','.'}, {'*','.','.','.','.','.'}, {'*','.','.','.','.','.'}, {'*','*','*','*','*','.'} },
        { {'*','.','.','.','*','.'}, {'*','*','.','*','*','.'}, {'*','.','*','.','*','.'}, {'*','.','.','.','*','.'}, {'*','.','.','.','*','.'} },
        { {'*','.','.','.','*','.'}, {'*','*','.','.','*','.'}, {'*','.','*','.','*','.'}, {'*','.','.','*','*','.'}, {'*','.','.','.','*','.'} },
        { {'.','*','*','*','.','.'}, {'*','.','.','.','*','.'}, {'*','.','.','.','*','.'}, {'*','.','.','.','*','.'}, {'.','*','*','*','.','.'} },
        { {'*','*','*','*','.','.'}, {'*','.','.','.','*','.'}, {'*','*','*','*','.','.'}, {'*','.','.','.','.','.'}, {'*','.','.','.','.','.'} },
        { {'.','*','*','*','.','.'}, {'*','.','.','.','*','.'}, {'*','.','.','.','*','.'}, {'*','.','.','*','*','.'}, {'.','*','*','*','*','.'} },
        { {'*','*','*','*','.','.'}, {'*','.','.','.','*','.'}, {'*','*','*','*','.','.'}, {'*','.','.','*','.','.'}, {'*','.','.','.','*','.'} },
        { {'.','*','*','*','*','.'}, {'*','.','.','.','.','.'}, {'.','*','*','*','.','.'}, {'.','.','.','.','*','.'}, {'*','*','*','*','.','.'} },
        { {'*','*','*','*','*','.'}, {'*','.','*','.','*','.'}, {'.','.','*','.','.','.'}, {'.','.','*','.','.','.'}, {'.','*','*','*','.','.'} },
        { {'*','.','.','.','*','.'}, {'*','.','.','.','*','.'}, {'*','.','.','.','*','.'}, {'*','.','.','.','*','.'}, {'.','*','*','*','.','.'} },
        { {'*','.','.','.','*','.'}, {'*','.','.','.','*','.'}, {'.','*','.','*','.','.'}, {'.','*','.','*','.','.'}, {'.','.','*','.','.','.'} },
        { {'*','.','.','.','*','.'}, {'*','.','.','.','*','.'}, {'*','.','*','.','*','.'}, {'*','*','.','*','*','.'}, {'*','.','.','.','*','.'} },
        { {'*','.','.','.','*','.'}, {'.','*','.','*','.','.'}, {'.','.','*','.','.','.'}, {'.','*','.','*','.','.'}, {'*','.','.','.','*','.'} },
        { {'*','.','.','.','*','.'}, {'.','*','.','*','.','.'}, {'.','.','*','.','.','.'}, {'.','.','*','.','.','.'}, {'.','.','*','.','.','.'} },
        { {'*','*','*','*','*','.'}, {'.','.','.','*','.','.'}, {'.','.','*','.','.','.'}, {'.','*','.','.','.','.'}, {'*','*','*','*','*','.'} },
        { {'.','.','.','.','.','.'}, {'.','.','.','.','.','.'}, {'.','.','.','.','.','.'}, {'.','.','.','.','.','.'}, {'.','.','.','.','.','.'} }
};

// Variables
bool first_page = true;
char page_buf_[PAGE_HEIGHT][PAGE_WIDTH];

// Functions
void clearPage()
{
    for(int r=0; r<PAGE_HEIGHT; ++r)
        for(int c=0; c<PAGE_WIDTH; ++c)
            page_buf_[r][c] = '.';
}

void printPage()
{
    for(int r=0; r<PAGE_HEIGHT; ++r)
    {
        for(int c=0; c<PAGE_WIDTH; ++c)
            cout << page_buf_[r][c];
        cout << endl;
    }
    cout << endl;

    for(int c=0; c<PAGE_WIDTH; ++c)
        cout << '-';
    cout << endl;
}

void insertToBuffer_C1(char ch, int r, int c)
{
    if(ch == ' ' || !isprint(ch))
        return;
    if(r >= 0 && r < PAGE_WIDTH && c >= 0 && c < PAGE_WIDTH)
        page_buf_[r][c] = ch;
}

void insertToBuffer_C5(char ch, int r, int c)
{
    if(ch == ' ')
        return;

    int char_index = ch - 'A';
    for(int i=0; i<CHAR_HEIGHT; ++i)
    {
        int row = r + i;
        if(row < 0 || row >= PAGE_WIDTH)
            continue;
        for(int j=0; j<CHAR_WIDTH; ++j)
        {
            int col = c + j;
            if(col < 0 || col >= PAGE_WIDTH)
                continue;
            if(CHAR_SET[char_index][i][j] == '*')
                page_buf_[row][col] = CHAR_SET[char_index][i][j];
        }
    }
}

void cmdPlaceString(FontType font, int r, int c, string s)
{
    for(int i=0; i<(int)s.length(); ++i)
    {
        if(c > PAGE_WIDTH)
            return;
        if(font == FONT_C1)
        {
            insertToBuffer_C1(s[i], r, c);
            c++;
        }
        else
        {
            insertToBuffer_C5(s[i], r, c);
            c += CHAR_WIDTH;
        }
    }
}

void cmdLeftJustifyString(FontType font, int r, string s)
{
    cmdPlaceString(font, r, 0, s);
}

void cmdRightJustifyString(FontType font, int r, string s)
{
    int len;
    if(font == FONT_C1)
        len = s.length();
    else
        len = s.length()*CHAR_WIDTH;
    int c = PAGE_WIDTH - len;
    cmdPlaceString(font, r, c, s);
}

void cmdCenterJustifyString(FontType font, int r, string s)
{
    int len;
    if(font == FONT_C1)
        len = s.length();
    else
        len = s.length()*CHAR_WIDTH;
    int c = (PAGE_WIDTH/2) - (len/2);
    cmdPlaceString(font, r, c, s);
}

void parseCommand(const string& line)
{
    istringstream iss_line(line);

    string command;
    iss_line >> command;
    if(command == ".EOP")
    {
        if(first_page)
            first_page = false;
        else
            cout << endl;
        printPage();
        clearPage();
        return;
    }
    else if(command == ".P")
    {
        string font_str; iss_line >> font_str;
        FontType F = (font_str == "C1" ? FONT_C1 : FONT_C5);
        int R; iss_line >> R;
        int C; iss_line >> C;
        string S; iss_line.ignore(10, '|'); getline(iss_line, S, '|');
        cmdPlaceString(F, R-1, C-1, S);
    }
    else if(command == ".L")
    {
        string font_str; iss_line >> font_str;
        FontType F = (font_str == "C1" ? FONT_C1 : FONT_C5);
        int R; iss_line >> R;
        string S; iss_line.ignore(10, '|'); getline(iss_line, S, '|');
        cmdLeftJustifyString(F, R-1, S);
    }
    else if(command == ".R")
    {
        string font_str; iss_line >> font_str;
        FontType F = (font_str == "C1" ? FONT_C1 : FONT_C5);
        int R; iss_line >> R;
        string S; iss_line.ignore(10, '|'); getline(iss_line, S, '|');
        cmdRightJustifyString(F, R-1, S);
    }
    else if(command == ".C")
    {
        string font_str; iss_line >> font_str;
        FontType F = (font_str == "C1" ? FONT_C1 : FONT_C5);
        int R; iss_line >> R;
        string S; iss_line.ignore(10, '|'); getline(iss_line, S, '|');
        cmdCenterJustifyString(F, R-1, S);
    }
}


// Main Function
int main()
{
    programEntry();
    //****************************************************************//
    // init page buffer
    clearPage();

    string line;
    while(getline(cin, line))
    {
        parseCommand(line);
    }
    cout << endl;
    //****************************************************************//
    programExit();
    return 0;
}
