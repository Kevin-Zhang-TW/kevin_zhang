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
const int MAX_N = 3005, p = 1e9 + 7;

int n;
ll A[MAX_N][2], B[MAX_N][2];
int s[MAX_N], t[MAX_N], a[MAX_N];

void clear(ll D[][2]) { memset(D, 0, sizeof(A)); }
int32_t main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	cin >> n;
	for (int i = 1;i <= n;++i)
		cin >> s[i];
	for (int i = 1;i <= n;++i)
		cin >> t[i];

	sort(s+1, s+1+n), sort(t+1, t+1+n);

	for (int i = 1, j = 1;i <= n;++i) {
		while (j <= n && s[j] <= t[i]) ++j;
		a[i] = j - 1;
		//DE(a[i]);
	}

	reverse(a+1, a+1+n);

	auto dp = A, tmp = B;
	
	dp[0][0] = 1;

	for (int i = 1;i <= n;++i) {

		clear(tmp);

		for (int j = 0;j < i;++j) for (int k = 0;k < 2;++k) {
			tmp[j + 1][k] += dp[j][k];
			tmp[j][1] += dp[j][k];
		}

		swap(tmp, dp);

		int gap = a[i] - a[i + 1];

		//DE(i, a[i], gap);

		for (int t = 0;t < gap;++t) {

			clear(tmp);

			for (int j = 0;j <= i;++j) for (int k = 0;k < 2;++k) if (dp[j][k] %= p) {
				ll old = dp[j][k];
				// if this one match with one of old ones
				if (j) 
					tmp[j - 1][k] += old * j;
				// if this one does not match with any one
				if (k == 0)
					tmp[j][k] += old;
			}

			swap(dp, tmp);
		}
	}

	ll res = dp[0][1] + dp[0][0];

	cout << res % p << '\n';
}
// consider when we encounter a prefix
// if we add it to match list
// it means it has to be matched in the end
//
// if not
// then every other dot afterward has to match something
// otherwise it can be matched with current prefix
//
// if we considering dp in other case
// it will be super hard to transfer QQ


