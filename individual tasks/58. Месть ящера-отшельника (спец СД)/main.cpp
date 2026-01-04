#include <iostream>
#include <algorithm>
using namespace std;

int findNextFree(int* parent, int it) 
{
    if (parent[it] == it) 
        return it;
    parent[it] = findNextFree(parent, parent[it]);
    return parent[it];
}

int main() 
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int N, K;
    cin >> N >> K;
    int* a = new int[N];
    int* b = new int[N];
    int* parent = new int[N + 1];
    for (int i = 0; i <= N; ++i)
        parent[i] = i;
    for (int i = 0; i < N; ++i) 
        cin >> a[i];
    for (int i = 0; i < N; ++i) 
        cin >> b[i];
    sort(a, a + N);
    sort(b, b + N, greater<int>());
    int* deltas = new int[N];
    memset(deltas, -1, sizeof(deltas[0]) * N);
    long long sum = 0;
    int mandatory = 0;
    for (int i = 0; i < N; ++i) 
    {
        int pos = lower_bound(a, a + N, b[i]) - a;
        int nextFree = (pos < N ? findNextFree(parent, pos) : N);
        if (nextFree < N) 
        {
            sum += a[nextFree];
            deltas[nextFree] = a[nextFree] - b[i];
            parent[nextFree] = findNextFree(parent, nextFree + 1);
        }
        else 
        {
            sum += b[i];
            ++mandatory;
            if (mandatory > K) 
            {
                cout << -1;
                delete[] a; 
                delete[] b; 
                delete[] parent; 
                delete[] deltas;
                return 0;
            }
        }
    }
    if (K - mandatory > 0) 
    {
        sort(deltas, deltas + N, greater<int>());
        for (int i = 0; i < K - mandatory && i < N; ++i) 
        {
            if (deltas[i] > 0) 
                sum -= deltas[i];
            else break;
        }
    }
    cout << sum;
    delete[] a; 
    delete[] b; 
    delete[] parent; 
    delete[] deltas;
    return 0;
}
