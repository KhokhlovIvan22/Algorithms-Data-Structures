#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <limits>
using namespace std;

struct Node {
    long long value;
    long long leftBorder;
    long long rightBorder;
};

int main() {
    freopen("bst.in", "r", stdin);
    freopen("bst.out", "w", stdout);
    int n=0;
    scanf("%d", &n);
    Node* Tree = new Node[n];
    long long m;
    int p;
    char c;
    Tree[0].leftBorder = numeric_limits<long long>::min();
    Tree[0].rightBorder = numeric_limits<long long>::max();
    scanf("%lld", &m);
    Tree[0].value = m;
    for (int i = 1; i < n; ++i) {
        scanf("%lld %d %c", &m, &p, &c);
        if (c == 'L') {
            Tree[i].leftBorder = Tree[p - 1].leftBorder;
            Tree[i].rightBorder = Tree[p - 1].value - 1;
            if (m < Tree[i].leftBorder || m > Tree[i].rightBorder) {
                printf("NO");
                delete[] Tree;
                return 0;
            }
        }
        else {
            Tree[i].leftBorder = Tree[p - 1].value;
            Tree[i].rightBorder = Tree[p - 1].rightBorder;
            if (m < Tree[i].leftBorder || m > Tree[i].rightBorder) {
                printf("NO");
                delete[] Tree;
                return 0;
            }
        }
        Tree[i].value = m;
    }
    printf("YES");
    delete[] Tree;
    return 0;
}
