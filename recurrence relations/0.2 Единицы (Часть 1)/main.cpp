#include <iostream>
using namespace std;

long long dp[1001][1001];

long long countCombinations(int N,int K)
{
	if (K == 0 || K==N) return 1;
	if (K < 0 || K > N) return 0;
	if (dp[N][K] != -1) return dp[N][K];
	dp[N][K] = (countCombinations(N - 1, K - 1) + countCombinations(N - 1, K)) % 1000000007;
	return dp[N][K];
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	memset(dp, -1, sizeof(dp[0][0])*1001*1001);
	int N=0, K=0;
	cin >> N >> K;
	cout << countCombinations(N, K);
	return 0;
}
