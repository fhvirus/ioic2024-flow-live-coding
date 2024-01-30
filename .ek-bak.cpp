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

struct Flow {
  struct Edge {
    // c: 剩餘流量
    // r: 反向邊編號
    int v, c, r;
  };
  vector<vector<Edge>> adj;
  void add(int u, int v, int c) {
    adj[u].push_back({ v, c, (int) adj[v].size() });
    adj[v].push_back({ u, 0, (int) adj[u].size() - 1 });
  }
  vector<bool> vis;
  vector<int> dis;
  Flow (int n) : adj(n), vis(n), dis(n) {}
  int dfs(int u, int t, int f) {
    // f: 目前流量上限最小值
    if (u == t or f == 0) return f;
    vis[u] = true;
    for (auto &[v, c, r]: adj[u]) {
      if (vis[v] or dis[v] != dis[u] + 1) continue;
      int df = dfs(v, t, min(c, f));
      if (df <= 0) continue;
      c -= df;
      adj[v][r].c += df;
      return df;
    }
    return 0;
  }
  ll flow(int s, int t) {
    ll ans = 0, df;
    while (true) {
      fill(begin(dis), end(dis), INT_MAX);
      queue<int> q;
      q.push(s);
      dis[s] = 0;
      while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto [v, c, r]: adj[u]) {
          if (c > 0 and dis[v] == INT_MAX) {
            dis[v] = dis[u] + 1;
            q.push(v);
          }
        }
      }

      fill(begin(vis), end(vis), false);
      df = dfs(s, t, INT_MAX);
      if (df <= 0) break;
      ans += df;
    }
    return ans;
  }
};
 
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
 
	int n, m;
	cin >> n >> m;
 
	Flow ff(n + 1);
	for (int a, b, c, i = 0; i < m; ++i) {
		cin >> a >> b >> c;
		ff.add(a, b, c);
	}
 
	cout << ff.flow(1, n) << '\n';
  return 0;
}
