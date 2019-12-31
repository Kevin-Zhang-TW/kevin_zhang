#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
using ll = long long;
const int maxn = 20010;
int a[maxn], lisan[maxn], n;
int tmp[maxn];
#define GET_POS(i) (lower_bound(lisan, lisan+n, (i)) - lisan)
int pos[5][maxn];
signed main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for(int i = 0;i < n;++i)cin >> lisan[i], tmp[i] = lisan[i];
	sort(lisan, lisan+n);
	for(int i = 0;i < n;++i)pos[0][ GET_POS(tmp[i]) ] = i;
	for(int j = 1;j < 5;++j){
		for(int i = 0;i < n;++i)cin >> tmp[i];
		for(int i = 0;i < n;++i)pos[j][ GET_POS(tmp[i]) ] = i;
	}
	for(int i = 0;i < n;++i)a[i] = i;
	sort(a, a+n, [&](int a, int b){
			int cnt = 0;
			for(int i = 0;i < 5;++i)cnt += pos[i][a] < pos[i][b];
			return cnt > 2;
			});
	for(int i = 0;i < n;++i)cout << lisan[a[i]] << '\n';
}

