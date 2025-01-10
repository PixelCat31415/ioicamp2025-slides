#include <bits/stdc++.h>
#define For(i, a, b) for(int i = a; i <= b; i++)
#define Forr(i, a, b) for(int i = a; i >= b; i--)
#define F first
#define S second
#define eb emplace_back
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
using namespace std;
using LL = long long;
using pii = pair<int, int>;
using pll = pair<LL, LL>;

const int MAXN = 100'000;
const int MAXLG = 17;

vector<tuple<int, int, int, int>> adj[2][MAXLG][MAXN + 10];
LL dist[2][MAXLG][MAXN + 10];

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // =^-w-^=
    cout << (sizeof(adj) + sizeof(dist)) << "\n";
    int n, q, s; cin >> n >> q >> s;
    for(int j = 0; j < MAXLG - 1; j++) {
        for(int i = 1; i <= n; i++) {
            adj[0][j + 1][i].push_back({0, j, i, 0});
            adj[0][j + 1][i].push_back({0, j, i + (1 << j), 0});
            adj[1][j][i].push_back({1, j + 1, i, 0});
            adj[1][j][i + (1 << j)].push_back({1, j + 1, i, 0});
        }
    }
    for(int i = 1; i <= n; i++) {
        adj[0][0][i].push_back({1, 0, i, 0});
    }
    while(q--) {
        int op; cin >> op;
        if(op == 1) {
            int a, b, w; cin >> a >> b >> w;
            adj[1][0][a].push_back({0, 0, b, w});
        } else {
            int t, l, r, w; cin >> t >> l >> r >> w;
            int k = __lg(r - l + 1);
            if(op == 2) {
                adj[1][0][t].push_back({0, k, l, w});
                adj[1][0][t].push_back({0, k, r - (1 << k) + 1, w});
            } else {
                adj[1][k][l].push_back({0, 0, t, w});
                adj[1][k][r - (1 << k) + 1].push_back({0, 0, t, w});
            }
        }
    }

    using tp4i = tuple<LL, int, int, int>;
    priority_queue<tp4i, vector<tp4i>, greater<tp4i>> pq;
    memset(dist, -1, sizeof(dist));
    pq.emplace(0, 0, 0, s);
    while(!pq.empty()) {
        LL d;
        int r, k, x;
        tie(d, r, k, x) = pq.top();
        pq.pop();
        if(dist[r][k][x] != -1) continue;
        dist[r][k][x] = d;
        for(auto &e:adj[r][k][x]) {
            int e0, e1, e2, e3;
            tie(e0, e1, e2, e3) = e;
            if(dist[e0][e1][e2] == -1) {
                pq.emplace(d + e3, e0, e1, e2);
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        cout << dist[0][0][i] << " \n"[i == n];
    }
    return 0;
}
