#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
using ll = long long;
#ifdef KEV
#define DE(i, e) cerr << #i << ' ' << i << e
void debug(auto L, auto R) { while (L < R) cerr << *L << " \n"[L+1==R], ++L; }
#else
#define DE(...) 0
void debug(...) {}
#endif
const int maxn = 200010, maxm = 1000010;
const ll inf = 1ll<<55;
ll dp[maxn];
int cu[maxn], cd[maxn], T;
struct bit {
	int val[maxm];
	void reset() {
		fill(val, val+maxm, 0);
	}
	bool rev = false;
	void REV(){ rev ^= true; }
	void modify(int i, int v) {
		++i;
		if (rev) i = maxm - i;
		for (;i < maxm;i += i&-i) 
			val[i] = max(val[i], v);
	}
	int query(int i) {
		++i;
		if (rev) i = maxm - i;
		int res = 0;
		for (;i;i ^= i&-i)
			res = max(res, val[i]);
		return res;
	}
}tree;
int n;
pair<int,int> loc[maxn];
vector<int> dep[maxn];
ll area(int a, int b) {
	return (ll)(loc[a].first-loc[b].first) * (loc[a].second-loc[b].second);
}
bool valid(int s, int t) {
	return loc[s].first < loc[t].first && loc[s].second < loc[t].second;
}
ll cal(int s, int t) {
	return valid(s, t) ? dp[s] + area(s, t) : inf;
}
void transition(const vector<int>&to, const vector<int>&from) {
	vector<vector<int>> L(to.size()), R(to.size());
	vector<int> ed(from.size());
	auto getdp = [&](const vector<int> &id, const vector<int> &fr) {
		deque< int > dq, ti;
		for (int i = 0, h = 0;i < id.size();++i) {
			// when x defeat y
			auto find = [&](int x, int y) {
				int l = i, r = id.size(), m;
				while (l < r) {
					m = l + r >> 1;
					if (cal(x, id[m]) <= cal(y, id[m]))
						r = m;
					else l = m+1;
				}
				return l;
			};
			auto putin = [&](int x) {
				while (dq.size() > 1 &&
						(ti.back()=find(dq.back(),x)) >= ti[ ti.size()-2 ])
					ti.pop_back(), dq.pop_back();
				if (ti.size())
					ti.back() = find(dq.back(), x);
				dq.push_back(x), ti.push_back(-1);
			};

			while (h < fr.size() && 
					valid(fr[h], id[i]))
				putin(fr[h++]);

			while (ti.size() > 1 &&
					ti[ ti.size()-2 ] <= i)
				ti.pop_back(), dq.pop_back();

			if (dq.empty()) continue;

			dp[ id[i] ] = min(dp[ id[i] ], cal(dq.back(), id[i]));
		}
	};
	for (int i = 0, h = 0, e = -1;i < to.size();++i) {
		while (e+1 < from.size() &&
			valid(from[e+1], to[i]))
			L[i].pb(++e);
		while (h < from.size() &&
			(i+1 == to.size() || !valid(from[h], to[i+1])))
			R[i].pb(h), ed[h] = i, ++h;
	}
	DE(to.size(), '\n');
	auto solve = [&](int l, int r) {
		DE(l, ' '), DE(r, '\n');
		vector<int> fl, fr, id(to.begin()+l, to.begin()+r+1);
		for (int i = l;i <= r;++i)
			fl.insert(fl.end(), L[i].begin(), L[i].end());
		for (int i = r;i >= l;--i)
			fr.insert(fr.end(), R[i].rbegin(), R[i].rend());
		for (int &i : fl) i = from[i];
		for (int &i : fr) i = from[i];

		getdp(id, fl);
		reverse(id.begin(), id.end());
		getdp(id, fr);
	};
	for (int i = 0;i < to.size();++i) {
		int j = i;
		while (j < to.size() && L[j].empty())
			++j;
		int lft = i, rt = j == to.size() ? to.size()-1 : ed[ L[j][0] ];
		solve(lft, rt);
		i = rt;
	}
}
void ss(vector<int> id) {
	for (int u : id) 
		dep[ cu[u] ].pb(u);
	int s = *max_element(cu, cu+n+1);
	debug(cu, cu+n+1);
	fill(dp+1, dp+n+1, inf);
	for (int i = 2;i <= s;++i) {
		transition(dep[i], dep[i-1]);
	}
	debug(dp, dp+n+1);
	cout << dp[n] << '\n';
}
void solve() {
	tree.reset();
	for (int i = 0, x, y;i <= n;++i) {
		tie(x, y) = loc[i];
		DE(x, ' '), DE(y, '\n');
		cu[i] = tree.query(y) + 1;
		tree.modify(y, cu[i]);
	}
	tree.reset();
	tree.REV();
	for (int i = n, x, y;i >= 0;--i) {
		tie(x, y) = loc[i];
		cd[i] = tree.query(y) + 1;
		tree.modify(y, cd[i]);
	}
	int S = *max_element(cu, cu+n+1);
	vector<int> uf;
	for (int i = 0;i <= n;++i) {
		if (cu[i] + cd[i] == S+1) 
			uf.pb(i);
	}
	ss(uf);
}
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
	IO("mowing");
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> n >> T;
	for (int i = 1;i <= n;++i)
		cin >> loc[i].first >> loc[i].second;
	++n;
	loc[n] = {T, T};

	sort(loc, loc+n);
	solve();
}
