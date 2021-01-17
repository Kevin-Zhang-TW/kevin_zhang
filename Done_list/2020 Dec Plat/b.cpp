#include<bits/stdc++.h>
#define pb emplace_back
#define AI(i) begin(i), end(i)
using namespace std;
using ll = long long;
template<class T> bool chmin(T &a, T b) { return b < a && (a = b, true); }
template<class T> bool chmax(T &a, T b) { return a < b && (a = b, true); }
#ifdef KEV
#define DE(args...) kout("[ " + string(#args) + " ] = ", args)
void kout() {cerr << endl;}
template<class T, class ...U> void kout (T v, U ...e) { cerr << v << ' ', kout(e...); }
template<class T> void debug(T L, T R) { while (L != R) cerr << *L << " \n"[next(L)==R], ++L; }
#else
#define DE(...) 0
#define debug(...) 0
#endif
// What I should check
// 1. overflow
// 2. corner cases
// Enjoy the problem instead of hurrying to AC
// Good luck !
const int MAX_N = 61, p = 1e9 + 7;

int dp[MAX_N][MAX_N << 1][MAX_N << 1];
int n, k, q, con[MAX_N][MAX_N];
int bs[MAX_N], s[MAX_N], bt[MAX_N], t[MAX_N];
int bl[MAX_N << 1], br[MAX_N << 1];

void add(int &a, int b) { a += b - p, a += (a >> 31) & p; }

void solve_all() {
	for (int button = 1;button <= k;++button) {

		memcpy(dp[button], dp[button-1], sizeof(dp[0]));

		for (int mid = 0;mid < n;++mid) {
			memset(bl, 0, sizeof(bl));
			memset(br, 0, sizeof(br));

			for (int lst = 0;lst < n;++lst) {
				if (con[lst][mid])
					for (int j = 0;j < n + q;++j)
						add(bl[j], dp[button-1][j][lst]);
				if (con[mid][lst])
					for (int j = 0;j < n + q;++j)
						add(br[j], dp[button-1][lst][j]);
			}

			add(bl[mid], 1);
			add(br[mid], 1);

			for (int i = 0;i < q;++i) {
				if (bs[i] == button && s[i] == mid)
					add(bl[i + n], 1);
				if (bt[i] == button && t[i] == mid)
					add(br[i + n], 1);
			}

			for (int i = 0;i < n + q;++i)
				for (int j = 0;j < n + q;++j) {
					add(dp[button][i][j], 1ll * bl[i] * br[j] % p);
				}
		}
	}
}
int32_t main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> n >> k >> q;
	for (int i = 0;i < n;++i) for (int j = 0;j < n;++j) {
		char x; cin >> x;
		con[i][j] = x - '0';
	}
	for (int i = 0;i < q;++i) {
		cin >> bs[i] >> s[i] >> bt[i] >> t[i];
		--s[i], --t[i];
	}

	solve_all();

	for (int i = 0;i < q;++i)
		cout << dp[k][i + n][i + n] << '\n';
}
