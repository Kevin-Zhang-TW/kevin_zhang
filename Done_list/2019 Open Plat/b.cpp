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
// What I should check
// 1. overflow
// 2. corner cases
// Enjoy the problem instead of hurrying to AC
// Good luck !
const int MAX_N = 30010, MAX_K = 6, p = 1e9 + 7;

int n, k;
int cr[MAX_N][MAX_K], cc[MAX_N][MAX_K];

using mp = pair<ll,int>;
void add(int &a, int b) { a += b - p, a += (a>>31) & p; }
void chmin_add(mp &a, ll b, int c) {
	if (chmin(a.first, b))
		a.second = c;
	else if (a.first == b)
		add(a.second, c);
}

int32_t main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	IO("escape");
	//n = 30000, k = 6;
	cin >> n >> k;
	for (int i = 0;i < n;++i)
		for (int j = 0;j+1 < k;++j)
			cin >> cr[i][j];
	for (int i = 0;i < k;++i)
		for (int j = 0;j+1 < n;++j)
			cin >> cc[j][i];

	int all = 1;
	for (int i = 0;i < k;++i) all *= k;

	const ll inf = 1ll << 59;

	vector<mp> dp(all, make_pair(inf, 0)), tmp(all);


	auto express = [&](int v) {
		vector<int> res;
		for (int i = 0;i < k;++i)
			res.pb(v % k), v /= k;
		return res;
	};
	auto compress = [&](vector<int> vec) {
		int val = 0;
		for (int i = k-1;i >= 0;--i)
			val *= k, val += vec[i];
		return val;
	};
	auto lisan = [&](vector<int> val) {
		vector<int> map(k*2, -1);
		int cnt = 0;
		for (int &i : val) {
			if (map[i] == -1) {
				i = map[i] = cnt++;
			}
			else i = map[i];
		}
		return val;
	};

	vector<int> allmask(all);
	vector<vector<int>> preexp(all);
	//        first for mask, second for to
	vector< vector< pair<int, int> > > nxt(all);

	vector< vector< int > > nxtrow(k-1, vector< int > (all, -1));
	{
		iota(AI(allmask), 0);
		for (int &i : allmask) i = compress( lisan(express(i) ) );
		sort(AI(allmask));
		allmask.resize(unique(AI(allmask)) - begin(allmask));
		for (int i : allmask) preexp[i] = express(i);//, debug(AI(preexp[i]));

		for (int comp : allmask) {
			for (int mask = 1;mask < 1<<k;++mask) {
				// if number i is open
				vector<int> open(k), lab = preexp[comp];

				for (int i = 0;i < k;++i) if (mask >> i & 1) {
					++open[ lab[i] ];
				}

				bool valid = true;
				for (int c : lab) if (!open[c]) {
					valid = false;
					break;
				}
				if (!valid) continue;

				int nid = k;
				for (int i = 0;i < k;++i) if (~mask >> i & 1) 
					lab[i] = nid++;

				nxt[comp].pb(mask, compress(lisan(lab)));
			}
		}

		for (int bk = 0;bk + 1 < k;++bk) for (int comp : allmask) {

			vector<int> lab = preexp[comp];

			if (lab[bk] == lab[bk+1]) continue;

			int x = lab[bk+1];
			for (int &i : lab) if (i == x) i = lab[bk];

			nxtrow[bk][ comp ] = compress(lisan(lab));
		}
	}

	DE(k * allmask.size());
	// initialize dp
	{
		int v = 0;
		for (int i = k - 1;i >= 0;--i)
			v *= k, v += i;
		dp[v] = make_pair(0, 1);
	}

	

	for (int row = 0;row < n;++row) {

		for (int comp : allmask) tmp[comp] = make_pair(inf, 0);

		for (int bk = 0;bk + 1 < k;++bk) for (int comp : allmask) if (nxtrow[bk][comp] != -1 && dp[comp].first < inf) 
			chmin_add(dp[ nxtrow[bk][comp] ], dp[comp].first + cr[row][bk], dp[comp].second);
					
		if (row == n-1) continue;

		vector<ll> excost(1 << k);

		for (int mask = 1;mask < 1<<k;++mask) {
			excost[mask] = cc[row][ __lg(mask) ];
			if (mask != (mask & -mask))
				excost[mask] += excost[mask ^ (1<<__lg(mask))];
		}

		for (int comp : allmask) if (dp[comp].first < inf) {

			ll cost = dp[comp].first;

			int way = dp[comp].second;

			for (auto P : nxt[comp]) {
				int mask, nxtid;
				tie(mask, nxtid) = P;

				chmin_add(tmp[nxtid], cost + excost[mask], way);
			}
		}

		swap(dp, tmp);
	}

	cout << dp[0].second << '\n';
}
