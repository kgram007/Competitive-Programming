//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : UVa Online Judge
// Problem ID/title : 750 - 8 Queens Chess Problem (Method 1)
//********************************************************************************

#define __cplusplus 201103L

#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <algorithm>

using namespace std;

// Helper Class: Input Stream
class InputStreamCin
{
public:
    InputStreamCin(bool sync_io=false)
    {
        std::ios::sync_with_stdio(sync_io);
    }
    virtual ~InputStreamCin() {};

    template<typename T>
    void get(T& x)
    {
        cin >> x;
    }

    template<typename T>
    void getArray(T* x, int size)
    {
        for(int i=0; i<size; ++i)
            cin >> x[i];
    }

    string getLine()
    {
        string line;
        getline(cin, line);
        return line;
    }
};

class InputStreamFile
{
public:
    InputStreamFile(string file)
    {
        fs_.open(file);
    }
    virtual ~InputStreamFile()
    {
        fs_.close();
    }

    template<typename T>
    void get(T& x)
    {
        fs_ >> x;
    }

    template<typename T>
    void getArray(T* x, int size)
    {
        for(int i=0; i<size; ++i)
            fs_ >> x[i];
    }

    string getLine()
    {
        string line;
        getline(fs_, line);
        return line;
    }

private:
    ifstream fs_;
};

// Input Stream variable
//#undef INPUT_FROM_FILE
#ifdef INPUT_FROM_FILE
InputStreamFile in("test.txt");
#else
InputStreamCin in(false);
#endif

void printBoardMatrix(const vector< vector<bool> >& board)
{
    for(int i=0; i<8; ++i)
    {
        for(int j=0; j<8; ++j)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

void printHeading()
{
    cout << "SOLN       COLUMN" << endl;
    cout << " #     ";
    for(int i=1; i<=8; ++i)
        cout << " " << i;
    cout << endl << endl;;
}

void printSolution(const vector<int>& board_sol, int sol_num)
{
    if(sol_num < 10)
        cout << " ";
    cout << sol_num << "     ";
    for(int i=0; i<8; ++i)
        cout << " " << board_sol[i];
    cout << endl;
}

void initBoardSol(vector<int>& board, int R, int C)
{
    for(int i=0; i<8; ++i)
        board.push_back(0);
    board[C-1] = R;
}

vector< vector<bool> > getUpdateValidity(vector< vector<bool> > board_validity, int r, int c)
{
    for(int i=0; i<8; ++i)
    {
        board_validity[r][i] = false;
        board_validity[i][c] = false;
        if(r-c+i >= 0 && r-c+i < 8)
            board_validity[r-c+i][i] = false;
        if(r+c-i >= 0 && r+c-i < 8)
            board_validity[r+c-i][i] = false;
    }

    return board_validity;
}

void initBoardValidity(vector< vector<bool> >& board_validity, int r, int c)
{
    vector<bool> single_row;
    for(int i=0; i<8; ++i)
        single_row.push_back(true);

    for(int i=0; i<8; ++i)
        board_validity.push_back(single_row);

    board_validity = getUpdateValidity(board_validity, r, c);
    board_validity[r][c] = true;
}

bool checkValidity(vector< vector<bool> >& board_validity, int r, int c)
{
    return (board_validity[r][c]);
}

bool solveBoard(vector<int> board_sol, vector< vector<bool> > board_validity, int r, int c, int& sol_num)
{
    if(r > 7 && c > 7)
        return true;
    else if(r > 7)
        return false;
    else if(c > 7)
    {
        printSolution(board_sol, sol_num++);
        return true;
    }
    else
    {
        bool success;
        if( checkValidity(board_validity, r, c) )
        {
            board_sol[c] = r+1;
            success = solveBoard(board_sol, getUpdateValidity(board_validity, r, c), 0, c+1, sol_num);
        }

        success = solveBoard(board_sol, board_validity, r+1, c, sol_num);

        return success;
    }
}

int main()
{
    int T; in.get(T);
    while(T--)
    {
        int R, C;
        in.get(R); in.get(C);

        vector< int > board_sol;
        initBoardSol(board_sol, R, C);

        vector< vector<bool> > board_validity;
        initBoardValidity(board_validity, R-1, C-1);

        printHeading();

        int sol_num = 1;
        solveBoard(board_sol, board_validity, 0, 0, sol_num);

        if(T > 0)
            cout << endl;
    }
    
    return 0;
}

