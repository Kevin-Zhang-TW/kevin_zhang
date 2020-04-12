#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
using ll = long long;
const int maxn = 100;
int a[maxn], n, m, lim;
bool vis[maxn];
#define end(i) (cout << i << '\n', exit(0))
int tmp;
signed main(int argc, char* argv[]){
	assert(argc >= 3);
	ifstream input(argv[1]), output(argv[2]), sub(argv[3]);
	input >> n >> lim;
	cerr << "there are " << n << " cows\n";
	for (int i = 1;i <= n;++i)
		input >> a[i];

	output >> m;
	{
		sub >> tmp;
		cerr << "User took " << tmp << " rides\nAt least " << m << " is required\n";
		if (tmp != m) 
			end(0);
	}


	while (m--) {
		int len;
		sub >> len;
		if (len <= 0) end(0);
		ll sum = 0;
		vector<int> ids;
		while (len--) {
			int id;
			sub >> id;
			ids.pb(id);
			sum += a[id];
			if (vis[id]) end(0);
			vis[id] = true;
		}
		if (sum > lim) {
			cerr << "over weighted!\nCow : ";
			for (int u : ids)
				cerr << u << ' ';
			cerr << '\n';

			end(0);
		}
	}
	for (int i = 1;i <= n;++i) if (!vis[i]) {
		cerr << "the " << i << " th cow is still up there\n", end(0);
	}
	cout << 1 << '\n';
	cerr << "AC\n";

}
