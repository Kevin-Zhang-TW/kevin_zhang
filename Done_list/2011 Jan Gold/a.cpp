#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
using ll = long long;
const int maxn = 24;
int n, k, res;
string w[maxn];
#define V(i) ((i) - 'A')
bool same(const string &a, const string &b) {
	if (a.size() < b.size()) return false;
	for (int i = 1;i <= b.size();++i) if (a[a.size()-i] != b[b.size()-i]) return false;
	return true;
}
struct trie {
	struct node {
		node* next[3] = {}, * f = NULL;
		bool goback[3] = {};
		int cnt = 0, dp = -1, tmp = -1;
		void chmax(int val) { tmp = max(tmp, val+cnt); }
		void update() {
			if (dp == -1) return;
			for (int i = 0;i < 3;++i) if (next[i]) 
				next[i]->chmax(dp);
		}
		void pull() {
			res = max(res, tmp);
			dp = tmp;
			tmp = -1;
		}
	};
	node* root = new node;
	void insert(const string &w) {
		node* now = root;
		for (int i = 0;i < w.size();++i) {
			if (!now->next[V(w[i])]) now->next[V(w[i])] = new node;
			now = now->next[V(w[i])];
		}
	}
	void dfs(node* now) {
		static string cur;
		for (int i = 0;i < n;++i) if (same(cur, w[i]))
			++now->cnt;
		for (int i = 'A';i <= 'C';++i) if (now->next[V(i)]) {
			cur.push_back(i);
			dfs(now->next[V(i)]);
			cur.pop_back();
		}
	}
	void dfs2(node* now) {
		now->update();
		for (int i = 0;i < 3;++i) if (now->next[i] && !now->goback[i])
			dfs2(now->next[i]);
	}
	void dfs3(node* now) {
		now->pull();
		for (int i = 0;i < 3;++i) if (now->next[i] && !now->goback[i])
			dfs3(now->next[i]);
	}
	void update() {
		dfs2(root);
		dfs3(root);
	}
	void build() {
		dfs(root);
		queue<node*> togo;
		root->f = root;
		for (int i = 0;i < 3;++i) if (root->next[i]) togo.push(root->next[i]), root->next[i]->f = root;
		while (!togo.empty()) {
			node* now = togo.front();
			togo.pop();
			for (int i = 0;i < 3;++i) if (now->next[i]) {
				node* nf = now->f, * nx = now->next[i];
				while (nf != root && !nf->next[i]) nf = nf->f;
				nx->f = nf->next[i];
				togo.push(nx);
			}
			else {
				node* nf = now->f;
				while (nf != root && !nf->next[i]) nf = nf->f;
				now->next[i] = nf->next[i];
				now->goback[i] = true;
			}
		}
		root->dp = 0;
	}
}tree;
signed main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> n >> k;
	for (int i = 0;i < n;++i)
		cin >> w[i];
	for (int i = 0;i < n;++i)
		tree.insert(w[i]);
	tree.insert("A");
	tree.insert("B");
	tree.insert("C");
	tree.build();
	for (int i = 0;i < k;++i) tree.update();
	cout << res << '\n';
}
