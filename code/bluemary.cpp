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

const int MAXN = 50000;
const LL INF = 9e18;

struct Line {
    double a, b;  // y = ax + b
    Line(double _a = 0, double _b = 0): a(_a), b(_b) {}
    double operator()(double x) { return a * x + b; }
};

#define L(id) ((id) * 2 + 1)
#define R(id) ((id) * 2 + 2)
struct SegTree {
    Line lns[MAXN * 4 + 10];
    void build() {
        fill(begin(lns), end(lns), Line(0, -INF));
    }
    void insert(int id, int l, int r, Line ln) {
        int m = (l + r) / 2;
        if(lns[id](m) < ln(m)) swap(lns[id], ln);
        if(l == r) return;
        if(lns[id].a > ln.a) insert(L(id), l, m, ln);
        else insert(R(id), m + 1, r, ln);
    }
    double qry(int id, int l, int r, int x) {
        int m = (l + r) / 2;
        double res = lns[id](x);
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
    int q; cin >> q;
    seg.build();
    while(q--) {
        string op; cin >> op;
        if(op[0] == 'P') {
            double s, p; cin >> s >> p;
            seg.insert(0, 1, MAXN, Line(p, s - p));
        } else {
            int t; cin >> t;
            double res = max(0.0, seg.qry(0, 1, MAXN, t));
            cout << floor(res / 100) << "\n";
            // cerr << res << "\n";
        }
    }
}
