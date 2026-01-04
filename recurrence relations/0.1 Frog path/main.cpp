#include <iostream>
#include <cstring>
using namespace std;

int dp[100001];
int B[100001];
int depth = 0;
int limit = 3000; 

int iterBoost(int* A, int m) 
{
    for (int i = 3; i <= m; ++i) 
    {
        if (dp[i] != -1) continue;
        if (dp[i-2] > dp[i-3]) 
        {
            dp[i] = A[i - 1] + dp[i-2];
            B[i] = i - 2;
        }
        else 
        {
            dp[i] = A[i - 1] + dp[i-3];
            B[i] = i - 3;
        }
    }
    return dp[m];
}

int Max(int* A, int n)
{
    if (n == 0)
        return -1000000000;
    if (n == 1)
    {
        dp[1] = A[0];
        B[1] = -1;
        return dp[1];
    }
    if (n == 2)
        return -1000000000;
    if (dp[n] == -1)
    {
        int step2, step3;
        if (depth >= limit) 
            step2 = iterBoost(A, n - 2);
        else 
        {
            ++depth;
            step2 = Max(A, n - 2);
            --depth;
        }

        if (depth >= limit) 
            step3 = iterBoost(A, n - 3);
        else 
        {
            ++depth;
            step3 = Max(A, n - 3);
            --depth;
        }

        if (step2 > step3)
        {
            dp[n] = A[n - 1] + step2;
            B[n] = n - 2;
        }
        else
        {
            dp[n] = A[n - 1] + step3;
            B[n] = n - 3;
        }
    }
    return dp[n];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    memset(dp, -1, sizeof(dp[0]) * 100001);
    memset(B, -1, sizeof(B[0]) * 100001);
    int n = 0;
    cin >> n;
    int* A = new int[n];
    for (int i = 0; i < n; ++i)
        cin >> A[i];
    if (n == 2)
        cout << -1;
    else
    {
        dp[0] = -1000000000;
        dp[1] = A[0];
        dp[2] = -1000000000;
        cout << Max(A, n) << endl;
        int* order = new int[n / 2 + 2];
        int len = 0;
        for (int i = n; i != -1; i = B[i])
            order[len++] = i;
        for (int i = len - 1; i >= 0; --i)
            cout << order[i] << ' ';
        delete[] order;
    }
    delete[] A;
    return 0;
}
