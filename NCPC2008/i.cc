#include <iostream>
#include <cstring>
#include <cstdio>
#include <set>


using namespace std;

const size_t maxn = 111111;

int nx[maxn];
int a[maxn];
int c_nx[maxn];



int main() {

	freopen("in.txt", "r", stdin);

	int c, n, A;
	while (scanf("%d%d%d", &c, &n, &A) != EOF) {
		for (int i = 0; i < A; ++i) {
			scanf("%d", a + i);
		}
		for (int i = 0; i < n; ++i) {
			c_nx[i] = A + i;
		}
		for (int i = A - 1; i >= 0; --i) {
			nx[i] = c_nx[a[i]];
			c_nx[a[i]] = i;
		}
		set<int> hs;
		int ans = 0;
		for (int i = 0; i < A; ++i) {
			if (hs.find(i) != hs.end()) {
				hs.erase(i);
				hs.insert(nx[i]);
			} else if (hs.size() < c) {
				hs.insert(nx[i]);
				ans++;
			} else {
				set<int>::reverse_iterator it = hs.rbegin();
				int tmp = *it;
				hs.erase(tmp);
				hs.insert(nx[i]);
				ans++;
			}
		}

		printf("%d\n", ans);
	}

	return 0;
}
