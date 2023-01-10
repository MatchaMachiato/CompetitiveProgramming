/*
each dango is a node, if two dangos intersect we create an edge -> this is a bipartite graph
so we need to find the maximum indepent set = number of node - maximum matching (only on bipartite)
*/
#include <bits/stdc++.h>
#define ll long long
#define pii pair <ll, ll>
#define st first
#define nd second
#define rep(i, n, m) for (ll i = (n); i <= (m); i ++)
#define rrep(i, n, m) for (ll i = (n); i >= (m); i --)
using namespace std;
const long long INF = 1e18;
const long long N = 3000 + 5;

char a[N][N];
ll n, m;

bool cut(pii ver, pii hor) {
    rep(i, -2, 0) rep(j, -2, 0)
        if (make_pair(ver.st + i, ver.nd) == make_pair(hor.st, hor.nd + j))
            return true;
    return false;
}

vector <pii> ver, hor;

bool check(char a, char b, char c) {
    return a == 'R' && b == 'G' && c == 'W';
}

int id(int i, int j) {
    return (i - 1) * m + j;
}

ll cap[N + 2000][N + 2000];
//map <int, map<int, ll>> cap;
ll vis[N * 1000], mx, par[N * 1000];
vector <int> d[N * 1000];

ll bfs(ll s, ll t) {
    queue <pii> q;
    rep(i, 0, mx + 1) vis[i] = false, par[i] = -1;
    par[s] = -2;
    vis[s] = 1;

    q.push({s, INF});
    while (q.size()) {
        int u = q.front().st;
        ll flow = q.front().nd;
        q.pop();

        for (int v: d[u]) if (par[v] == -1 && cap[u][v]) {
            par[v] = u;
            ll newflow = min(flow, cap[u][v]);
            if (v == t) return newflow;
            q.push({v, newflow});
        }
    }

    return 0;
}

ll maxFlow() {
    ll flow = 0, tmp;
    while (tmp = bfs(0, mx + 1)) {
        flow += tmp;
        int u = mx + 1;
        while (u != 0) {
            int cur = u, pre = par[u];
            cap[pre][cur] -= tmp;
            cap[cur][pre] += tmp;
            u = pre;
        }
    }

    return flow;
}

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;

    rep(i, 1, n) rep(j, 1, m) cin >> a[i][j];
    rep(i, 1, n)
        rep(j, 1, m) {
            if (j >= 3 && check(a[i][j - 2], a[i][j - 1], a[i][j]))
                hor.push_back({i, j});
            if (i >= 3 && check(a[i - 2][j], a[i - 1][j], a[i][j]))
                ver.push_back({i, j});
        }

    int buff = hor.size();
    int u = buff, v;
    for (pii x: ver) {
        u ++;
        v = 0;
        for (pii y: hor) {
            v ++;
            if (cut(x, y)) {
                d[u].push_back(v);
                d[v].push_back(u);
                cap[u][v] = cap[v][u] = 1;
            }
        }
    }

    mx = hor.size() + ver.size();

    rep(i, 1, buff) {
        d[0].push_back(i);
        d[1].push_back(0);
        cap[0][i] = 1;
    }

    int t = mx + 1;
    rep(i, buff + 1, mx) {
        d[t].push_back(i);
        d[i].push_back(t);
        cap[i][t] = 1;
    }

    ll tmp = maxFlow();
    cout << mx - tmp << '\n';

    return 0;
}
