#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
using ll = long long;
const int maxm = 1000010, maxn = 40001, maxk = 16, p = 1e9+7;
vector<pair<int,int>> alle[maxm];
int n, m;
namespace mst{
	int sz[maxn], g[maxn];
	ll res, cnt = 1;
	int find(int i){return i == g[i] ? i : g[i] = find(g[i]);}
	bool merge(int a, int b){
		if((a = find(a)) == (b = find(b)))return false;
		if(sz[a] < sz[b])swap(a, b);
		sz[a] += sz[b];
		g[b] = g[a];
		return true;
	}
	void init(){for(int i = 1;i <= n;++i)sz[i] = 1, g[i] = i; }
};
void build_mst(){
	mst::init();
	map<int,int> g;
	function<int(int)> find = [&](int a){
		if(g.count(a))return find(g[a]);
		return a;
	};
	auto merge = [&](int a, int b){
		a = find(mst::find(a)), b = find(mst::find(b));
		if(a == b)return false;
		g[b] = a;
		return true;
	};
	for(int i = 0;i < maxm;++i){
		if(alle[i].empty())continue;
		int cnt = 0;
		vector<int> tcnt(4);
		auto cb = [](int a){
			int res = 0;
			while(a)res += a&1, a>>=1;
			return res;
		};
		for(int s = 1;s < (1<<alle[i].size());++s){
			bool ok = true;
			for(int j = 0;j < alle[i].size();++j)if(s&(1<<j))if(!merge(alle[i][j].first, alle[i][j].second))ok = false;
			g.clear();
			tcnt[cb(s)] += ok;
		}
		int ue = 0;
		for(int j = 0;j < alle[i].size();++j){
			auto [a, b] = alle[i][j];
			if(mst::merge(a, b)) mst::res += i, ++ue;
		}
		cnt = tcnt[ue];
		mst::cnt = mst::cnt * max(1, cnt) % p;
	}
}
signed main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for(int a, b, w, i = 0;i < m;++i){
		cin >> a >> b >> w;
		if(a != b) alle[w].pb(a, b);
	}
	build_mst();
	cout << mst::res << ' ' << mst::cnt << '\n';
}

