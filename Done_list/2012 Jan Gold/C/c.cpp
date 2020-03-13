#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
using ll = long long;
const int maxn = 100010, p = 1000000007;
int n, m;
ll dp[2][maxn];
vector<int> edge[maxn];
bool vis[maxn];
void dfs(int now, int last = 0) {
	dp[0][now] = 1;
	for (int u : edge[now]) if (u && u != last) {
		dfs(u, now);
		dp[1][now] = (dp[1][now] * dp[0][u] + dp[0][now] * (dp[0][u]+dp[1][u])) % p;
		dp[0][now] = dp[0][now] * (dp[0][u]) % p;
	}
}
int od[maxn];
int cnt;
void lpc(int now, int last = 0) {
	static int t;
	//cout << "now " << now << '\n';
	od[now] = ++t;
	vis[now] = true;
	for (int u : edge[now]) if (u != last) {
		if (vis[u]) cnt += od[now] > od[u];
		else lpc(u, now);
	}
	else last = -1;
}
signed main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for (int a, b;m--;) {
		cin >> a >> b;
		assert(a != b);
		edge[a].pb(b);
		edge[b].pb(a);
	}
	ll res = 1;
	for (int i = 1;i <= n;++i) if (!vis[i]) {
		cnt = 0;
		lpc(i);
		//cout << "lpc " << cnt << '\n';
		if (cnt == 1) res = res * 2 % p;
		else if (cnt > 1) return cout << 0 << '\n', 0;
		else {
			dfs(i);
			res = res * (dp[0][i] + dp[1][i]) % p;
		}
	}
	cout << res << '\n';
}
