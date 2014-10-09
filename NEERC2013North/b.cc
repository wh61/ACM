#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

const int maxn = 10;
const int maxm = 1111;

string name[maxn];
char s[maxm][maxn];
int cnt[maxn + 1];

int main() {
	freopen("bad.in", "r", stdin);
	freopen("bad.out", "w", stdout);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		cin >> name[i];
	}
	for (int i = 0; i < m; ++i) {
		string str;
		cin >> str;
		for (int j = 0; j < str.size(); ++j) s[i][j] = str[j];
	}
	memset(cnt, 0 ,sizeof(cnt));
	for (int i = 0; i < m; ++i) {
		int tot = 0;
		for (int j = 0; j < n; ++j) if (s[i][j] == 'X') ++tot;
		if (tot != 1) {
			cnt[n]++;
			continue;
		}
		int k = 0;
		for (int j = 0; j < n; ++j) if (s[i][j] == 'X') k = j;
		cnt[k]++;
	}
	vector<pair<int, int> > vec;
	for (int i = 0; i < n; ++i) {
		vec.push_back(make_pair(m - cnt[i], i));
	}
	sort(vec.begin(), vec.end());
	for (int i = 0; i < n; ++i) {
		printf("%s %.2lf%%\n", name[vec[i].second].c_str(), (m - vec[i].first) * 100.0 / m);
	}
	printf("Invalid %.2lf%%\n", cnt[n] * 100.0 / m);

	return 0;
}
