#include <bits/stdc++.h>
#define int ll
#define F first
#define S second
#define eb emplace_back
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 100'000;

vector<pii> adj[MAXN * 3 + 10];
int dist[MAXN * 3 + 10];
int cur_nid;
#define addEdge(a, b, w) adj[a].eb(b, w)

#define L(id) ((id) * 2 + 1)
#define R(id) ((id) * 2 + 2)
struct SegTree {
    int nid[MAXN * 4 + 10];
    void build(int id, int l, int r, int rev) {
        if(l == r) {
            nid[id] = l;
            return;
        }
        nid[id] = ++cur_nid;
        int m = (l + r) / 2;
        build(L(id), l, m, rev);
        build(R(id), m + 1, r, rev);
        if(!rev) {
            addEdge(nid[id], nid[L(id)], 0);
            addEdge(nid[id], nid[R(id)], 0);
        } else {
            addEdge(nid[L(id)], nid[id], 0);
            addEdge(nid[R(id)], nid[id], 0);
        }
    }
    void link(int id, int l, int r, int L, int R, int target, int weight, int rev) {
        if(l >= L && r <= R) {
            if(!rev) addEdge(target, nid[id], weight);
            else     addEdge(nid[id], target, weight);
            return;
        }
        int m = (l + r) / 2;
        if(L <= m) link(L(id), l, m, L, R, target, weight, rev);
        if(R > m)  link(R(id), m + 1, r, L, R, target, weight, rev);
    }
} seg, ges;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // =^-w-^=
    int n, q, s; cin >> n >> q >> s;
    cur_nid = n;
    seg.build(0, 1, n, 0);
    ges.build(0, 1, n, 1);
    
    while(q--) {
        int op; cin >> op;
        if(op == 1) {
            int a, b, w; cin >> a >> b >> w;
            addEdge(a, b, w);
        } else {
            int t, l, r, w; cin >> t >> l >> r >> w;
            if(op == 2) seg.link(0, 1, n, l, r, t, w, 0);
            else        ges.link(0, 1, n, l, r, t, w, 1);
        }
    }

    memset(dist, -1, sizeof(dist));
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.emplace(0, s);
    while(!pq.empty()) {
        int d, x; tie(d, x) = pq.top(); pq.pop();
        if(dist[x] >= 0) continue;
        dist[x] = d;
        for(auto &e:adj[x]) if(dist[e.F] == -1) {
            pq.emplace(d + e.S, e.F);
        }
    }

    for(int i = 1; i <= n; i++) {
        cout << dist[i] << " \n"[i == n];
    }
    return 0;
}
