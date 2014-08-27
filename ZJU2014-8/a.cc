#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int getMin(int n) {
	if (n % 4 == 0 || n % 4 == 3) return 0;
	else return 1;
}




int main() {

	freopen("in.txt", "r", stdin);


	int n;
	while (scanf("%d", &n) != EOF) {
		if (n == 1) {
			puts("1 1");
			puts("1");
			puts("1");
			continue;
		}
		if (n == 2) {
			puts("1 1");
			puts("1 2");
			puts("2 1");
			continue;
		}
		int mi = getMin(n), mx = n - getMin(n - 1);
		vector<int> v1, v2;
		for (int i = n; i >= 1; --i) v1.push_back(i);
		for (int i = n - 1; i >= 1; --i) v2.push_back(i);
		v2.push_back(n);
		printf("%d %d\n", mi, mx);
		for (int i = 0; i < n; ++i) {
			if (i) printf(" ");
			printf("%d", v1[i]);
		}
		puts("");
		for (int i = 0; i < n; ++i) {
			if (i) printf(" ");
			printf("%d", v2[i]);
		}
		puts("");
	}


	return 0;
}
