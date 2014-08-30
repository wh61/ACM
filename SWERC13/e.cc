#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

char s_[33];

typedef unsigned long long LL;

const LL P1 = 10007;
const LL P2 = 100007;

inline LL getHash(const string& s) {
	int sz = s.size();
	LL val = 0;
	for (int i = 0; i < sz; ++i) {
		int tmp = s[i];
		if ('a' <= s[i] && s[i] <= 'z') tmp -= 'a' - 'A';
		val = val * P1 + tmp;
	}
	return val;
}


int main() {


	freopen("in.txt", "r", stdin);

	int n = 0, ca = 0;

	while (scanf("%d", &n) != EOF) {
		if (ca > 0) puts("");

	    printf("Learning case %d\n", ++ca);
		//vector<vector<string> > v;
		vector<LL> seq;

		set<LL> wd;
		set<LL> sq;

		wd.insert(getHash("joe"));

		while (scanf("%s", s_)) {
			string s = s_;//. , : ; ? !
			if (s == "*" || s == "." || s == "," || s == ":" || s == ";" || s == "?" || s == "!") {
			//	if (seq.size() != 0) v.push_back(seq);
				if (seq.size() == 0) {
				    if (s == "*") break; else continue;
				}
				for (int i = 0; i < seq.size(); ++i) {
					LL val = 0;
					for (int j = i; j < min(i + n, (int)seq.size()); ++j) {
						val = val * P2 + seq[j];
						sq.insert(val);
					}
				}
				seq.clear();
				if (s == "*") break;
				else continue;
			}
			LL val = getHash(s);
			seq.push_back(val);
			wd.insert(val);
		}

		vector<string> S;

		while (scanf("%s", s_)) {
			string s = s_;//. , : ; ? !
			if (s == "#" || s == "." || s == "," || s == ":" || s == ";" || s == "?" || s == "!") {
				if (seq.size() == 0) {
				    if (s == "#") break; else continue;
				}

				int buzhidao = false;

				for (int i = 0; i < seq.size(); ++i) {
					LL val = 0;
					for (int j = i; j < min(i + n, (int)seq.size()); ++j) {
						val = val * P2 + seq[j];
						if (sq.find(val) == sq.end()) buzhidao = true;
						sq.insert(val);
					}
				}

				if (seq.size() == 1) buzhidao = false;

				if (buzhidao) {
					printf("What does the sentence \"");

					for (int i = 0; i < S.size(); ++i) {
						if (i) printf(" ");
						printf("%s", S[i].c_str());
					}

					printf("\" mean?\n");
				}

				seq.clear();
				S.clear();
				if (s == "#") break;
				else continue;
			}

			LL val = getHash(s);

			if (wd.find(val) == wd.end()) {
				printf("What does the word \"%s\" mean?\n", s.c_str());
			}

			wd.insert(val);
			seq.push_back(val);
			S.push_back(s);
		}



	}
	return 0;
}
