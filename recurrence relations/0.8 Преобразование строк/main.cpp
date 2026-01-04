#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int minFine(string X, string Y,int i, int j, int fine_d, int fine_i, int fine_r, vector <vector<int>>& dp)
{
	if (dp[i][j] != -1)
		return dp[i][j];
	else
	{
		if (i == 0)
			dp[i][j] = j * fine_i;
		else if (j == 0)
			dp[i][j] = i * fine_d;
		else
		{
			int charEquality = (X[i-1] == Y[j-1]) ? 0 : 1;
			dp[i][j] = min( {minFine(X, Y, i - 1, j, fine_d, fine_i, fine_r,dp) + fine_d,
				minFine(X, Y, i, j - 1, fine_d, fine_i, fine_r,dp) + fine_i,
				minFine(X, Y, i - 1, j - 1, fine_d, fine_i, fine_r,dp) + charEquality * min(fine_r,fine_d+fine_i)} );
		}
		return dp[i][j];
		}
}

int main()
{
	ifstream in("in.txt");
	ofstream out("out.txt");
	int d, i, r;
	in >> d >> i >> r;
	string X, Y;
	in >> X;
	in >> Y;
	vector <vector<int>> dp(X.length()+1, vector<int>(Y.length()+1, -1));
	out << minFine(X, Y, X.length(), Y.length(), d, i, r, dp);
	out.close();
	return 0;
}
