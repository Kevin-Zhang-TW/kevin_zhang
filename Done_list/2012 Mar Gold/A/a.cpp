#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
using ll = long long;
#define int ll
const int maxn = 100010;
vector<int> fac[maxn];
ll cnt[maxn];
int m, n, mod;
vector<ll> pf[maxn];
void init() {
	for (int i = 2;i <= n;++i) if (fac[i].empty()) {
		for (int j = i;j <= n;j += i)
			fac[j].pb(i);
	}
	for (int i = 1;i <= n;++i) {
		pf[i].pb(0);
		for (int j = i;j <= m;j += i) {
			pf[i].pb( pf[i].back() + m-j+1);
			pf[i].back() %= mod;
		}
	}
}
ll s, b, res;
signed main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> m >> n >> s >> b >> mod;
	s *= s, b *= b;
	init();

	for (ll i = 1;i <= n;++i) {
		ll left=m+1, right=0;
		{
			ll l = 1, r = m+1, mid;
			while (l < r) {
				mid = l + r >> 1;
				if (mid * mid + i * i < s)
					l = mid+1;
				else
					r = mid;
			}
			left = l;
		}
		{
			ll l = 0, r = m, mid;
			while (l < r) {
				mid = (l + r >> 1)+1;
				if (mid * mid + i * i > b)
					r = mid-1;
				else 
					l = mid;
			}
			right = r;
		}
		if (left > right) continue;
		auto &fac = ::fac[i];
		for (int s = 0;s < (1<<fac.size());++s) {
			int val = 1, cnt = 0;
			for (int j = 0;j < fac.size();++j) if ((1<<j) & s)
				cnt ^= 1, val *= fac[j];
			auto &v = pf[ val ];
			if (val > right) continue;
				
			ll nv = (mod + v[right/val] - v[(left-1)/val]) * 2 * (n-i+1) % mod;
			if (cnt)
				nv = -nv;
			if (nv < 0)
				nv += mod;
			res = (res + nv) % mod;
		}
	}
	if (s == 1)
		res = (res + (ll)m * (ll)(n+1) + (ll)(m+1) * (ll)n) % mod;
	cout << res << '\n';
}
