#define pb emplace_back
using namespace std;
using ll = long long;
const int maxn = 40010;
int n, sz[maxn], v[maxn], res;
bool block[maxn];
vector<int> edge[maxn];
int pfmax[maxn], sum_max;
struct BS {
	int sum, peak, rcnt;
	BS& operator += (int val) {
		if (val == 1) {
			rcnt = max(0, rcnt-1);
			++peak;
		}
		else {
			++rcnt;
			peak = max(peak-1, 0);
		}
		sum += val;

		sum_max = max(sum, sum_max);

		if (!sum && !rcnt) res = max(res, peak);
		return *this;
	}
	BS (int val) {
		sum = 0, peak = 0, rcnt = 0;
		(*this) += val;
	}
	BS ():sum(0), peak(0), rcnt(0){};
	void update() {
		if (rcnt == 0) {
			assert(sum >= 0);
			pfmax[ sum ] = max( pfmax[ sum ], peak);
		}
	}
	void match() {
		if (rcnt == 0) {
			assert(sum >= 0);
			if (~pfmax[sum]) res = max({res, pfmax[sum], peak});
		}
	}
};
void get_sz(int now, int lst = -1) {
	sz[now] = 1;
	for (int u : edge[now]) if (u != lst && !block[u])
		get_sz(u, now), sz[now] += sz[u];
}
int get_cen(int now, int all, int lst = -1) {
	for (int u : edge[now]) if (u != lst && !block[u])
		if (sz[u] + sz[u] > all) return get_cen(u, all, now);
	return now;
}
void dfs_update(int now, BS val, int lst = -1) {
	val += v[now];
	val.update();
	if (block[now]) return;
	for (int u : edge[now]) if (u != lst)
		dfs_update(u, val, now);
}
void dfs_match(int now, BS val, int lst = -1) {
	val += -v[now];
	val.match();
	if (block[now]) return;
	for (int u : edge[now]) if (u != lst)
		dfs_match(u, val, now);
}
void test_cross(int c) {
	BS val(-v[c]);
	fill(pfmax+1, pfmax+sum_max+1, -1);
	sum_max = 0;
	for (int u : edge[c]) if (!block[u])
		dfs_match(u, val, c), dfs_update(u, BS(), c);

	fill(pfmax+1, pfmax+sum_max+1, -1);
	sum_max = 0;
	for (int u : edge[c]) if (!block[u])
		dfs_match(u, val, c), dfs_update(u, BS(), c);
}
void get_ans(int now = 1) {
	get_sz(now);
	int c = get_cen(now, sz[now]);
	block[c] = true;
	test_cross(c);
	reverse(edge[c].begin(), edge[c].end());
	test_cross(c);
	for (int u : edge[c]) if (!block[u])
		get_ans(u);
	block[c] = false;
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
	ios_base::sync_with_stdio(0), cin.tie(0);
	memset(pfmax, -1, sizeof(pfmax));
	pfmax[0] = 0;
	IO("btree");
	cin >> n;
	for (int i = 2, p;i <= n;++i) {
		cin >> p;
		edge[p].pb(i);
		edge[i].pb(p);
	}
	for (int i = 1;i <= n;++i) {
		char s;cin >> s;
		v[i] = (s == '(' ? 1 : -1);
	}
	get_ans();
	cout << res << '\n';
}
