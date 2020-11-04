#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<iterator>

using namespace std;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	int n; cin >> n;
	vector <int> data(n);
	int temp;
	for (int i = 0; i < n; ++i) {
		cin >> temp;
		data[i] = temp;
	}
	string result; result.reserve(n + 1);
	int q; cin >> q;
	int l, r, x;
	for (int i = 0; i < q; ++i) {
		cin >> l >> r >> x;
		
	}
	return 0;
}
