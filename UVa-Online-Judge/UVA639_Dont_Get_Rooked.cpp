//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : UVa Online Judge
// Problem ID/title : 639 - Dont Get Rooked
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
//#undef CHECK_RUN_TIME
//#undef INPUT_FROM_FILE
//#undef OUTPUT_TO_FILE
//******************************************//

using namespace std;

//************************* Helper *******************************//
// Helper Class: Input Stream
class InputStream
{
public:
    template<typename T>
    void get(T& x) { cin >> x; }

    template<typename T>
    void getArray(T& x, int size) { for(int i=0; i<size; ++i) cin >> x[i]; }

    int getLine(string& line) { getline(cin, line); return line.size(); }

    void getNonEmptyLine(string& line) {  while( !getLine(line) ); }
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
#ifdef INPUT_FROM_FILE
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


typedef bool CellType;
typedef vector< vector<CellType> > Board;
int N;

void printBoard(const Board& board_validity, const Board& board_wall, int r=-1, int c=-1, char ch='O')
{
    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<N; ++j)
        {
            if(i == r && j == c)
                cout << ch << " ";
            else if(board_wall[i][j])
                cout << "X" << " ";
            else
                cout << board_validity[i][j] << " ";
        }
        cout << endl;
    }
}

Board getUpdatedValidity(Board board_validity, Board& board_wall, int r, int c)
{
    // Column down
    for(int i=0; i<N; i++)
    {
        if(c+i < N)
        {
            if(board_wall[r][c+i])
                break;
            board_validity[r][c+i] = false;
        }
    }
    // Column up
    for(int i=0; i<N; i++)
    {
        if(c-i >= 0)
        {
            if(board_wall[r][c-i])
                break;
            board_validity[r][c-i] = false;
        }
    }
    // Rows right
    for(int i=0; i<N; i++)
    {
        if(r+i < N)
        {
            if(board_wall[r+i][c])
                break;
            board_validity[r+i][c] = false;
        }
    }
    // Rows left
    for(int i=0; i<N; i++)
    {
        if(r-i >= 0)
        {
            if(board_wall[r-i][c])
                break;
            board_validity[r-i][c] = false;
        }
    }
    return board_validity;
}

bool checkValidity(const Board& board_validity, const Board& board_wall, int r, int c)
{
    return (board_validity[r][c]) && (!board_wall[r][c]);
}

void getSolution(Board board_validity, Board& board_wall, int& max_rooks, int rook_count, int r, int c)
{
    if(r > N-1)
    {
        r=0; c++;
        if(c > N-1)
        {
            max_rooks = max(max_rooks, rook_count);
            return;
        }
    }

    if( checkValidity(board_validity, board_wall, r, c) )
        getSolution(getUpdatedValidity(board_validity, board_wall, r, c), board_wall, max_rooks, rook_count+1, r+1, c);

    getSolution(board_validity, board_wall, max_rooks, rook_count, r+1, c);
}

int getSolution(Board& board_validity, Board& board_wall)
{
    int max_rooks = 0;
    for(int i=0; i<N; ++i)
    {
        int max_temp = 0;
        getSolution(board_validity, board_wall, max_rooks, 0, i, 0);
        max_rooks = max(max_rooks, max_temp);
    }
    return max_rooks;
}


// Main Function
int main()
{
    programEntry();
    //******************************************//
    while(1)
    {
        in.get(N);
        if(N == 0)
            break;

        Board board_wall(N);
        Board board_validity(N);
        for(int i=0; i<N; ++i)
        {
            board_wall[i] = vector<CellType>(N);
            board_validity[i] = vector<CellType>(N);
            for(int j=0; j<N; ++j)
            {
                char ch; in.get(ch);
                if(ch == '.') board_wall[i][j] = false;
                else board_wall[i][j] = true;
                board_validity[i][j] = true;
            }
        }

        int max_rooks = getSolution(board_validity, board_wall);
        cout << max_rooks << endl;
    }
    //******************************************//
    programExit();
    return 0;
}

