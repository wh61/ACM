#include <iostream>
#include <cstdio>

using namespace std;

const long double eps = 1e-7;

int main() {

	freopen("in.txt", "r", stdin);


	int T;
	scanf("%d", &T);
	while (T--) {
		int v1_, v2_, R_, D_;
		scanf("%d%d%d%d", &v1_, &v2_, &R_, &D_);
		long double v1 = v1_, v2 = v2_, R = R_, D = D_;
		long double t = D / v2;
		long double d1 = v1 * t;
		long double d2 = D;
		if (d1 * d1 + 4 * R * R / 4 > d2 * d2 + eps) {
			puts("Why give up treatment");
		} else puts("Wake up to code");

	}
	return 0;
}
