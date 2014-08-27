#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>



using namespace std;

char s[5555];
int len;


char getNext(int pos) {
	for (int i = pos; i < len; ++i) {
		if (s[i] != '=') return s[i];
	}
	return '=';
}



int main() {
	freopen("in.txt", "r", stdin);
	int n;
	while (scanf("%d", &n) != EOF) {
		scanf("%s", s);
		len = strlen(s);
		int a = 'a', z = a + n - 1;
		int now = 0;
		string ans = "";
		char tmp = getNext(0), val;
		if (tmp == '>') val = z;
		if (tmp == '<') val = a;
		if (tmp == '=') val = a;
		int ok = true;
		ans.push_back(val);
		for (int i = 0; i < len; ++i) {
			if (s[i] == '=') {

			} else if (s[i] == '<'){
				val++;
				if (val > z) ok = false;
				int tmp = getNext(i + 1);
				if (tmp == '>') val = z;
			} else if (s[i] == '>') {
				val--;
				if (val < a) ok = false;
				int tmp = getNext(i + 1);
				if (tmp == '<') val = a;
			}
			ans.push_back(val);
			if (!ok) break;
		}
		if (ok) {
			cout << ans << endl;
		} else {
			cout << -1 << endl;
		}
	}

	return 0;
}
