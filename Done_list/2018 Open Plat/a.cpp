#include<bits/stdc++.h>
#define pb emplace_back
#define AI(i) begin(i), end(i)
using namespace std;
using ll = long long;
template<class T>
bool chmax(T &val, T nv) { return val < nv ? (val = nv, true) : false; }
template<class T>
bool chmin(T &val, T nv) { return nv < val ? (val = nv, true) : false; }
#ifdef KEV
#define DE(args...) kout("[ " + string(#args) + " ] = ", args)
void kout() {cerr << endl;}
template<class T1, class ...T2>
void kout (T1 v, T2 ...e) { cerr << v << ' ', kout(e...); }
template<class T>
void debug(T L, T R) { while (L != R) cerr << *L << " \n"[next(L)==R], ++L; }
#else
#define DE(...) 0
#define debug(...) 0
#endif
// What I should check
// 1. overflow
// 2. corner cases
// Enjoy the problem instead of hurrying to AC
// Good luck !
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
const int MAX_N = 300010;
int a[MAX_N], n;
ll solve(int l, int r) {
	ll res = 0;
	for (int i = l;i <= r;++i) {
		for (int j = r;j >= i;--j) if (a[j] < a[i]) {
			res += j - i + 1;
			break;
		}
	}
	return res;
}
ll quickish_sort(int l, int r) {
	ll res = r - l + 1;

	for (int i = l;i < r;++i) {
		if (a[i] > a[i+1]) swap(a[i], a[i+1]);
	}

	vector<int> pfmx(n + 1), sufmn(n + 1);
	pfmx[l] = a[l];
	for (int i = l + 1;i <= r;++i)
		pfmx[i] = max(pfmx[i-1], a[i]);
	sufmn[r] = a[r];
	for (int i = r-1;i >= l;--i)
		sufmn[i] = min(sufmn[i+1], a[i]);

	int L = l;
	for (int i = l;i < r;++i) 
		if (pfmx[i] <= sufmn[i+1])
			res += solve(L, i), L = i+1;
	return res;

}
int32_t main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	IO("sort");
	cin >> n;
	for (int i = 1;i <= n;++i)
		cin >> a[i];
	cout << quickish_sort(1, n) << '\n';
}
