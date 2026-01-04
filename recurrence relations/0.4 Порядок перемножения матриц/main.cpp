#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

int matrixMul(int* N, int* M, int S)
{
    vector<vector<int>> dp(S + 1, vector<int>(S + 1, 0));
    for (int i = 1; i < S+1; ++i)
    {
        dp[i][i] = 0;
    }
    for (int c = 2; c < S+1; ++c)
        for (int i = 1; i < S - c + 2; ++i)
        {
            int min = INT_MAX;
            int cur;
            int j;
            j = c + i - 1;
            for (int k = i; k < j; ++k)
            {
                cur = N[i-1] * M[k-1] * M[j-1] + dp[i][k] + dp[k + 1][j];
                if (cur < min)
                    min = cur;
            }
            dp[i][j] = min;
        }
    return dp[1][S];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int S;
    fin >> S;
    int* N = new int[S];
    int* M = new int[S];
    for (int i = 0; i < S; ++i)
    {
        fin >> N[i];
        fin >> M[i];
    }
    fout << matrixMul(N, M, S);
    delete[]N;
    delete[]M;
    return 0;
}
