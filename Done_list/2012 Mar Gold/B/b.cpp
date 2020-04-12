#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
using ll = long long;
const int maxn = 100010;
int n, b[maxn];
ll a[maxn];
signed main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1;i <= n;++i)
		cin >> a[i] >> b[i];
	for (int i = 1;i <= n;++i)
		a[i] += a[i-1] -b[i];

	nth_element(a, a+n/2, a+n);
	int g = a[n/2];
	ll res = 0;
	for (int i = 0;i < n;++i) {
		res += abs(a[i]-g);
	}
	cout << res + abs(a[n]) << '\n';

}
