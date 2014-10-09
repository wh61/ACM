#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <set>

using namespace std;

char s_[300];


string washStr(char *s, int len) {
	string str;
	int i = 0;
	while (i < len && s[i] == ' ') {
		++i;
	}
	int j = len - 1;
	while (j >= i && s[j] == ' ') {
		--j;
	}
	for (; i <= j; ++i) {
		if (s[i] != ' ') {
			str.push_back(s[i]);
		} else {
			if (s[i - 1] != ' ') {
				str.push_back(s[i]);
			}
		}
	}
	return str;
}



typedef unsigned long long LL;
const LL PP = 1007;
const LL P = 1000007;
LL p[11111];


inline LL toHash(const string& s) {
	int sz = s.size();
	LL val = 0;
	for (int i = 0; i < sz; ++i) {
		val = val * PP + s[i];
	}
	return val;
}

void canMatch(const vector<vector<LL> > &vec, const vector<LL> &seq, int len, vector<int> &ans_seq) {
	int sz = seq.size();
	set<LL> hs;
	LL tmp = 0;
	for (int i = 0; i < len; ++i) {
		tmp = tmp * P + seq[i];
	}
	LL val = 0;
	for (int i = 0; i < sz - len + 1; ++i) {
		LL temp = tmp - val * p[len];
		hs.insert(temp);
		val = val * P + seq[i];
		if (i + len < sz) {
			tmp = tmp * P + seq[i + len];
		}
	}


	for (int k = 0; k < vec.size(); ++k) {
		bool finded = false;
		const vector<LL> &v = vec[k];
		if (v.size() < len) continue;
		int sz = v.size();
		LL tmp = 0;
		for (int i = 0; i < len; ++i) {
			tmp = tmp * P + v[i];
		}
		LL val = 0;
		for (int i = 0; i < sz - len + 1; ++i) {
			LL temp = tmp - val * p[len];
			if (hs.find(temp) != hs.end()) {
				finded = true;
			}
			val = val * P + v[i];
			if (i + len < sz) {
				tmp = tmp * P + v[i + len];
			}
		}
		if (finded) ans_seq.push_back(k);
	}
}



bool canMatch(const vector<vector<LL> > &vec, const vector<LL> &seq, int len) {
	int sz = seq.size();
	set<LL> hs;
	LL tmp = 0;
	for (int i = 0; i < len; ++i) {
		tmp = tmp * P + seq[i];
	}
	LL val = 0;
	for (int i = 0; i < sz - len + 1; ++i) {
		LL temp = tmp - val * p[len];
		hs.insert(temp);
		val = val * P + seq[i];
		if (i + len < sz) {
			tmp = tmp * P + seq[i + len];
		}
	}

	bool finded = false;
	for (int k = 0; k < vec.size(); ++k) {
		const vector<LL> &v = vec[k];
		if (v.size() < len) continue;
		int sz = v.size();
		LL tmp = 0;
		for (int i = 0; i < len; ++i) {
			tmp = tmp * P + v[i];
		}
		LL val = 0;
		for (int i = 0; i < sz - len + 1; ++i) {
			LL temp = tmp - val * p[len];
			if (hs.find(temp) != hs.end()) {
				finded = true;
				break;
			}
			val = val * P + v[i];
			if (i + len < sz) {
				tmp = tmp * P + v[i + len];
			}
		}
		if (finded) break;
	}
	return finded;
}


int getLongest(const vector<vector<LL> > &vec, const vector<LL> &seq) {
	int L = 0, R = seq.size();
	while (L < R) {
		int mid = (L + R) / 2;
		if (canMatch(vec, seq, mid + 1)) {
			L = mid + 1;
		} else {
 			R = mid;
		}
	}
	return L;
}



int main() {


	freopen("in.txt", "r", stdin);

	p[0] = 1;
	for (int i = 1; i <= 10000; ++i) {
		p[i] = p[i - 1] * P;
	}
	int n;
	while (scanf("%d\n", &n) != EOF) {
		vector<vector<LL> > vec;
		vector<string> fileName;
		for (int i = 0; i < n; ++i) {
			vector<LL> seq;
			int flag = 0;
			while (gets(s_)) {
				int len = strlen(s_);
				string s = washStr(s_, len);
				if (s == "***END***") {
					break;
				}
				if (s == "") {
					continue;
				}
				if (!flag) {
					fileName.push_back(s);
					flag = 1;
					continue;
				}
				seq.push_back(toHash(s));
			}
			vec.push_back(seq);
		}
		vector<LL> seq;
		while (gets(s_)) {
			int len = strlen(s_);
			string s = washStr(s_, len);
			if (s == "***EOF***") {
				break;
			}
			if (s == "") {
				continue;
			}
			seq.push_back(toHash(s));
		}
		int ans = getLongest(vec, seq);
		if (ans == 0) {
			puts("0");
		} else {
			printf("%d", ans);
			vector<int> ans_seq;
			canMatch(vec, seq, ans, ans_seq);
			for (int i = 0; i < ans_seq.size(); ++i) {
				printf(" %s", fileName[ans_seq[i]].c_str());
			}
			puts("");
		}
	}
	return 0;
}
