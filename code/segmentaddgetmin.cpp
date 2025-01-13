#include <bits/stdc++.h>
#define int LL
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

const int MAXN = 400'000;
const int INF = 2e18;

struct Line {
    int a, b;  // ax + b
    Line(int _a = 0, int _b = 0): a(_a), b(_b) {}
    int operator()(const int &x) {
        return a * x + b;
    }
};

#define L(id) ((id) * 2 + 1)
#define R(id) ((id) * 2 + 2)
struct SegTree {
    int* pos;
    Line a[MAXN * 4 + 10];
    void build(int* _pos) {
        pos = _pos;
        fill(begin(a), end(a), Line(0, INF));
    }
    void insert(int id, int l, int r, Line ln) {
        int m = (l + r) / 2;
        if(ln(pos[m]) < a[id](pos[m])) swap(a[id], ln);
        if(l == r) return;
        if(ln.a > a[id].a) insert(L(id), l, m, ln);
        else insert(R(id), m + 1, r, ln);
    }
    void insert(int id, int l, int r, int L, int R, Line ln) {
        if(l >= L && r <= R) {
            insert(id, l, r, ln);
            return;
        }
        int m = (l + r) / 2;
        if(L <= m) insert(L(id), l, m, L, R, ln);
        if(R > m)  insert(R(id), m + 1, r, L, R, ln);
    }
    int qry(int id, int l, int r, int x) {
        int res = a[id](pos[x]);
        if(l == r) return res;
        int m = (l + r) / 2;
        if(x <= m) res = min(res, qry(L(id), l, m, x));
        else       res = min(res, qry(R(id), m + 1, r, x));
        return res;
    }
} seg;

int pos[MAXN + 10];

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // =^-w-^=
    using tp5i = tuple<int, int, int, int, int>;
    vector<tp5i> evts;
    vector<int> vp = {0};
    int n, q; cin >> n >> q;
    while(n--) {
        int l, r, a, b; cin >> l >> r >> a >> b; r--;
        evts.eb(0, l, r, a, b);
    }
    while(q--) {
        int op; cin >> op;
        if(op == 0) {
            int l, r, a, b; cin >> l >> r >> a >> b; r--;
            evts.eb(0, l, r, a, b);
        } else {
            int p; cin >> p;
            evts.eb(1, p, 0, 0, 0);
            vp.eb(p);
        }
    }
    sort(all(vp));
    vp.erase(unique(all(vp)), vp.end());
    int m = sz(vp);
    For(i, 0, m - 1) pos[i + 1] = vp[i];
    seg.build(pos);
    for(auto &evt:evts) {
        int op, l, r, a, b; tie(op, l, r, a, b) = evt;
        if(op == 0) {
            l = lower_bound(pos + 1, pos + m + 1, l) - pos;
            r = upper_bound(pos + 1, pos + m + 1, r) - pos - 1;
            if(l <= r) seg.insert(0, 1, m, l, r, Line(a, b));
        } else {
            l = lower_bound(pos + 1, pos + m + 1, l) - pos;
            int res = seg.qry(0, 1, m, l);
            if(res >= INF) cout << "INFINITY\n";
            else cout << res << "\n";
        }
    }
    return 0;
}
