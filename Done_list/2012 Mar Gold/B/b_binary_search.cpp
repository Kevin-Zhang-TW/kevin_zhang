#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
using ll = long long;
const int maxn = 100010;
int n, b[maxn];
#define int ll
ll a[maxn];
ll cost(int val) {
	ll res = abs(val);
	for (int i = 1;i < n;++i)
		res += abs(a[i] - val);
	return res + abs(a[n]);
}
signed main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1;i <= n;++i)
		cin >> a[i] >> b[i];
	for (int i = 1;i <= n;++i)
		a[i] += a[i-1] -b[i];
	int l = -1000000000, r = 1000000000, m;
	while (l < r) {
		m = (l + r >> 1)+1;
		if (cost(m) > cost(m-1))
			r = m-1;
		else if (cost(m) < cost(m-1))
			l = m;
		else
			l = r = m;
	}
	cout << cost(l) << '\n';
}


