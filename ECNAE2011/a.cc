#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const size_t maxn = 1010;

int w[maxn];
char s1[maxn];
char s2[maxn];



vector<int> merge(const vector<int> &v1, const vector<int> &v2, int K) {
	int sz1 = v1.size();
	int sz2 = K;
	int i = 0;
	int j = 0;
	vector<int> v;
	for (int k = 0; k < sz1 + sz2; ++k) {
		if (i == sz1) {
			v.push_back(v2[j++]);
		} else if (j == sz2) {
			v.push_back(v1[i++]);
		} else {
			if (v1[i] > v2[j]) {
				v.push_back(v1[i++]);
			} else {
				v.push_back(v2[j++]);
			}
		}
	}
	return v;
}


int main() {

	freopen("in.txt", "r", stdin);

	int n, ca = 0;
	while (scanf("%d", &n) != EOF) {
		if (n == 0) break;
		scanf("%s", s1);
		scanf("%s", s2);
		for (int i = 0; i < n; ++i) {
			scanf("%d", w + i);
		}

		vector<int> v10, v01, v11;
		for (int i = 0; i < n; ++i) {
			if (s2[i] == '0'  && s1[i] == '1') {
				v10.push_back(w[i]);
			} else if (s1[i] == '0' && s2[i] == '1') {
				v01.push_back(w[i]);
			} else if (s1[i] == '1' && s2[i] == '1'){
				v11.push_back(w[i]);
			}
		}
		int sz = v11.size();

		typedef long long LL;

		LL ans = 10000000000000000;

		sort(v10.begin(), v10.end());
		sort(v01.begin(), v01.end());
		sort(v11.begin(), v11.end());

		reverse(v11.begin(), v11.end());
		reverse(v10.begin(), v10.end());
		reverse(v01.begin(), v01.end());

		LL CUR = 0;

		for (int i = 0; i < n; ++i) {
			if (s1[i] == '1') {
				CUR += w[i];
			}
		}


		for (int k = 0; k <= sz; ++k) {
			LL tmp = 0;
			vector<int> vec1 = merge(v10, v11, k);
			vector<int> vec2 = merge(v01, v11, k);
			LL cur = CUR;
			int sz1 = vec1.size();
			for (int i = 0; i < sz1; ++i) {
				cur -= vec1[i];
				tmp += cur;
			}
			int sz2 = vec2.size();
			for (int i = sz2 - 1; i >= 0; --i) {
				cur += vec2[i];
				tmp += cur;
			}
			ans = min(ans, tmp);
		}

		printf("Case %d: ", ++ca);
		cout << ans << endl;
	}
	return 0;
}
