#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <algorithm>


using namespace std;


struct student {
	int t, id;
	student(int t_, int id_):t(t_), id(id_) {}
	student() {}
}a[222222];

int TransformTime(int h, int m, int s) {
	return ((h * 60) + m) * 60 + s;
}

bool cmp(const student& a, const student& b) {
	if (a.t == b.t) return a.id < b.id;
	return a.t < b.t;
}


int main() {

//	freopen("in.txt", "r", stdin);

	int T;
	scanf("%d", &T);
	while (T--) {
		int n, m;
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++i) {
			int h, m, s;
			scanf("%d:%d:%d", &h, &m, &s);
			int val = TransformTime(h, m, s);
			a[i] = student(val, i + 1);
		}
		sort(a, a + n, cmp);
		int st = 0, ed = a[0].t + m;
		int ans = 1;
		vector<int> v;
		v.push_back(a[0].id);
		for (int i = 1; i < n; ++i) {
			if (a[i].t >= ed) {
				ans++;
				ed = a[i].t + m;
				v.push_back(a[i].id);
			} else continue;
		}
		sort(v.begin(), v.end());
		printf("%d\n%d", ans, v[0]);
		for (int i = 1; i < v.size(); ++i) {
			printf(" %d", v[i]);
		}
		puts("");
	}
	return 0;
}

