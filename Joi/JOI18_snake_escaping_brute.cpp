#include <bits/stdc++.h>
#define ll long long
#define pii pair <ll, ll>
#define st first
#define nd second
#define rep(i, n, m) for (ll i = (n); i <= (m); i ++)
#define rrep(i, n, m) for (ll i = (n); i >= (m); i --)
using namespace std;
const long long INF = 1e18;
const long long N = 1e6 + 5;
const long long mask_Max = 2e6;
int n, q, L;
ll a[N], f[mask_Max];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("test.inp", "r", stdin);
    //freopen("test.out", "w", stdout);

    cin >> L >> q;
    n = 1ll << L;
    rep(i, 0, n - 1) {
        char ch;
        cin >> ch;
        a[i] = ch - '0';
    }

    rep(i, 0, n - 1) {
        rep(j, 0, n - 1) {
            ll cur = 0;
            rep(k, 0, L - 1) {
                ll val = 2;
                if (j >> k & 1) {
                    if (i >> k & 1) val = 1; else val = 0;
                }
                cur = cur * 3 + val;
            }
            f[cur] += a[i];
        }
    }

    string t;
    while (q --) {
        cin >> t;
        reverse(t.begin(), t.end());
        ll val = 0;
        rep(i, 0, L - 1) {
            if (t[i] == '1') val = val * 3 + 1;
            if (t[i] == '0') val = val * 3;
            if (t[i] == '?') val = val * 3 + 2;
        }

        cout << f[val] << '\n';
    }

    return 0;
}
