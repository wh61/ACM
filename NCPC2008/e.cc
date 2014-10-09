#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

int p[22];

const int inf = 100000000;
int main() {
	freopen("in.txt", "r", stdin);
	int n, B, H, W;
	while (cin >> n >> B >> H >> W) {
		int minCost = inf;
		for (int i = 0; i < H; ++i) {
			int p;
			cin >> p;
			for (int j = 0; j < W; ++j) {
				int c;
				cin >> c;
				if (c >= n) {
					minCost = min(minCost, p * n);
				}
			}
		}
		if (minCost > B) {
			puts("stay home");
		} else {
			printf("%d\n", minCost);
		}
	}
	return 0;
}
