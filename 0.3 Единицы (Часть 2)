#include <iostream>
#include <cstring>
using namespace std;

const int mod = 1000000007;

long long binPow(long long B, long long N)
{
    B %= mod;
    if (N == 0) return 1;
    if (N == 1) return B;
    long long t = binPow(B, N / 2) % mod;
    if ((N & 1) == 0)
        return (t * t) % mod;
    else
        return ((t * t) % mod * B) % mod;
}

long long mul(int l, int r)
{
    if (l > r) return 1;
    if (l == r) return l % mod;
    int m = (l + r) / 2;
    long long left = mul(l, m);
    long long right = mul(m + 1, r);
    return (left * right) % mod;
}

long long countCombinations(int N, int K, int max)
{
    if (K == 0 || K == N) return 1;
    long long higher = mul(max + 1, N);         
    long long lower = binPow(mul(1, N-max), mod - 2);
    return (higher * lower) % mod;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N = 0, K = 0;
    cin >> N >> K; 
    int max = (K > N - K ? K : N - K);
    cout << countCombinations(N, K, max);
    return 0;
}
