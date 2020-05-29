#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
using ll = long long;
const int maxn = 1010, p = 2012;
char w[maxn];
int n, dp[maxn][maxn], pf[maxn];
#define V(i) (i == '(' ? 1 : -1)
/*
ID: ckevin31
LANG: C++14
TASK: 
*/
#ifndef KEV
inline void IO(string name) {
	freopen((name + ".in").c_str(), "r", stdin);
	freopen((name + ".out").c_str(), "w", stdout);
}
#else
inline void IO(string name){}
#endif
signed main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	IO("bbreeds");
	cin >> w+1;
	n = strlen(w+1);
	int a = count(w+1, w+1+n, '(');
	if (a + a != n) return cout << 0 << '\n', 0;
	dp[0][0] = 1;
	for (int i = 1;i <= n;++i) {
		pf[i] = pf[i-1] + V(w[i]);
		int b = pf[i-1];
		if (w[i] == '(') {
			for (int j = 0;j <= n;++j) {
				int val = dp[i-1][j];
				dp[i][j] += val;
				dp[i][j+1] += val;
			}
		}
		if (w[i] == ')') {
			for (int j = 0;j <= n;++j) {
				int val = dp[i-1][j];
				if (j) dp[i][j-1] += val;
				if (b-j>0) dp[i][j] += val;
			}
		}
		for (int j = 0;j <= n;++j)
			dp[i][j] %= p;
	}
	cout << dp[n][0] << '\n';
}
