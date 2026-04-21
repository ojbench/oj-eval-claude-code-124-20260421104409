#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 1000005;
int max_val[MAXN * 4];
int lazy[MAXN * 4];

void push_up(int node) {
    max_val[node] = max(max_val[node * 2], max_val[node * 2 + 1]);
}

void push_down(int node) {
    if (lazy[node] != 0) {
        max_val[node * 2] += lazy[node];
        lazy[node * 2] += lazy[node];
        max_val[node * 2 + 1] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
        lazy[node] = 0;
    }
}

void update(int node, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
        max_val[node] += val;
        lazy[node] += val;
        return;
    }
    push_down(node);
    int mid = (l + r) / 2;
    if (ql <= mid) update(node * 2, l, mid, ql, qr, val);
    if (qr > mid) update(node * 2 + 1, mid + 1, r, ql, qr, val);
    push_up(node);
}

int query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return max_val[node];
    }
    push_down(node);
    int mid = (l + r) / 2;
    int res = 0;
    if (ql <= mid) res = max(res, query(node * 2, l, mid, ql, qr));
    if (qr > mid) res = max(res, query(node * 2 + 1, mid + 1, r, ql, qr));
    return res;
}

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int main() {
    int x, k, p;
    if (scanf("%d %d %d", &x, &k, &p) != 3) return 0;

    for (int i = 0; i < p; ++i) {
        int u = read();
        int v = read();
        int n = read();

        if (u >= v) {
            printf("T\n");
            continue;
        }

        // The interval is [u, v-1]
        if (query(1, 1, x - 1, u, v - 1) + n <= k) {
            update(1, 1, x - 1, u, v - 1, n);
            printf("T\n");
        } else {
            printf("N\n");
        }
    }

    return 0;
}
