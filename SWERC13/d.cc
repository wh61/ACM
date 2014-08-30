#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>

using namespace std;


typedef unsigned long long LL;

const int maxn = 1111;
const LL MOD = 777;

LL hs[maxn];
LL mod[maxn];


inline LL getHash(int l, int r) {
	return hs[r + 1] - hs[l] * mod[r - l + 1];
}

bool sub(const string& sub, const string& s) {
	if (sub.size() > s.size()) return false;
	hs[0] = 0;
	for (int i = 0; i < s.size(); ++i) {
		hs[i + 1] = hs[i] * MOD + s[i];
	}
	LL subVal = 0;
	for (int i = 0; i < sub.size(); ++i)
		subVal = subVal * MOD + sub[i];
	int ssz = s.size(), subsz = sub.size();
	for (int pos = 0; pos < ssz - subsz + 1; ++pos) {
		LL val = getHash(pos, pos + subsz - 1);
		if (subVal == val) return true;
	}
	return false;
}

void buildTree(int n, int val, string &s) {
	if (n > 1) {
		buildTree(n - 1, 0, s);
	}
	s.push_back('0' + val);
	if (n > 1) {
		buildTree(n - 1, 1, s);
	}
}


int main() {

	freopen("in.txt", "r", stdin);


	mod[0] = 1;
	for (int i = 1; i < maxn; ++i) mod[i] = mod[i - 1] * MOD;
	int T, ca = 0;
	cin >> T;
	while (T--) {
		printf("Case %d: ", ++ca);
		int n;
		string s_;
		cin >> n >> s_;
		int sz = s_.length();
		string seq = "";
		for(int i = 0; i < sz; ++i) {
			if (s_[i] == 'L') seq.push_back('0'); else seq.push_back('1');
		}
		string s = "";
		//cout << s_ << endl;
		//cout << seq << endl;

		if (n > 9) {
			buildTree(8, 0, s);
			string s1 = s + "0" + s;
			string s2 = s + "1" + s;
			if (sub(seq, s1) || sub(seq, s2)) puts("Yes"); else puts("No");
		} else {
			buildTree(n, 0, s);

			if (sub(seq, s)) puts("Yes"); else puts("No");
		}

	}
}
