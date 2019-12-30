#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
using ll = long long;
const int maxn = 10, inf = 100;
//     row   squar   column
//  dp[ i ] [  j  ] [  k   ]
#define base(i) vector<vector<vector<int>>> (2, vector<vector<int>> (1<<4, vector<int> (1<<10, (i))))
#define iter() for(int i : {0, 1})for(int j = 0;j < 1<<4;++j)for(int k = 0;k < 1<<10;++k)
#define iter_lim() for(int i : {0, 1})for(int j = jl;j < jr;++j)for(int k = kl;k < kr;++k)
string g[maxn];
auto dp = base(0);
int hor[maxn], ver[maxn], sq[maxn];
void out(int i, int k){
	for(int j = 0;j < k;++j)cout << !!(i&(1<<j));cout << ' ';
}
void refresh(int row){
	auto tmp = base(inf);
	int jl = 0, jr = 1<<4, kl = 0, kr = 1<<10;// [l, r)
	if(row == 0){
		for(int j = 0;j < 9;++j)kl |= ver[j] << j;
		kr = kl+1;
	}
	if(row % 3 == 0){
		for(int i = 0;i < 3;++i)for(int j = 0;j < 9;++j)if(g[i+row][j] == '1')
			jl ^= 1<<(j/3);
		jr = jl+1;	
		iter_lim()  tmp[ hor[row] ][ j ][ k ] = dp[ 0 ][ 0 ][ k ];
	}
	else iter_lim() tmp[ hor[row] ][ j ][ k ] = dp[ 0 ][ j ][ k ];
	iter() dp[i][j][k] = tmp[i][j][k];
}
#define O(i, j, k) (cout << (i) << ' ', out(j, 3), out(k, 9), cout << ' ')
int solve(){ 
	for(int r = 0;r < 9;++r){
		refresh(r);
		for(int c = 0;c < 9;++c){
			auto tmp = base(inf);
			iter() if(dp[i][j][k] != inf)tmp[ i^1 ][ j ^ (1<<(c/3)) ][ k ^ (1<<c) ] = dp[i][j][k]+1;
			iter() dp[i][j][k] = min(tmp[i][j][k], dp[i][j][k]);
		}
	}
	return dp[0][0][0];
}
signed main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	for(int i = 0;i < 9;++i)cin >> g[i];
	for(int i = 0;i < 9;++i)for(int j = 0;j < 9;++j){
		hor[i] ^= g[i][j] == '1';
		ver[j] ^= g[i][j] == '1';
	}
	cout << solve() << '\n';
}

