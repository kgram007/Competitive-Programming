//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : UVa Online Judge
// Problem ID/title : 750 - 8 Queens Chess Problem (Method 2)
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

typedef vector< vector<int> > SolutionVector;

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

void initBoardValidity(vector< vector<bool> >& board_validity)
{
    vector<bool> single_row;
    for(int i=0; i<8; ++i)
        single_row.push_back(true);

    for(int i=0; i<8; ++i)
        board_validity.push_back(single_row);
}

bool checkValidity(vector< vector<bool> >& board_validity, int r, int c)
{
    return (board_validity[r][c]);
}

void genSolution(vector<int> board_sol, vector< vector<bool> > board_validity, SolutionVector& sol_vec, int r, int c)
{
    if(r > 7 && c > 7)
        return;
    else if(r > 7)
        return;
    else if(c > 7)
    {
        //printSolution(board_sol, 0);
        sol_vec.push_back(board_sol);
        return;
    }
    else
    {
        if( checkValidity(board_validity, r, c) )
        {
            board_sol[c] = r+1;
            genSolution(board_sol, getUpdateValidity(board_validity, r, c), sol_vec, 0, c+1);
        }

        genSolution(board_sol, board_validity, sol_vec, r+1, c);
    }
}

int main()
{

    SolutionVector sol_vec;
    vector< vector<bool> > board_validity;
    initBoardValidity(board_validity);

    genSolution(vector<int>(8), board_validity, sol_vec, 0, 0);

    int T; in.get(T);
    while(T--)
    {
        int R, C;
        in.get(R); in.get(C);

        printHeading();

        int sol_num = 1;
        for(int i=0; i<(int)sol_vec.size(); ++i)
            if(sol_vec[i][C-1] == R)
                printSolution(sol_vec[i], sol_num++);

        if(T > 0)
            cout << endl;
    }
    
    return 0;
}

