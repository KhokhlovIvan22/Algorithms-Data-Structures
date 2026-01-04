#include "fstream"
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

int minFine(int n, int *positions)
{
	vector<vector<int>> dp(n + 1, vector<int>(n + 1));
	for (int i = 1; i < n + 1; ++i)
		dp[i][i] = 0;
	for (int length = 2; length < n + 1; ++length)
		for (int i = 1; i <= n - length + 1; ++i)
		{
			int j = i + length - 1;
			int cur = 0;
			dp[i][j] = INT_MAX;
			for (int k = i; k < j; ++k)
			{
				cur = dp[i][k] + dp[k + 1][j] + abs(positions[k] - positions[j]);
				if (cur < dp[i][j])
					dp[i][j] = cur;
			}
		}
	return dp[1][n];
}

int main() 
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int n;
	fin >> n;
	int* positions = new int[n+1];
	int num;
	for (int i = 1; i < n + 1; ++i)
	{
		fin >> num;
		positions[num] = i;
	}
	fout << minFine(n, positions);
	delete[]positions;
	return 0;
}
