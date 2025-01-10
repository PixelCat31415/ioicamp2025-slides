#include <bits/stdc++.h>
#define F first
#define S second
#define eb emplace_back
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
using namespace std;
using LL = long long;
using pii = pair<int, int>;
using pll = pair<LL, LL>;

const int MAXN = 200'000;
const LL INF = 9e18;

struct Line {
    LL a, b;  // y = ax + b
    Line(LL _a = 0, LL _b = 0): a(_a), b(_b) {}
    LL operator()(LL x) { return a * x + b; }
};

#define L(id) ((id) * 2 + 1)
#define R(id) ((id) * 2 + 2)
struct SegTree {
    LL pos[MAXN + 10];
    Line lns[MAXN * 4 + 10];
    void build() {
        fill(begin(lns), end(lns), Line(0, -INF));
    }
    void insert(int id, int l, int r, Line ln) {
        int m = (l + r) / 2;
        if(lns[id](pos[m]) < ln(pos[m])) swap(lns[id], ln);
        if(l == r) return;
        if(lns[id].a > ln.a) insert(L(id), l, m, ln);
        else insert(R(id), m + 1, r, ln);
    }
    LL qry(int id, int l, int r, int x) {
        int m = (l + r) / 2;
        LL res = lns[id](pos[x]);
        if(l == r) return res;
        if(x <= m) res = max(res, qry(L(id), l, m, x));
        else res = max(res, qry(R(id), m + 1, r, x));
        return res;
    }
} seg;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // =^-w-^=
    int n, q; cin >> n >> q;
    vector<tuple<int, LL, LL>> qrys;
    vector<int> pos = {0};
    while(n--) {
        LL a, b; cin >> a >> b;
        qrys.eb(0, a, b);
    }
    while(q--) {
        int op; cin >> op;
        if(op == 0) {
            LL a, b; cin >> a >> b;
            qrys.eb(0, a, b);
        } else {
            int x; cin >> x;
            qrys.eb(1, x, x);
            pos.eb(x);
        }
    }
    sort(all(pos));
    pos.erase(unique(all(pos)), pos.end());
    int m = sz(pos);
    for(int i = 0; i < m; i++) seg.pos[i + 1] = pos[i];
    seg.build();
    for(auto &tp:qrys) {
        LL op, a, b; tie(op, a, b) = tp;
        if(op == 0) {
            seg.insert(0, 1, m, Line(-a, -b));
        } else {
            int p = (int)(upper_bound(all(pos), a) - pos.begin());
            cout << (-seg.qry(0, 1, m, p)) << "\n";
        }
    }
    return 0;
}
