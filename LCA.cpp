#include<bits/stdc++.h>
using namespace std;

class binaryLifting {
public:
	vector<vector<int>> up;
	vector<int> depth;
	int LOG;
	int N;
public:
	binaryLifting(vector<vector<int>>& g) {
		N = g.size() - 1;
		int size = N;
		LOG = 0;
		while (size) {
			LOG++;
			size /= 2;
		}
		depth.resize(N + 1);
		up.resize(N + 1, vector<int>(LOG + 1));
		dfs(1, 1, g);
	}
	void dfs(int u, int p, vector<vector<int>>& g) {
		up[u][0] = p;
		for (int i = 1; i <= LOG; i++) {
			up[u][i] = up[up[u][i - 1]][i - 1];
		}
		for (auto v : g[u]) {
			if (v != p) {
				depth[v] = depth[u] + 1;
				dfs(v, u, g);
			}
		}
	}
	int get(int node, int k) {
		if (k > depth[node]) {
			return -1;
		}
		for (int i = LOG; i >= 0; i--) {
			if (k & (1 << i)) {
				node = up[node][i];
				k -= (1 << i);
			}
		}
		return node;
	}
	int LCA(int a, int b) {
		if (depth[a] < depth[b]) {
			swap(a, b);
		}
		int k = depth[a] - depth[b];
		a = get(a, k);
		if (a == b) {
			return a;
		}
		for (int i = LOG; i >= 0; i--) {
			if (up[a][i] != up[b][i]) {
				a = up[a][i];
				b = up[b][i];
			}
		}
		return up[a][0];
	}
};

vector<vector<int>> g;

int main() {
	int n;
	cin >> n;

	g.resize(n + 1);

	for (int i = 0; i < n - 1; i++) {
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
    
	binaryLifting tree(g);
	cout << tree.LCA(2, 3);
}
