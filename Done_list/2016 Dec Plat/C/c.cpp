#include<bits/stdc++.h>
#define pb emplace_back
#define AI(i) begin(i), end(i)
using namespace std;
using ll = long long;
#ifdef KEV
#define DE(args...) cerr << "[" << #args << "] = ", kout(args)
void kout() {cerr << endl;}
template<class T1, class ...T2>
void kout (T1 v, T2 ...e) { cerr << v << ' ', kout(e...); }
void debug(auto L, auto R) { while (L != R) cerr << *L << " \n"[next(L)==R], ++L; }
#else
#define DE(...) 0
void debug(...) {}
#endif
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
const int maxn = 100010;
const ll inf = 1ll << 58;
int n, k;
vector<ll> cand[maxn];
ll osum, gensum, gencnt;
void dfs(int now, ll sum, ll mx) {
	if (sum > mx) return;
	if (now == n)
		return;

	if (gencnt >= k) return;

	for (ll v : cand[now]) {
		if (v + sum > mx) break;
		DE(now, v + sum);
		++gencnt;
		gensum += v + sum;
		dfs(now+1, v + sum, mx);
		if (gencnt >= k) return;
	}
	if (sum + cand[now][0] <= mx)
		dfs(now+1, sum, mx);
}
ll count(ll mx) {
	DE(mx);
	gensum = osum, gencnt = 1;
	dfs(0, osum, mx);
	return gencnt;
}
ll solve() {
	if (k == 1) return osum;

	sort(cand, cand+n, [&](const vector<ll> &a, const vector<ll> &b) {
		return a[0] < b[0];
		});

	ll L = osum, R = osum, M;
	for (int i = 0;i < n;++i) {
		R += cand[i].back();
	}

	while (L < R) {
		M = L + R >> 1;
		if (count(M+1) >= k)
			R = M;
		else
			L = M + 1;
	}
	count(L);
	DE(L);
	assert(gencnt <= k);

	return gensum + (k - gencnt) * (L+1);
}
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	IO("roboherd");
	cin >> n >> k;
	for (int s, i = 0;i < n;++i) {
		cin >> s;
		cand[i].resize(s);
		for (auto &v : cand[i])
			cin >> v;
		sort(AI(cand[i]));
		osum += cand[i][0];
		for (int j = 1;j < s;++j)
			cand[i][j] -= cand[i][0];
		cand[i].erase(begin(cand[i]));
		if (s == 1) 
			--n, --i;
	}
	cout << solve() << '\n';
}
