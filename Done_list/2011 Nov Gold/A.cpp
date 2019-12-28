#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
using ll = long long;
const int maxn = 100010;
int cnt[maxn], h[maxn], n, lisan[maxn], _len = 1, k;
ll res;
#define LIS(i) (lisan[_len++] = i)
#define POS(i) (lower_bound(lisan, lisan+_len, (i)) - lisan + 1)
#define lowbit(i) ((i) & -(i))
#define readchar getchar_unlocked
int val[maxn];
void add(int i){ for(;i < maxn;i += lowbit(i))++val[i]; }
int query(int i){ int res = 0; for(;i;i ^= lowbit(i))res += val[i]; return res; }

signed main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> n >> k;
	for(int i = 1;i <= n;++i)cin >> h[i], cnt[i] = (h[i] < k) + cnt[i-1];
	for(int i = 1;i <= n;++i)LIS(i - cnt[i] * 2);
	sort(lisan, lisan+_len);
	add(POS(0));
	for(int i = 1;i <= n;++i){
		res += query(POS(i - cnt[i] * 2));
		add(POS(i - cnt[i] * 2));
	}
	cout << res << '\n';
}

