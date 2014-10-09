#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;


struct point {
	int x, y;
	point(int x_ = 0, int y_ = 0):x(x_), y(y_) {}
	friend int operator* (const point& p1, const point& p2);
};

int operator* (const point& p1, const point& p2) {
	return p1.x * p2.y - p2.x * p1.y;
}

point operator- (const point& p1, const point& p2) {
	return point(p1.x - p2.x, p1.y - p2.y);
}

double dist(const point& p1, const point& p2) {
	point p = p1 - p2;
	return sqrt((double)(p.x * p.x + p.y * p.y));
}


int main() {

	freopen("in.txt", "r", stdin);


	int T, ca = 0;
	int X1, Y1, X2, Y2;
	while (cin >> X1 >> Y1 >> X2 >> Y2) {
		if (X1 == 0 && Y1 == 0 && X2 == 0 && Y2 == 0) break;
		point p1(X1, Y1);
		point p2(X2, Y2);
		cin >> X1 >> Y1 >> X2 >> Y2;
		point p3(X1, Y1);
		point p4(X2, Y2);

		bool intersect = false;

		point l1 = p3 - p2;
		point l2 = p1 - p2;
		point l3 = p4 - p2;

		typedef long long LL;

		LL tmp1 = l1 * l2;
		LL tmp2 = l2 * l3;

		l1 = p1 - p3;
		l2 = p4 - p3;
		l3 = p2 - p3;

		LL tmp3 = l1 * l2;
		LL tmp4 = l2 * l3;

		if (tmp1 * tmp2 > 0 && tmp3 * tmp4 > 0) {
			intersect = true;
		}


		double ans = 1000000000;
		if (intersect) {
			ans = min(dist(p1, p3) + dist(p2, p3), dist(p1, p4) + dist(p2, p4));
		} else {
			ans = dist(p1, p2);
		}

		printf("Case %d: %.3lf\n", ++ca, ans / 2);

 	}
	return 0;
}
