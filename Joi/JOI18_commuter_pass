#include <bits/stdc++.h>
#define ll long long
#define pii pair <ll, ll>
#define st first
#define nd second
#define rep(i, n, m) for (ll i = (n); i <= (m); i ++)
#define rrep(i, n, m) for (ll i = (n); i >= (m); i --)
using namespace std;
const long long INF = 1e18;
const long long N = 1e5 + 5;

int n, m;
void dijkstra(vector <pii> *adj, ll *dist, int s) {
    rep(i, 1, n) dist[i] = INF;
    priority_queue <pii, vector <pii>, greater <pii>> q;
    q.push({0, s});
    dist[s] = 0;
    while (q.size()) {
        ll w = q.top().st, u = q.top().nd; q.pop();
        if (w > dist[u]) continue;

        for (pii x: adj[u]) {
            int v = x.st, cost = x.nd;
            ll newCost = w + cost;
            if (newCost < dist[v]) {
                dist[v] = newCost;
                q.push({dist[v], v});
            }
        }
    }
}

int U, V, S, T;
ll f[N], p[N];
vector <pii> d[N];

void initGraph() {
    rep(i, 1, m) {
        int u, v, w;
        cin >> u >> v >> w;
        d[u].push_back({v, w});
        d[v].push_back({u, w});
    }

    dijkstra(d, f, S);
    dijkstra(d, p, T);
}


namespace sub12 {
    vector <pii> g[N];
    ll ans[N];

    void solve() {
        ll mi = f[T];

        rep(i, 1, n) {
            g[i] = d[i];
            for (pii &x: g[i]) {
                ll w = x.nd, j = x.st;
                if (f[i] + w + p[j] == mi || f[j] + w + p[i] == mi)
                    x.nd = 0;
            }
        }

        dijkstra(g, ans, U);
        cout << ans[V];
    }
}

namespace sub3 {

    ll fu[N], fv[N], mi, ans;
    bool vis[N];

    void dfs(int r, int u) {
        vis[u] = true;
        ans = min(ans, min(fu[r] + fv[u], fv[r] + fu[u]));
        for (pii x: d[u])
            if (f[u] + x.nd + p[x.st] == mi && !vis[x.st])
                dfs(r, x.st);
    }

    void solve() {
        mi = f[T];
        dijkstra(d, fu, U);
        dijkstra(d, fv, V);

        ans = fu[V];
        rep(i, 1, n) if (f[i] + p[i] == mi) {
            rep(j, 1, n) vis[j] = false;
            dfs(i, i);
        }

        cout << ans << '\n';
    }
}

namespace sub4 {
    // dp on dag
    // dp[i] = shortest path from some node to V
    ll fu[N], fv[N], mi, ans, dpv[N], dpu[N];
    bool vis[N];
    
    void dfs(int u) {
        vis[u] = true;

        dpv[u] = fv[u];
        dpu[u] = fu[u];
        
        for (pii x: d[u]) {
            int v = x.st, w = x.nd;
            if (f[u] + w + p[v] == mi) {
                if (!vis[v]) dfs(v);
                dpv[u] = min(dpv[u], dpv[v]);
                dpu[u] = min(dpu[u], dpu[v]);
            }
        }
    }

    void solve() {
        mi = f[T];
        dijkstra(d, fu, U);
        dijkstra(d, fv, V);

        rep(i, 1, n) dpv[i] = dpu[i] = INF;
        dfs(S);

        ans = fu[V];
        rep(i, 1, n) ans = min(ans, min(fv[i] + dpu[i], fu[i] + dpv[i]));
        cout << ans << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> n >> m >> S >> T >> U >> V;
    initGraph();
    // if (n <= 500)
    //     sub3 :: solve();
    // else
    //     sub12 :: solve();

    sub4 :: solve();
    return 0;
}
