#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

int cnt[10];
int a[10];


inline void dec(int val) {
	for (int i = 0; i < 4; ++i)
	{
		cnt[val % 10]--;
		val /= 10;
	}
}

inline void inc(int val) {
	for (int i = 0; i < 4; ++i)
	{
		cnt[val % 10]++;
		val /= 10;
	}
}

inline void deccc(int val) {
	for (int i = 0; i < 7; ++i)
	{
		cnt[val % 10]--;
		val /= 10;
	}
}

inline void inccc(int val) {
	for (int i = 0; i < 7; ++i)
	{
		cnt[val % 10]++;
		val /= 10;
	}
}



inline bool check() {
	bool ok = true;
	for (int i = 0; i < 10; ++i) if (cnt[i] < 0) {
		ok = false;
		break;
	}
	return ok;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	for (int i = 0; i < 10; ++i) {
		cin >> a[i];
		cnt[i] = a[i];
	}

	bool ansed = false;
	int ans1 = -1, ans2 = -1;

	for (int val1 = 0; val1 < 10000; ++val1)
	{
		if (ansed) break;
		dec(val1);
		if (!check()) {
			inc(val1);
			continue;
		}
		int rs1, rs2, rs3, rs4, val2, rs;
		for (int num24 = 0; num24 < 10; ++num24) {
			if (ansed) break;
			rs4 = num24 * val1;
			if (rs4 > 9999) break;
			dec(rs4);
			if (!check()) {
				inc(rs4);
				continue;
			}
			for (int num23 = 0; num23 < 10; ++num23) {
				if (ansed) break;
				rs3 = num23 * val1;
				if (rs3 > 9999) break;
				dec(rs3);
				if (!check()) {
					inc(rs3);
					continue;
				}
				for (int num22 = 0; num22 < 10; ++num22) {
					if (ansed) break;
					rs2 = num22 * val1;
					if (rs2 > 9999) break;
					dec(rs2);
					if (!check()) {
						inc(rs2);
						continue;
					}
					for (int num21 = 0; num21 < 10; ++num21) {
						if (ansed) break;
						rs1 = num21 * val1;
						if (rs1 > 9999) break;
						dec(rs1);
						if (!check()) {
							inc(rs1);
							continue;
						}
						val2 = num24 * 1000 + num23 * 100 + num22 * 10 + num21;
						dec(val2);
						if (!check()) {
							inc(val2);
							inc(rs1);
							continue;
						}
						rs = val1 * val2;
						if (rs > 9999999) {
							inc(val2);
							inc(rs1);
							continue;
						}


						deccc(rs);

						if (!check()) {
							inccc(rs);
							inc(val2);
							inc(rs1);
							continue;
						}

						ansed = true;
						for (int i = 0; i < 10; ++i) {
							if (cnt[i] != 0) ansed = false;
						}

						if (ansed) {
							ans1 = val1;
							ans2 = val2;
						}

						inccc(rs);
						inc(rs1);
						inc(val2);
					}
					inc(rs2);
				}
				inc(rs3);
			}
			inc(rs4);
		}
		inc(val1);
	}

	printf("%d\n", ans1);
	printf("%d\n", ans2);



	return 0;
}
