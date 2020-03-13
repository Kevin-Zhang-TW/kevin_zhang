#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
using ll = long long;
const int maxn = 15;
int n, m, k;
char w[maxn];
int v[2][2][2][maxn];
#define tov(i) ((i) == 'T')
bool ok(int,ll);
bool solve_both(int,int,ll);
ll adv(ll ov, int i, int bs, int ss) {
	return (ov * v[bs][ss][tov('T')][i] + ov + v[bs][ss][tov('B')][i]) % m;
}
int mr() {
	return rand() > ( RAND_MAX / 2);
}
signed main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m >> k >> w;
	srand(uint64_t(new char));
	for (int i = 0;i < n;++i) {
		for (int s : {tov('T'), tov('B')})
			for (int ss : {tov('T'), tov('B')})
				cin >> v[s][ss][tov('T')][i] >> v[s][ss][tov('B')][i];//, cerr << v[s][ss][tov('T')][i] << ' ';
		//cerr << '\n';
	}
	ll r = 0;
	for (int i = 0;i < n;++i) {
		//cout << "\nr " << r << '\n';
		if (solve_both(i, tov('B'), r)) {
			putchar('B');
			r = adv(r, i, tov('B'), tov(w[i]));
		}
		else {
			putchar('T');
			r = adv(r, i, tov('T'), tov(w[i]));
		}
	}
	putchar('\n');
}

bool ok(int now, ll r) {
	int v = mr();
	return solve_both(now, v, r) || solve_both(now, !v, r);
}
bool solve_both(int now, int side, ll r) {
	if (now == n) return min(m-r, r) <= k;
	int v = mr();
	return ok(now+1, adv(r, now, side, v)) && 
		ok(now+1, adv(r, now, side, !v));
}
