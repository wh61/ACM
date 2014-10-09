#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;


string getbit(int val, const string& I, const string& V, const string& X) {
	if (val == 0) return "";
	if (val == 1) return I;
	if (val == 2) return I + I;
	if (val == 3) return I + I + I;
	if (val == 4) return I + V;
	if (val == 5) return V;
	if (val == 6) return V + I;
	if (val == 7) return V + I + I;
	if (val == 8) return V + I + I + I;
	if (val == 9) return I + X;
}


string int2Roman(int val) {
	int val4 = val / 1000;
	int val3 = val % 1000 / 100;
	int val2 = val % 100 / 10;
	int val1 = val % 10;
	string str;
	str += getbit(val4, "M", "", "");
	str += getbit(val3, "C", "D", "M");
	str += getbit(val2, "X", "L", "C");
	str += getbit(val1, "I", "V", "X");
	return str;
}



int main() {
	freopen("roman.in", "r", stdin);
	freopen("roman.out", "w", stdout);
	//freopen("in.txt", "r", stdin);

	int A, B;
	char ch1, ch2, chch;
	scanf("%d%c%c-%d%c%c", &A, &ch1, &chch, &B, &ch2, &chch);
	if (ch1 == 'B') {
		A = 754 - A;
	} else {
		A += 753;
	}
	if (ch2 == 'B') {
		B = 754 - B;
	} else {
		B += 753;
	}
	int sz = 0;
	int ans = 0;
	for (int i = A; i <= B; ++i) {
		int val = i;
		if (val < 0) val = -val;
		string s = int2Roman(val);
		int sz = s.size();
		ans = max(ans, sz);
	}
	printf("%d\n", ans);
	return 0;
}
