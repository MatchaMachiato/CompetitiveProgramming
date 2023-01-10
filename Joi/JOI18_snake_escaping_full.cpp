#include <bits/stdc++.h>
#define ll long long
#define pii pair<ll, ll>
#define st first
#define nd second
#define file "test"
#define rep(i, begin, end) for (ll i = (begin); i <= (end); i ++)
#define rrep(i, begin, end) for (ll i = (begin); i >= (end); i --)
using namespace std;
const long long INF = 1e18;
const long long N = 2e6 + 5;

int a[N], L, q, n;

ll dp[2][N];

// dp[bit][mask] = sum of mask such bit on = bit

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifndef ONLINE_JUDGE
        freopen(file".inp", "r", stdin); freopen(file".out", "w", stdout);
    #endif
    
    cin >> L >> q;  
    n = 1 << L;

    rep(i, 0, n - 1) {
        char ch; cin >> ch;
        a[i] = ch - '0';
    }

    rep(bit, 0, 1) {
        rep(mask, 0, n - 1) dp[bit][mask] = a[bit == 0 ? (n - 1 - mask) : mask];
        rep(i, 0, L - 1) rep(mask, 0, n - 1) 
            if (mask >> i & 1)
                dp[bit][mask] += dp[bit][mask ^ (1 << i)];
    }   

    string s;

    while (q --) {
        int na = 0, nb = 0, nc = 0, ma = 0, mb = 0, mc = 0;
        cin >> s;
        reverse(s.begin(), s.end());

        rep(i, 0, L - 1) {
            if (s[i] == '1') {
                na ++; ma ^= 1 << i;
            }

            if (s[i] == '0') {
                nb ++; mb ^= 1 << i;
            }

            if (s[i] == '?') {
                nc ++; mc ^= 1 << i;
            }
        }

        if (nc <= na && nc <= nb) {
            ll ans = 0;
            for (int i = mc; ; i = (i - 1) & mc) {
                ans += a[i ^ ma];
                if (i == 0) break;
            }            

            cout << ans << '\n';
        } else {
            int bit = 1, mask = ma, other = mb;
            if (nb < na) {
                bit = 0;
                mask = mb;
                other = ma;
            }

            ll ans = 0;
            int bb = __builtin_popcount(mask) & 1;
            for (int i = mask; ; i = (i - 1) & mask) {
                if ((__builtin_popcount(i) & 1) == bb) {
                    ans += dp[bit][i ^ mc];;
                }
                else    {
                    ans -= dp[bit][i ^ mc];
                }
                if (i == 0) break;
            }

            cout << ans << '\n';
        }
    }

    return 0;
}    
/**  /\_/\
*   (= ._.)
*   / >🍵 \>🍮

3 case
cnt 0 min
cnt 1 min
cnt ? min

-> handle each case in 2^cnt, cnt <= L / 3 -> O(q * 2 ^ (L / 3));
solving for ? -> brute
solving for 1 or 0 -> inclusive exclusive using dp sos fast

**/
