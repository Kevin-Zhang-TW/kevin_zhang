#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
using ll = long long;
const int maxn = 600;
vector<int> edge[maxn];
int n, a, b;
struct line {
	int x1, x2, y1, y2;
	friend istream& operator >> (istream& in, line &a) {
		in >> a.x1 >> a.y1 >> a.x2 >> a.y2;
		if (a.x1 > a.x2) swap(a.x1, a.x2);
		if (a.y1 > a.y2) swap(a.y1, a.y2);
		return in;
	}
	friend bool intersect(const line &a, const line &b) {
		return !(a.x1 > b.x2 || a.x2 < b.x1 || a.y1 > b.y2 || a.y2 < b.y1);
	}
};
vector<line> h, v;
int ma[maxn], res, vis[maxn], T;
bool match(int now) {
	if (vis[now] == T)return false;
	vis[now] = T;

	if (now < a) {
		for (int u : edge[now]) if (ma[u] == -1) {
			ma[u] = now;
			ma[now] = u;
			++res;
			return true;
		}
		for (int u : edge[now]) if (u != ma[now] && match(u)){
			ma[now] = u;
			ma[u] = now;
		   	return true;
		}
		return false;
	}
	else return match(ma[now]);
}


signed main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	memset(ma, -1, sizeof(ma));
	cin >> n;
	for (int i = 0;i < n;++i) {
		line a;
		cin >> a;
		if (a.x1 == a.x2) h.pb(a);
		else v.pb(a);
	}
	a = h.size(), b = v.size();
	for (int i = 0;i < a;++i) for (int j = 0;j < b;++j)
		if (intersect(h[i], v[j])) edge[i].pb(j+a), edge[j+a].pb(i);//, cout << i << ' ' << a+j << '\n';
	for (int i = 0;i < a;++i)
		++T, match(i);
	cout << a + b - res << '\n';
	//for (int i = 0;i < a+b;++i) if (edge[i].empty()) ++res;
	//cout << res << '\n';
}

