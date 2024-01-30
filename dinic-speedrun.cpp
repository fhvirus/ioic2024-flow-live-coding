#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

struct Dinic {
  struct E { int v, c, r; };
  vector<vector<E>> adj;
  void add(int u, int v, int c) {
    adj[u].push_back({ v, c, sz(adj[v]) });
    adj[v].push_back({ u, 0, sz(adj[u])-1 });
  }
  vi le, it, q;
  Dinic (int n) : adj(n), q(n) {}
  int dfs(int u, int t, int f) {
    if (u == t or f == 0) return f;
    for (int &i = it[u]; i < sz(adj[u]); ++i) {
      auto &[v, c, r] = adj[u][i];
      if (le[v] == le[u] + 1)
        if (int p = dfs(v, t, min(c, f)))
          return c -= p, adj[v][r].c += p, p;
    }
    return 0;
  }
  ll flow (int s, int t) {
    ll ans = 0; q[0] = s;
    do {
      le = it = vi(sz(q));
      int qi = 0, qe = le[s] = 1;
      while (qi < qe) {
        int u = q[qi++];
        for (auto [v, c, r]: adj[u]) {
          if (c > 0 and le[v] == 0)
            le[v] = le[u] + 1, q[qe++] = v;
        }
      }
      while (int p = dfs(s, t, INT_MAX)) ans += p;
    } while (le[t] != 0);
    return ans;
  }
};
 
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
 
	int n, m, s, t;
	cin >> n >> m >> s >> t;
 
	Dinic flow(n + 1);
	for (int a, b, c, i = 0; i < m; ++i) {
		cin >> a >> b >> c;
		flow.add(a, b, c);
	}
 
	cout << flow.flow(s, t) << '\n';
  return 0;
}
