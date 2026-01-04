#include <fstream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

void distances(int v, int n, const vector<vector<pair<int, int>>>& adjacency, long long* dist)
{
	bool* processed = new bool[n];
	memset(processed, false, sizeof(processed[0]) * n);
	dist[v] = 0;
	priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> queue;
	queue.push(make_pair(0, v));
	while (!queue.empty())
	{
		pair<long long, int> cur = queue.top();
		queue.pop();
		if (processed[cur.second])
			continue;
		processed[cur.second] = true;
		dist[cur.second] = cur.first;
		for (pair<long long, int> neighbour : adjacency[cur.second])
			if (!processed[neighbour.first] && cur.first + neighbour.second < dist[neighbour.first])
				queue.push(make_pair(cur.first + neighbour.second, neighbour.first));
	}
	delete[]processed;
}

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int n, m;
	fin >> n >> m;
	vector<vector<pair<int, int>>> adjacency(n);
	int u, v, w;
	for (int i = 0; i < m; ++i)
	{
		fin >> u >> v >> w;
		adjacency[u - 1].push_back(make_pair(v-1, w));
		adjacency[v - 1].push_back(make_pair(u - 1, w));
	}
	long long* dist = new long long[n];
	fill(dist, dist+n, numeric_limits<long long>::max());
	distances(0, n, adjacency, dist);
	fout << dist[n - 1];
	return 0;
}
