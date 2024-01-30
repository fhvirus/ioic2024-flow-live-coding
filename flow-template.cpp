#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

struct Flow {
  void add(int u, int v, int c) {}
  ll flow(int s, int t) {}
};
 
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
 
	int n, m;
	cin >> n >> m;
 
	Flow flow(n + 1);
	for (int a, b, c, i = 0; i < m; ++i) {
		cin >> a >> b >> c;
		flow.add(a, b, c);
	}
 
	cout << flow.flow(1, n) << '\n';
  return 0;
}
