#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;


int main() {

	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	int n, K;
	unsigned int x_1, x0, A, B, C;
	while (cin >> n >> K >> x_1 >> x0 >> A >> B >> C) {
		unsigned int val, val1 = x_1, val2 = x0, num, mask = (1 << 31) - 1;
		priority_queue<unsigned int, vector<unsigned int>, greater<unsigned int> > q;
		for (int i = 1; i <= n; ++i) {
			val = val1 * A + val2 * B + C;
			val = val & mask;
			if (q.size() < K) {
				q.push(val);
			} else {
				if (val > q.top()) { q.pop(); q.push(val);}
			}
			val1 = val2;
			val2 = val;
		}
		vector<int> v;
		while (!q.empty()) {
			v.push_back(q.top());
			q.pop();
		}
		reverse(v.begin(), v.end());
		for (int i = 0; i < v.size(); ++i) {
			if (i) printf(" ");
			printf("%d", v[i]);
		}
		puts("");
	}
	return 0;
}
