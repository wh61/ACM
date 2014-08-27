#include <iostream>
#include <cstdio>
#include <cmath>


using namespace std;

long double r, R;
const long double eps = 1e-19;
const long double pi = acos(-1.0);


inline long double getA(long double a) {
	long double A = 2 * a;
	long double tmp = ( sin((pi - a) / 4) / cos((pi - a) / 4) ) * sin(A / 2) * R;
	return tmp;
}


inline double getr(double a, double b, double c) {

}



int main() {

	freopen("in.txt", "r", stdin);

	while (cin >> r >> R) {
		if (r > R / 2 + 1e-10) {
			puts("NO Solution!");
			continue;
		}
		long double LL = 1e-19, RR = pi / 3;
		while (LL + eps < RR) {
			long double mid = (LL + RR) / 2;
			long double val = getA(mid);
			if (val > r) RR = mid;
			else LL = mid;
		}

		long double a = LL;

	//	printf("%.4lf\n", (double)getA(a));

		long double L1 = sin(a) * R * 2;
		long double L2 = sin((pi - a) / 2) / sin(a) * L1;

		double l1 = L1, l2 = L2;

		printf("%.9lf %.9lf %.9lf\n", l1, l2, l2);


	}
	return 0;
}

