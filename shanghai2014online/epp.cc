#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>



using namespace std;

const int maxn = 66;


int n, m, K;

struct point {
	int x, y;
	point(int x_ = 0, int y_ = 0):x(x_), y(y_) {}
}p[maxn];


typedef long long LL;

LL dist(const point& p1, const point& p2) {
	return (LL)abs(p1.x - p2.x) + (LL)abs(p1.y - p2.y);
}

LL dis[maxn][maxn];

const int maxnode = 5000;
const int MaxM = 62;
const int MaxN = 62;

struct DLX
{
    int n,m,size;
    int U[maxnode],D[maxnode],R[maxnode],L[maxnode],Row[maxnode],Col[maxnode];
    int H[MaxN],S[MaxN];
    int ands,ans[MaxN];
    void init(int _n,int _m)
    {
        n = _n;
        m = _m;
        for(int i = 0;i <= m;i++)
        {
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i-1;
            R[i] = i+1;
        }
        R[m] = 0; L[0] = m;
        size = m;
        for(int i = 1;i <= n;i++)
            H[i] = -1;
    }
    void Link(int r,int c)
    {
        ++S[Col[++size]=c];
        Row[size] = r;
        D[size] = D[c];
        U[D[c]] = size;
        U[size] = c;
        D[c] = size;
        if(H[r] < 0)H[r] = L[size] = R[size] = size;
        else
        {
            R[size] = R[H[r]];
            L[R[H[r]]] = size;
            L[size] = H[r];
            R[H[r]] = size;
        }
    }
    void remove(int c)
    {
        for(int i = D[c];i != c;i = D[i])
            L[R[i]] = L[i], R[L[i]] = R[i];
    }
    void resume(int c)
    {
        for(int i = U[c];i != c;i = U[i])
            L[R[i]]=R[L[i]]=i;
    }
    bool v[maxnode];
    int f()
    {
        int ret = 0;
        for(int c = R[0];c != 0;c = R[c])v[c] = true;
        for(int c = R[0];c != 0;c = R[c])
            if(v[c])
            {
                ret++;
                v[c] = false;
                for(int i = D[c];i != c;i = D[i])
                    for(int j = R[i];j != i;j = R[j])
                        v[Col[j]] = false;
            }
        return ret;

    }
    bool Dance(int d)
    {
        if(d + f() > K)return false;
        if(R[0] == 0)return d <= K;
        int c = R[0];
        for(int i = R[0];i != 0;i = R[i])
            if(S[i] < S[c])
                c = i;
        for(int i = D[c];i != c;i = D[i])
        {
            remove(i);
            for(int j = R[i];j != i;j = R[j])remove(j);
            if(Dance(d+1))return true;
            for(int j = L[i];j != i;j = L[j])resume(j);
            resume(i);
        }
        return false;
    }
};

DLX g;


int check(LL mid){
	g.init(n, n);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (dis[i][j] <= mid) {
				g.Link(i, j);
			}
		}
	}
	return g.Dance(0);
}






int main() {


	freopen("in.txt", "r", stdin);

	int T, ca = 0;
	cin >> T;
	while (T--) {
		cin >> n >> K;
		for (int i = 1; i <= n; ++i) {
			int a, b;
			cin >> a >> b;
			p[i] = point(a, b);
		}

		LL L = 0, R = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				dis[i][j] = dist(p[i], p[j]);
				R = max(R, dis[i][j]);
			}
		}
		while (L < R) {
			LL mid = (L + R) / 2;
			int val = check(mid);
			if (val) R = mid;
			else L = mid + 1;
		}

		printf("Case #%d: ", ++ca);
		cout << L << endl;
	}

	return 0;
}

