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

const int MAXN = 1'000'000;

#define L(id) ((id) * 2 + 1)
#define R(id) ((id) * 2 + 2)
struct SegTree {
    struct Node {
        int mx, mxc;
        int mx2, tagmn;
        LL sum;
        void chmin(int x) {
            if(tagmn == -1) {
                tagmn = x;
            } else {
                tagmn = min(tagmn, x);
            }
            if(x < mx) {
                sum -= (LL)mxc * (mx - x);
                mx = x;
            }
        }
    } a[MAXN * 4 + 10];
    void push(int id) {
        if(a[id].tagmn != -1) {
            a[L(id)].chmin(a[id].tagmn);
            a[R(id)].chmin(a[id].tagmn);
            a[id].tagmn = -1;
        }
    }
    void pull(int id) {
        a[id].sum = a[L(id)].sum + a[R(id)].sum;
        if(a[L(id)].mx == a[R(id)].mx) {
            a[id].mx = a[L(id)].mx;
            a[id].mxc = a[L(id)].mxc + a[R(id)].mxc;
            a[id].mx2 = max(a[L(id)].mx2, a[R(id)].mx2);
        } else if(a[L(id)].mx > a[R(id)].mx) {
            a[id].mx = a[L(id)].mx;
            a[id].mxc = a[L(id)].mxc;
            a[id].mx2 = max(a[R(id)].mx, a[L(id)].mx2);
        } else {
            a[id].mx = a[R(id)].mx;
            a[id].mxc = a[R(id)].mxc;
            a[id].mx2 = max(a[L(id)].mx, a[R(id)].mx2);
        }
    }
    void build(int id, int l, int r, int* data) {
        if(l == r) {
            a[id].mx = data[l];
            a[id].mxc = 1;
            a[id].sum = data[l];
            a[id].mx2 = -1;
            a[id].tagmn = -1;
            return;
        }
        int m = (l + r) / 2;
        build(L(id), l, m, data);
        build(R(id), m + 1, r, data);
        pull(id);
        a[id].tagmn = -1;
    }
    void range_chmin(int id, int l, int r, int L, int R, int x) {
        if(l >= L && r <= R && x > a[id].mx2) {
            a[id].chmin(x);
            return;
        }
        int m = (l + r) / 2;
        push(id);
        if(L <= m) range_chmin(L(id), l, m, L, R, x);
        if(R > m)  range_chmin(R(id), m + 1, r, L, R, x);
        pull(id);
    }
    int range_max(int id, int l, int r, int L, int R) {
        if(l >= L && r <= R) return a[id].mx;
        int m = (l + r) / 2;
        int res = -1;
        push(id);
        if(L <= m) res = max(res, range_max(L(id), l, m, L, R));
        if(R > m)  res = max(res, range_max(R(id), m + 1, r, L, R));
        pull(id);
        return res;
    }
    LL range_sum(int id, int l, int r, int L, int R) {
        if(l >= L && r <= R) return a[id].sum;
        int m = (l + r) / 2;
        LL res = 0;
        push(id);
        if(L <= m) res += range_sum(L(id), l, m, L, R);
        if(R > m)  res += range_sum(R(id), m + 1, r, L, R);
        pull(id);
        return res;
    }
} seg;

int a[MAXN + 10];

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // =^-w-^=
    int T; cin >> T;
    while(T--) {
        int n, q; cin >> n >> q;
        For(i, 1, n) cin >> a[i];
        seg.build(0, 1, n, a);
        while(q--) {
            int op, l, r; cin >> op >> l >> r;
            if(op == 0) {
                int x; cin >> x;
                seg.range_chmin(0, 1, n, l, r, x);
            } else if(op == 1) {
                cout << seg.range_max(0, 1, n, l, r) << "\n";
            } else {
                cout << seg.range_sum(0, 1, n, l, r) << "\n";
            }
        }
    }
    return 0;
}
