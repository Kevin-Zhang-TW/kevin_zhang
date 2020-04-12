#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
using ll = long long;
const int maxn = 18;
int lim, a[maxn], n;
int dp[maxn+2][1<<maxn], lst[maxn+2][1<<maxn], use[maxn+2][1<<maxn];
void init() {
	for (int i = 0;i <= maxn;++i)
		fill(dp[i]+1, dp[i]+(1<<maxn), lim+1);
}
signed main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> n >> lim;
	for (int i = 0;i < n;++i)
		cin >> a[i];

	init();

	for (int i = 0;i < n;++i)
		dp[1][1<<i] = a[i];
	int cost = n;
	for (int i = 1;i <= n;++i) {
		for (int s = 0;s < (1<<n);++s) if (dp[i][s] <= lim) {
			for (int j = 0;j < n;++j) if (~s&(1<<j)) {
				int &val = dp[i][s | (1<<j)];
				val = min(val, dp[i][s] + a[j]);
				if (val == dp[i][s] + a[j]) {
					lst[i][ s | (1<<j) ] = s;
					use[i][ s | (1<<j) ] = j+1;
				}
			}
		}
		for (int s = 0;s < (1<<n);++s) if (dp[i][s] <= lim)
			dp[i+1][s] = 0;
		if (dp[i][(1<<n)-1] <= lim) {
			cost = i;
			break;
		}
				
	}
	cout << cost << '\n';
	int now = cost, s = (1<<n)-1;
	while (cost--) {
		vector<int> id;
		while (dp[now][s]) {
			id.pb(use[now][s]);
			s = lst[now][s];
		}
		cout << id.size();
		for (int u : id) 
			cout << ' ' << u;
		cout << '\n';
		--now;
	}
}
