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
const long long N = 2e5 + 5;
 
ll dp[N][3], n, m, ans;
char a[3005][3005];
 
bool check(char a, char b, char c) {
    return a == 'R' && b == 'G' && c == 'W';
}
 
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifndef ONLINE_JUDGE
        //freopen(file".inp", "r", stdin); freopen(file".out", "w", stdout);
    #endif
    
    cin >> n >> m;
    rep(i, 1, n) rep(j, 1, m) cin >> a[i][j];
 
    rep(s, 2, n + m) {
        
        ll res = 0;
        rep(j, 1, m) dp[j][1] = dp[j][2] = 0;
 
        rep(j, 1, m) {
            int i = s - j;
            if (i < 1 || i > n) continue;
 
            // 1: vertical
            // 2: horizontal
 
            { // no dango
                dp[j][1] = max(dp[j - 1][1], dp[j - 1][2]);
 
                if (j > 3)
                    dp[j][2] = max(dp[j - 1][2], dp[j - 3][1]);
            }
 
            { // if can make dango
                if (i > 2 && check(a[i - 2][j], a[i - 1][j], a[i][j]))
                    dp[j][1] ++;
                
                if (j > 2 && check(a[i][j - 2], a[i][j - 1], a[i][j]))
                    dp[j][2] ++;
            }
            
            res = max(res, max(dp[j][1], dp[j][2]));
        }
        ans += res;
    }
 
    cout << ans << '\n';
 
    return 0;
}    
/**  /\_/\
*   (= ._.)
*   / >🍵 \>🍮
 
dp on diagonal
i, j is the position of dago end with 'w'
**/
