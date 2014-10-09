#include <iostream>
#include <cstdio>


using namespace std;

int main() {
	int T;
	cin >> T;
	while (T--) {
		int n;
        cin >> n;
		int tmp = 0;
		for (int i = 0; i < n; ++i) {
			tmp = tmp * 2 + 1;
		}
		cout << tmp << endl;
	}
	return 0;
}
