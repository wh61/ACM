#include <iostream>
#include <cstdio>

using namespace std;

typedef long long LL;

const int maxn = 111111;
LL p[maxn];





int main() {
	int n, dd, aa, bb;
	while (scanf("%d%d%d%d", &n, &dd, &aa, &bb) != EOF) {
		LL d = dd, a = aa, b = bb;
		for (int i = 0; i < n; ++i) {
			int tmp;
			scanf("%d", &tmp);
			p[i] = tmp;
		}

		int inc = 0, dec = 0;
		LL s = 0;
		for (int i = 1; i < n; ++i) {
			if (p[i] > p[i - 1]) {
				inc++;
				dec = 0;
				LL x = inc * a;
				LL buy = min(x, d / p[i]);
				d -= buy * p[i];
				s += buy;
			} else if (p[i] < p[i - 1]) {
				dec++;
				inc = 0;
				LL y = dec * b;
				LL sell = min(y, s);
				s -= sell;
				d += sell * p[i];
			}
		}
		cout << d << ' ' << s << endl;
	}
	return 0;
}
