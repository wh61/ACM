#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

int gcd_(int a, int b) { return b ? gcd_(b, a % b) : a;}

int main() {
	freopen("in.txt", "r", stdin);
	int ab, ac, bd;
	while (scanf("%d%d%d", &ab, &ac, &bd) != EOF) {
		int up = ab * ac;
		int down = bd - ac;
		int gcd = gcd_(up, down);
		printf("%d/%d\n", up / gcd, down / gcd);
	}
	return 0;
}
