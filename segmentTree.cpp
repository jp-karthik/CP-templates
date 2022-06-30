#include<bits/stdc++.h>
using namespace std;

class segmentTree {
	//Build time => O(N), query response => O(log(N))
	/* Note : Functionality of the segmentTree can be altered according to our 
	interest by changing the operational connectors in the following lines */
	// Line no. : 32, 40, 43, 57
private:
	vector<long long> ST;
public:
	//A parameterized constructor which takes input as a vector of whose segTree has to be created
	segmentTree(vector<long long>& v) {
		buildST(v);
	}
	//getter and setter functions of the segTree
	long long get(int query_low, int query_high) { //0 indexed where query_low <= query_high
		return getST(1, 0, ST.size() / 2 - 1, query_low, query_high);
	}
	void set(int pos, long long val) { //0 indexed
		updateST(1, 0, ST.size() / 2 - 1, pos, pos, val);
	}
	//bts buildST, getST, updateST functions which are used by get, set and constructors
	void buildST(vector<long long> v) {
		while (!checkPower(v.size())) {
			v.push_back(0);
		}
		ST.resize(2 * v.size());
		for (int i = 0; i < v.size(); i++) {
			ST[v.size() + i] = v[i];
		}
		for (int i = v.size() - 1; i >= 1; i--) {
			ST[i] = min(ST[2 * i], ST[2 * i + 1]); //in case of min query
		}
	}
	long long getST(int node, int node_low, int node_high, int query_low, int query_high) {
		if (node_low >= query_low && node_high <= query_high) {
			return ST[node];
		}
		if (node_high < query_low || node_low > query_high) {
			return 1e18; //in case of min query
		}
		int mid = (node_low + node_high) / 2;
		return min(getST(left(node), node_low, mid, query_low, query_high), 
			getST(right(node), mid + 1, node_high, query_low, query_high)); //in case of min query
	}
	void updateST(int node, int node_low, int node_high, int query_low, int query_high, int val) {
		if (node_low >= query_low && node_high <= query_high) {
			ST[node] = val;
			return;
		}
		if (node_high < query_low || node_low > query_high) {
			return;
		}
		int mid = (node_low + node_high) / 2;
		updateST(left(node), node_low, mid, query_low, query_high, val);
		updateST(right(node), mid + 1, node_high, query_low, query_high, val); 
		ST[node] = min(ST[left(node)], ST[right(node)]); //in case of min query
	}
	//helper functions to get the left and right child and for initialization of the segTree
	int left(int i) {
		return 2 * i;
	} 
	int right(int i) {
		return 2 * i + 1;
	}
	bool checkPower(long long size) {
		long long cnt = 0;
		while (size) {
			if (size % 2 == 1) {
				cnt++;
			}
		size /= 2;
		}
		if (cnt == 1) return true;
		return false;
	}
};


int main() {
	long long  n;
	cin >> n;
	vector<long long> v(n);
	for (auto& x : v) {
		cin >> x;
	}
	segmentTree tree(v); //instance of segment tree class

	//available methods in this object 
	cout << tree.get(0, 1); 
	tree.set(0, 0);
}