#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 3000;
const int inf = 1000000000;

struct event{
	int t, type;
	event(int t_ = 0, int type_ = 0):t(t_), type(type_) {}
};

bool cmp(const event& a, const event& b) {
	return a.t < b.t;
}

int t[maxn];
int dp[maxn];

int main() {

	freopen("in.txt", "r", stdin);

	int n;
	while (scanf("%d", &n) != EOF) {
		vector<event> vec;
		for (int i = 0; i < n; ++i) {
			int hh, mm;
			char ch;
			scanf("%d:%d %c", &hh, &mm, &ch);
			int t = hh * 60 + mm;
			int type = ch == 'U' ? 1 : 0;
			vec.push_back(event(t, type));
		}
		sort(vec.begin(), vec.end(), cmp);
		int ans_1 = 0;
		int U = 0, last = -1000;
		int pay = 44;

		for (int i = 0; i < n; ++i) {
			int t = vec[i].t, type = vec[i].type;
			if (t - last <= 90) {
				if (type == 0) {
					ans_1 += 44 - pay;
					pay = 44;
					continue;
				} else if (type == 1 && U == 0) {
					U++;
					ans_1 += 44 - pay;
					pay = 44;
					continue;
				} else if (type == 1 && U == 1) {
					U = 1;
					last = t;
					ans_1 += 28;
					pay = 28;
				}
			} else {
				if (type == 0) {
					pay = 26;
					ans_1 += 26;
					last = t;
					U = 0;
				} else if (type == 1) {
					pay = 28;
					ans_1 += 28;
					last = t;
					U = 1;
				}
			}
		}

		dp[n] = 0;
		for (int i = n - 1; i >= 0; --i) {
			dp[i] = inf;

				int U = 0;
				for (int j = i; j < n; ++j) {
					if (vec[j].type == 1) {
						++U;
					}
					if (vec[j].t - vec[i].t <= 90 && U < 2) {
						dp[i] = min(dp[i], dp[j + 1] + 44);
					} else {
						break;
					}
				}

			if (vec[i].type == 0) {
				dp[i] = min(dp[i], dp[i + 1] + 26);
			} else {
				dp[i] = min(dp[i], dp[i + 1] + 28);
			}
		}
		printf("%d %d\n", ans_1, dp[0]);
	}
	return 0;
}
