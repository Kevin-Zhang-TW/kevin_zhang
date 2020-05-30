#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
using ll = long long;
const int maxn = 50010;
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
int n, m;
char w[10][maxn];
ll res;
int pf[10][maxn], bo[maxn];
#define V(i) ((i) == '(' ? 1 : -1)
void build(int t) {
	auto pf = ::pf[t];
	for (int i = 1;i <= m;++i)
		pf[i] = pf[i-1] + V(w[t][i]);
	deque<int> dq;
	for (int i = m;i >= 1;--i) {
		while (dq.size() && pf[dq.back()] >= pf[i]) dq.pop_back();
		dq.push_back(i);
		while (dq.size() && pf[dq.back()] >= pf[i-1]) dq.pop_back();

		if (dq.size()) 
			bo[i] = min(bo[i], dq.back()-1);//, tmp[i] = bo[i];
	}
}
struct trie {
	map<int, trie*> nxt;
	void insert(int t) {
		trie* now = this;
		for (int i = 0;i < n;++i) {
			auto it = now->nxt.find(pf[i][t]);
			if (it == end(now->nxt))
				now->nxt[ pf[i][t] ] = new trie;
			now = now->nxt[ pf[i][t] ];
		}
		++now->cnt;
	}
	int query(int t) {
		trie* now = this;
		for (int i = 0;i < n;++i) {
			auto it = now->nxt.find(pf[i][t]);
			if (it == end(now->nxt)) return 0;
			now = it->second;
		}
		return now->cnt;
	}
	int cnt = 0;
};
vector<int> pos[maxn], neg[maxn];
void solve() {
	fill (bo+1, bo+m+1, m);
	for (int i = 0;i < n;++i) 
		build(i);
	trie* now = new trie;

	for (int i = 1;i <= m;++i) 
		if (bo[i] > i) {
			pos[bo[i]].pb(i-1);
			neg[i].pb(i-1);
		}
	for (int i = 1;i <= m;++i) {
		now->insert(i);
		for (int u : pos[i]) res += now->query(u);
		for (int u : neg[i]) res -= now->query(u);
	}
}

signed main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	IO("cbs");
	cin >> n >> m;
	for (int i = 0;i < n;++i)
		cin >> w[i]+1;
	solve();
	cout << res << '\n';
}
