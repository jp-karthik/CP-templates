#include <bits/stdc++.h>
using namespace std;

class sparseTable {
    //Build time => O(N * log(N)), query response => O(1)
    /* Note : Functionality of the sparsetable can be altered according to our 
    interest by changing the operational connectors in the following lines */
    // Line no. : 28, 36
private:
    vector<long long> LOG;
    vector<vector<long long>> table;
public:
    //A parameterized constructor which takes input vector and builds LOG and sparse table 
    sparseTable(vector<long long>& v) {
        long long n = v.size();
        LOG.resize(n + 1);
        LOG[1] = 0;
        for (int i = 2; i <= n; i++) {
            LOG[i] = LOG[i / 2] + 1;
        }
        table.resize(LOG[n] + 1, vector<long long>(n));
        for (int i = 0; i < n; i++) {
            table[0][i] = v[i];
        }
        for (int i = 1; i <= LOG[n]; i++) { //O(N * log(N))
            for (int j = 0; j < n; j++) {
                if (j + (1<<i) - 1 < n) {
                    table[i][j] = min(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]); //in case of min query
                }
            }
        }
    }
    //getter function of for responding to the query
    long long get(long long L, long long R) { //0 indexed where L <= R 
        long long len = R - L + 1;
        return min(table[LOG[len]][L], table[LOG[len]][R - (1 << LOG[len]) + 1]); //in case of min query
    }
};

int main() {
    long long n, q;
    cin >> n;

    vector<long long> v(n);
    for (auto & x : v) cin >> x;

    sparseTable table(v); //instance of sparseTable class
    cout << table.get(0, 1); // method in this object
}