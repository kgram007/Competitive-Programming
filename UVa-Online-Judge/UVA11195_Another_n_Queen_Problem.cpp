//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : UVa Online Judge
// Problem ID/title : 11195 - Another n Queen Problem
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

//#undef CHECK_RUN_TIME
#ifdef CHECK_RUN_TIME
#include "Timer.h"
#endif

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
    void getArray(T& x, int size)
    {
        for(int i=0; i<size; ++i)
            cin >> x[i];
    }

    void getLine(string& line)
    {
        getline(cin, line);
    }

    void ignore()
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    void getArray(T& x, int size)
    {
        for(int i=0; i<size; ++i)
            fs_ >> x[i];
    }

    void getLine(string& line)
    {
        getline(fs_, line);
    }

    void ignore()
    {
        fs_.ignore(numeric_limits<streamsize>::max(), '\n');
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

typedef vector< vector< int > > SolutionVector;
typedef unsigned int ValidityType;
struct ValidityBoard
{
    ValidityType row;
    ValidityType diag_f;
    ValidityType diag_b;
};

#define ALL_ONES    (numeric_limits<ValidityType>::max())
#define MIN_N       (3)
#define MAX_N       (14)

int N = 3;

inline void setBit(ValidityType& board_val, int i, bool val)
{
    if(val)
        board_val |= (0x01 << i);
    else
        board_val &= ~(0x01 << i);
}

inline bool getBit(const ValidityType& board_val, int i)
{
    return (board_val >> i) & 0x01;
}

ValidityBoard getUpdateValidity(ValidityBoard board_validity, int r, int c)
{
    setBit(board_validity.row, r, false);
    setBit(board_validity.diag_f, r+c, false);
    setBit(board_validity.diag_b, N-1-c+r, false);
    return board_validity;
}

void initBoardValidity(ValidityBoard& board_validity)
{
    board_validity.row = ALL_ONES;
    board_validity.diag_f = ALL_ONES;
    board_validity.diag_b = ALL_ONES;
}

bool checkValidity(const ValidityBoard& board_validity, int r, int c)
{
    return getBit(board_validity.row, r) && getBit(board_validity.diag_f, r+c) && getBit(board_validity.diag_b, N-1-c+r);
}

int getNextValidRow(const ValidityBoard& board_validity, int r, int c)
{
    int row = -1;
    for(int i=r; i<N; ++i)
    {
        if(getBit(board_validity.row, i) && getBit(board_validity.diag_f, i+c) && getBit(board_validity.diag_b, N-1-c+i))
        {
            row = i;
            break;
        }
    }
    return row;
}

//ofstream ofs("out.txt", ios::out);
//ofstream ofs1("out1.txt", ios::out);
//
//void printSol(ofstream& f, int s[])
//{
//    for(int i=0; i<N; ++i)
//        f << s[i] << "\t";
//    f << "\n";
//}
//
//void printSol(ofstream& f, vector<int>& s)
//{
//    for(int i=0; i<N; ++i)
//        f << s[i] << "\t";
//    f << "\n";
//}
//
//void printSol_rev(ofstream& f, vector<int>& s)
//{
//    for(int i=0; i<N; ++i)
//        f << N+1-s[i] << "\t";
//    f << "\n";
//}

void genSolution_2(ValidityBoard board_validity, int& sol_count, SolutionVector& sol_vec, int r, int c, int s[])
{
    if(r > N-1)
        return;
    else if(c > N-1)
    {
        //printSol(ofs1, s);
        //ofs << "====================\n";
        sol_count++;
        return;
    }
    else
    {
        if( checkValidity(board_validity, r, c) )
        {
            s[c] = r+1;
            //printSol(ofs, s);
            genSolution_2(getUpdateValidity(board_validity, r, c), sol_count, sol_vec, 0, c+1, s);
            s[c] = 0;
        }

        genSolution_2(board_validity, sol_count, sol_vec, r+1, c, s);
    }
}

void genSolution_11(ValidityBoard board_validity, SolutionVector& sol_vec, int s[], int r, int c)
{
    if(r > N-1)
        return;
    else if(r > (N-1)/2 && c == 0)
        return;
    else if(c > N-1)
    {
        sol_vec.push_back(vector<int>(s,s+N));
        return;
    }
    else
    {
        if( checkValidity(board_validity, r, c) )
        {
            s[c] = r+1;
            genSolution_11(getUpdateValidity(board_validity, r, c), sol_vec, s, 0, c+1);
        }

        genSolution_11(board_validity, sol_vec, s, r+1, c);
    }
}
void genSolution_1(ValidityBoard board_validity, SolutionVector& sol_vec, int s[], int r, int c)
{
    if(r > N-1)
        return;
    else if(c > N-1)
    {
        sol_vec.push_back(vector<int>(s,s+N));
        return;
    }
    else
    {
        int valid_r = r;
        while((valid_r = getNextValidRow(board_validity, valid_r, c)) >= 0)
        {
            s[c] = valid_r + 1;
            genSolution_1(getUpdateValidity(board_validity, valid_r, c), sol_vec, s, 0, c+1);

            valid_r++;
            if(valid_r > (N-1)/2 && c == 0)
                break;
        }
    }
}


int findSolution(SolutionVector& sol_vec, vector< vector<int> >& invalid_places)
{
    int total_count = 0;
    int invalid_count = 0;
    for(int i=0; i<(int)sol_vec.size(); ++i)
    {
        //printSol(ofs1, sol_vec[i]);
        bool invalid = false;
        for(int j=0; j<N && !invalid; ++j)
        {
            if(invalid_places[j].empty())
                continue;
            for(int k=0; k<(int)(invalid_places[j].size()) && !invalid; ++k)
            {
                if(sol_vec[i][j] == invalid_places[j][k])
                {
                    invalid_count++;
                    invalid = true;
                }
            }
        }

        if(sol_vec[i][0]-1 != N/2)
        {
            //printSol_rev(ofs1, sol_vec[i]);
            invalid = false;
            for(int j=0; j<N && !invalid; ++j)
            {
                if(invalid_places[j].empty())
                    continue;
                for(int k=0; k<(int)(invalid_places[j].size()) && !invalid; ++k)
                {
                    if(N+1-sol_vec[i][j] == invalid_places[j][k])
                    {
                        invalid_count++;
                        invalid = true;
                    }
                }
            }
        }

        if(sol_vec[i][0]-1 == N/2)
            total_count++;
        else
            total_count += 2;
    }

    int sol_count = total_count - invalid_count;
    return sol_count;
}

void genSolution_3(ValidityBoard board_validity, vector< vector<int> >& invalid_places, int sol[], int& total_count, int& invalid_count, int r, int c)
{
    if(r > N-1)
        return;
    else if(r > (N-1)/2 && c == 0)
        return;
    else if(c > N-1)
    {
        //sol_vec.push_back(vector<int>(s,s+N));
        for(int j=0; j<N; ++j)
        {
            if(invalid_places[j].empty())
                continue;
            for(int k=0; k<(int)invalid_places[j].size(); ++k)
            {
                if(sol[j] == invalid_places[j][k])
                    invalid_count++;
                if(N-(sol[j]-1) == invalid_places[j][k])
                    invalid_count++;
            }
        }

        if(sol[0]-1 == N/2)
            total_count++;
        else
            total_count += 2;

        return;
    }
    else
    {
        if( checkValidity(board_validity, r, c) )
        {
            sol[c] = r+1;
            genSolution_3(getUpdateValidity(board_validity, r, c), invalid_places, sol, total_count, invalid_count, 0, c+1);
        }

        genSolution_3(board_validity, invalid_places, sol, total_count, invalid_count, r+1, c);
    }
}

int genSolution(ValidityBoard& board_validity, SolutionVector& sol_vec, vector< vector<int> >& invalid_places)
{
//    int s[N] = {0};
//    int sol_count = 0;
//    genSolution_2(board_validity, sol_count, sol_vec, 0, 0, s);
//    return sol_count;

//    int s[N] = {0};
//    genSolution_1(board_validity, sol_vec, s, 0, 0);
//    int sol_count = findSolution(sol_vec, invalid_places);
//    return sol_count;

//    int s[N] = {0};
//    int total_count = 0, invalid_count = 0;
//    genSolution_3(board_validity, invalid_places, s, total_count, invalid_count, 0, 0);
//    int sol_count = total_count - invalid_count;
//    return sol_count;
}


void genSolutionAndCache(ValidityBoard& board_validity, SolutionVector& sol_vec)
{
    int sol[N] = {0};
    initBoardValidity(board_validity);
    genSolution_1(board_validity, sol_vec, sol, 0, 0);
}

int main()
{
#ifdef CHECK_RUN_TIME
    Timer _run_timer;
    _run_timer.start();
#endif

    unordered_map<int, SolutionVector> sol_vec_cache;


    int testcase_num = 1;
    while(1)
    {
        int n; in.get(n);
        if(n == 0)
            break;

        N = n;

        if(sol_vec_cache.find(n) == sol_vec_cache.end())
        {
            SolutionVector sol_vec;
            ValidityBoard board_validity;
            initBoardValidity(board_validity);

            genSolutionAndCache(board_validity, sol_vec);
            sol_vec_cache[ n ] = sol_vec;
        }

        vector< vector<int> > invalid_places(N);
        for(int i=0; i<N; ++i)
        {
            for(int j=0; j<N; ++j)
            {
                char ch; in.get(ch);
                if(ch == '*')
                    invalid_places[j].push_back(i+1);
            }
        }

        int sol_count = findSolution(sol_vec_cache[n], invalid_places);
        printf("Case %d: %d\n", testcase_num++, sol_count);
    }


#ifdef CHECK_RUN_TIME
    _run_timer.printTimeMilliSec("====================\nRun Time");
#endif
    return 0;
}

