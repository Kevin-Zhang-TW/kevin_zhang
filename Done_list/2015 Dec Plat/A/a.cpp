#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
using ll = long long;
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
#ifdef KEV
#define DE(i, e) cerr << #i << ' ' << i << e
void debug(auto L, auto R) { while (L < R) cerr << *L << " \n"[L+1==R], ++L; }
#else
#define DE(...) 0
void debug(...) {}
#endif
const int maxn = 300010, maxk = 17;
int n, q, anc[maxk][maxn], dep[maxn], in[maxn], out[maxn], suf[maxn];
vector<int> edge[maxn];
inline bool isanc(int a, int b) { return in[a] <= in[b] && out[a] >= out[b]; }
void dfs1(int now, int lst = 1) {
	static int d, t;
	dep[now] = ++d;
	in[now] = ++t;
	anc[0][now] = lst;
	for (int u : edge[now]) if (u != lst)
		dfs1(u, now);
	--d;
	out[now] = t;
}
#define P(i) ((i)==1?0:anc[0][i])
int lca(int a, int b) {
	if (dep[a] > dep[b]) swap(a, b);
	if (isanc(a, b)) return a;
	for (int i = maxk-1;i >= 0;--i)
		if (!isanc(anc[i][b], a))
			b = anc[i][b];
	return anc[0][b];
}
void dfs2(int now, int lst = 1) {
	for (int u : edge[now]) if (u != lst)
		dfs2(u, now), suf[now] += suf[u];
}
signed main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	IO("maxflow");
	cin >> n >> q;
	for (int i = 1, a, b;i < n;++i) {
		cin >> a >> b;
		edge[a].pb(b);
		edge[b].pb(a);
	}
	dfs1(1);
	for (int d = 1;d < maxk;++d)
		for (int i = 1;i <= n;++i)
			anc[d][i] = anc[d-1][ anc[d-1][i] ];
	for (int a, b;q--;) {
		cin >> a >> b;
		int lc = lca(a, b);
		++suf[a], ++suf[b], --suf[lc], --suf[P(lc)];
	}
	dfs2(1);
	cout << *max_element(suf+1, suf+1+n) << '\n';

}

