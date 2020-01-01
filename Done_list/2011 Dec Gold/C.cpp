#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
using ll = long long;
const int maxn = 1 << 17, maxk = 17;

struct sgt{
	int v[maxn<<1], tag[maxn<<1];
	void add_node(int i, int val, int sz){
		v[i] += val * sz;
		tag[i] += val;
	}
	void push(int i, int sz){
		if(i < maxn && tag[i]){
			add_node(i<<1, tag[i], sz>>1);
			add_node(i<<1|1, tag[i], sz>>1);
			tag[i] = 0;
		}
	}
	void update(int i, int sz){
		if(i < maxn){
			push(i, sz);
			v[i] = v[i<<1] + v[i<<1|1];
		}
	}
	void add(int l, int r, int val){
		l += maxn, r += maxn;
		pa(l), pa(r);
		int sz = 1, sl = l>>1, sr = r>>1;
		for(;l < r;(++l)>>=1, (--r)>>=1, sz <<= 1){
			if( l&1)add_node(l, val, sz);
			if(~r&1)add_node(r, val, sz);
		}
		if(l == r)add_node(l, val, sz);
		for(sz = 2;sl;sl >>= 1, sr >>= 1, sz <<= 1)
			update(sl, sz), update(sr, sz);
	}
	void pa(int pos){
		int sz = maxn;
		for(int i = maxk;i > 0;--i, sz >>= 1)push(pos >> i, sz);
	}
	int query(int l, int r){
		l += maxn, r += maxn;
		pa(l), pa(r);
		int res = 0;
		for(;l < r;(++l)>>=1, (--r)>>=1){
			if( l&1)res += v[l];
			if(~r&1)res += v[r];
		}
		if(l == r)res += v[l];
		return res;
	}
}tree;
int n, m, in[maxn], out[maxn];
int lid[maxn], top[maxn], pa[maxn];
vector<int> edge[maxn];
void dfs1(int now = 1, int last = 0){
	static int sz[maxn];
	sz[now] = 1;
	int end = 0;
	for(int i = 0;i < edge[now].size();++i)if(edge[now][i] != last){
		dfs1(edge[now][i], now);
		sz[now] += sz[edge[now][i]];
		edge[now][end++] = edge[now][i];
	}
	edge[now].resize(end);
	for(int i = 1;i < edge[now].size();++i)if(sz[ edge[now][i] ] > sz[ edge[now][0] ])
		swap(edge[now][i], edge[now][0]);
}
void dfs2(int now = 1, bool is_top = true){
	static int t, lcnt;
	in[now] = ++t;
	if(is_top)top[ lid[now] = ++lcnt ] = now;
	else lid[now] = lid[ pa[now] ];
	for(int u : edge[now]){
		pa[u] = now;
		dfs2(u, u != edge[now].front());
	}
	out[now] = t;
}
inline bool isanc(int a, int b){ return in[a] <= in[b] && out[a] >= out[b]; }
void add(int a, int b){
	int oa = a, ob = b;
	auto jump_add = [&](int &now, int other){
		for(;!isanc(top[ lid[now] ], other);now = pa[ top[lid[now]] ])
			tree.add(in[ top[lid[now] ] ], in[ now ], 1);
	};
	jump_add(a, b);
	jump_add(b, a);
	if(in[a] > in[b])swap(a, b);
	if(b == a)return;
	tree.add(in[a]+1, in[b], 1);
}
int query(int a, int b){
	int res = 0;
	auto jump_query = [&](int &now, int other){
		for(;!isanc(top[ lid[now] ], other);now = pa[ top[lid[now]] ])
			res += tree.query(in[ top[lid[now] ] ], in[ now ]);
	};
	jump_query(a, b);
	jump_query(b, a);
	if(a == b)return res;
	if(in[a] > in[b])swap(a, b);
	return res + tree.query(in[a]+1, in[b]);
}

signed main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for(int i = 1, a, b;i < n;++i){
		cin >> a >> b;
		edge[a].pb(b);
		edge[b].pb(a);
	}
	dfs1();
	dfs2();
	for(int a, b, i = 0;i < m;++i){
		char cmd;
		cin >> cmd >> a >> b;
		if(cmd == 'Q')cout << query(a, b) << '\n';
		else add(a, b);
	}
}

