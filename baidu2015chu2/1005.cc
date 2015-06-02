#include <iostream>
#include <cstring>
#include <cstdio>



using namespace std;


const int MAXN = 100010;  
const int INF = 0x3f3f3f3f;  
  
int n;  
  
int A[MAXN], S[MAXN];  
int d[MAXN];  
  
void init()  
{  
    for(int i = 1; i <= n; i++) S[i] = INF; //这很重要，与upper_bound有关。  
    memset(d, 0, sizeof(d));  
}  

int BSearch(int x, int y, int v) //二分求上界  
{  
    while(x <= y)  
    {  
        int mid = x+(y-x)/2;  
        if(S[mid] <= v) x = mid+1;  
        else y = mid-1;  
    }  
    return x;  
}  
  
int dp()  
{  
    init();  
    int ans = 0;  
    for(int i = 1; i <= n; i++)  
    {  
        int x = 1, y = i;  
        int pos = BSearch(x, y, A[i]);  
        d[i] = pos;  
        S[d[i]] = min(S[d[i]], A[i]);  
        ans = max(ans, d[i]);  
    }  
 //   printf("%d\n", ans);  
	return ans;
}



int main() {
	freopen("1005.in", "r", stdin);
	int T, ca = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", A + i);
			A[i] -= i;
		}
		int ans = n - dp();
		printf("Case #%d:\n%d\n", ++ca, ans);
	}
	return 0;
}
