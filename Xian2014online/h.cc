#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>


using namespace std;

const int maxn = 111111;

bool Bused[maxn];
int a[maxn];
int f[maxn];

typedef long long LL;



int main() {

	freopen("in.txt", "r", stdin);

	int n;
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i <= n; ++i) Bused[i] = false;
		LL val = 0;
		for (int num = n; num >= 0; --num) {
			if (Bused[num]) continue;
			int maxbit = -1;
			for (int i = 0; i < 20; ++i) if ((num >> i) & 1) maxbit = i;
			int tmp = 0;
			for (int i = 0; i <= maxbit; ++i) {
				if (((num >> i) & 1 )== 0)
					tmp |= 1 << i;
			}
			f[tmp] = num;
			f[num] = tmp;
			val += num ^ tmp;
			val += num ^ tmp;
			Bused[num] = Bused[tmp] = true;
		}


		cout << val << endl;
		for (int i = 0; i <= n; ++i) {
			int num;
			scanf("%d", &num);
			if (i) printf(" ");
			printf("%d", f[num]);
		}
		puts("");

	}


	return 0;

}
