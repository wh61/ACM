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
		unsigned int L = 0,  R = (1 << 31) - 1;
		while (L < R) {
			unsigned int mid = L + (R - L) / 2;
			int cnt = 0;
			val1 = x_1;
			val2 = x0;
			for (int i = 1; i <= n; ++i) {
				val = (val1 * A + val2 * B + C) & mask;
				val1 = val2;
				val2 = val;
				if (val >= mid + 1) ++cnt;
			}
			if (cnt >= K) {
				L = mid + 1;
			} else {
				R = mid;
			}
		}
		vector<unsigned int> vec;
		val1 = x_1, val2 = x0;
		int tot = 0;
		for (int i = 1; i <= n; ++i) {
			val = (val1 * A + val2 * B + C) & mask;
			val1 = val2;
			val2 = val;
			if (val > L) {
				vec.push_back(val);
				tot++;
			}
		}
		for (int i = tot; i < K; ++i) {
			vec.push_back(L);
		}
		sort(vec.begin(), vec.end());
		reverse(vec.begin(), vec.end());

		for (int i = 0; i < K; ++i) {
			if (i) printf(" ");
			printf("%u", vec[i]);
		}
		puts("");



	}
	return 0;
}
