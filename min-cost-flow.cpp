#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#ifdef NONTOI
#define debug(args...) LKJ("\033[1;32m["#args"]\033[0m", args)
template<class I> void LKJ(I&&x){ cerr << x << '\n'; }
template<class I, class...T> void LKJ(I&&x, T&&...t)
{ cerr << x << ", ", LKJ(t...); }
template<class I> void print(I a, I b)
{ while(a < b) cerr << *a << " \n"[next(a) == b], ++a; }
#else
#define debug(...) 0
#define print(...) 0
#endif

struct MinCostFlow {
  struct E { int v, c; ll k; int r, rc; };
  vector<vector<E>> adj;
  vector<int> par, par_eid; // SPFA 的來源和邊編號
  MinCostFlow(int n): adj(n), par(n), par_eid(n) {}
  void add(int u, int v, int c, ll k) {
    adj[u].push_back({v, c, k, (int) adj[v].size(), c});
    adj[v].push_back({u, 0, -k, (int) adj[u].size() - 1, 0});
  }
  ll spfa(int s, int t) { // 就是普通的 SPFA
    fill(begin(par), end(par), -1);
    vector<ll> dis(par.size(), LLONG_MAX); // 路徑長
    vector<bool> in_q(par.size(), false);
    queue<int> q;
    dis[s] = 0; q.push(s); in_q[s] = true;
    while (!q.empty()) {
      int u = q.front(); q.pop(); in_q[u] = false;
      for (int i = 0; i < (int) adj[u].size(); ++i) {
        auto &[v, c, k, r, rc] = adj[u][i];
        if (rc > 0 and dis[u] + k < dis[v]) {
          dis[v] = dis[u] + k;
          par[v] = u;
          par_eid[v] = i;
          if (!in_q[v]) q.push(v);
          in_q[v] = true;
        }
      }
    }
    return dis[t];
  }
  pair<int, ll> flow(int s, int t) {
    // SPFA 找費用最小的路徑
    int flow = 0;
    ll cost = 0, d;
    while ((d = spfa(s, t)) < LLONG_MAX) {
      int cur = INT_MAX; // 找可以擴充的流量
      for (int u = t; u != s; u = par[u]) 
        cur = min(cur, adj[par[u]][par_eid[u]].rc);
      flow += cur, cost += d * cur;
      for (int u = t; u != s; u = par[u]) { // 擴充他
        adj[par[u]][par_eid[u]].rc -= cur;
        adj[u][ adj[par[u]][par_eid[u]].r ].rc += cur;
      }
    }
    return make_pair(flow, cost);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  MinCostFlow mcf(n+1);
  for (int u, v, c, k, i = 0; i < m; ++i) {
    cin >> u >> v >> c >> k;
    mcf.add(u, v, c, k);
  }

  auto [flow, cost] = mcf.flow(1, n);
  cout << flow << ' ' << cost << '\n';

  return 0;
}
