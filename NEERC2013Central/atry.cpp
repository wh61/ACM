#include <iostream>
#include <cstdio>
using namespace std;

void work(char A, char B, char C, int n) {
	if (n > 0) {
		work(A, C, B, n - 1);
		printf("%c %c")
	}
}


int main() {
	return 0;
}
