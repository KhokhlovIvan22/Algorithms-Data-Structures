#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int palindromLength(const string& S, vector<vector<int>>& dp)
{
    int n = S.length();
    for (int i = 1; i <= n; ++i) 
        dp[i][i] = 1;
    for (int i = 1; i < n; ++i) 
    {
        if (S[i] == S[i+1])
            dp[i][i + 1] = 2;
        else
            dp[i][i + 1] = 1;
    }
    for (int length = 3; length <= n; ++length) 
    {
        for (int i = 1; i <= n - length + 1; ++i) 
        {
            int j = i + length - 1;
            if (S[i] == S[j])
                dp[i][j] = dp[i + 1][j - 1] + 2;
            else
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }
    }
    return dp[1][n];
}

void printPalindrom(const string& S, vector<vector<int>>& dp, ofstream& fout)
{
    int n = S.length() - 1; 
    int i = 1, j = n;
    string half;
    string middle;
    while (i <= j) 
    {
        if (i == j) 
        {
            middle=S[i];
            break;
        }
        if (S[i]==S[j])
        {
            half+=S[i];
            i++; 
            j--;
        }
        else if (dp[i][j] == dp[i + 1][j]) 
            i++;
        else 
            j--;
    }
    string rev = half;
    reverse(rev.begin(), rev.end());
    fout << half + middle + rev;
}

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    string S;
    fin >> S;
    S = " " + S;
    vector<vector<int>> dp(S.length()+1, vector<int>(S.length() + 1));
    fout << palindromLength(S, dp)<<endl;
    printPalindrom(S, dp, fout);
    return 0;
}
