#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <string>
#include <cstring>
#define INF 2000000000
#define MAXN 1005
#define MAXM 10005
#define eps 1e-4
using namespace std;
typedef int type;

struct node
{
    int u, v;
    type w;
}edge[MAXN * MAXN];
int pre[MAXN], id[MAXN], vis[MAXN], n, m;
type in[MAXN];

type Directed_MST(int root, int V, int E)
{
    type ret = 0;
    while(true)
    {
        //1.找最小入边
        for(int i = 0; i < V; i++)
           in[i] = INF;
        for(int i = 0; i < E; i++)
        {
            int u = edge[i].u;
            int v = edge[i].v;
            if(edge[i].w < in[v] && u != v)
              {pre[v] = u; in[v] = edge[i].w;}
        }
        for(int i = 0; i < V; i++)
        {
            if(i == root) continue;
            if(in[i] == INF) return -1;//除了根以外有点没有入边,则根无法到达它
        }
        //2.找环
        int cnt = 0;
        memset(id, -1, sizeof(id));
        memset(vis, -1, sizeof(vis));
        in[root] = 0;
        for(int i = 0; i < V; i++) //标记每个环
        {
            ret += in[i];
            int v = i;
            while(vis[v] != i && id[v] == -1 && v != root)  //每个点寻找其前序点，要么最终寻找至根部，要么找到一个环
            {
                vis[v] = i;
                v = pre[v];
            }
            if(v != root && id[v] == -1)//缩点
            {
                for(int u = pre[v]; u != v; u = pre[u])
                    id[u] = cnt;
                id[v] = cnt++;
            }
        }
        if(cnt == 0) break; //无环   则break
        for(int i = 0; i < V; i++)
            if(id[i] == -1) id[i] = cnt++;
        //3.建立新图
        for(int i = 0; i < E; i++)
        {
            int u = edge[i].u;
            int v = edge[i].v;
            edge[i].u = id[u];
            edge[i].v = id[v];
            if(id[u] != id[v]) edge[i].w -= in[v];
        }
        V = cnt;
        root = id[root];
    }
    return ret;
}

const int maxn = 1005;
int A[maxn];
int mp[55][555];

inline void add(int i, int a, int b, int c) {
	edge[i].u = a;
	edge[i].v = b;
	edge[i].w = c;
}


int main() {

//	freopen("in.txt", "r", stdin);

	int n, m;
	while (scanf("%d%d", &n, &m) != EOF) {

		if (n == 0 && m == 0) break;

		for (int i = 1; i <= n; ++i) scanf("%d", A + i);

		int cnt = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= A[i]; ++j) {
				mp[i][j] = ++cnt;
			}
		}

		int s = 0;
		int tot = 0;

		for (int i = 1; i <= n; ++i) {
			add(tot++, s, mp[i][0], 0);
			for (int j = A[i]; j > 0; --j) {
				add(tot++, mp[i][j], mp[i][j - 1], 0);
			}
		}

		for (int i = 0; i < m; ++i) {
			int c, l1, d, l2, mm;
			scanf("%d%d%d%d%d", &c, &l1, &d, &l2, &mm);
			add(tot++, mp[c][l1], mp[d][l2], mm);
		}

		int ans = 0;

		ans = Directed_MST(s, cnt + 1, tot);
		printf("%d\n", ans);

	}
	return 0;
}






/*
int main()
{
    while(scanf("%d%d", &n, &m) != EOF)
    {
        for(int i = 0; i < n; i++)
           scanf("%lf%lf", &p[i].x, &p[i].y);
        for(int i = 0; i < m; i++)
        {
            scanf("%d%d", &edge[i].u, &edge[i].v);
            edge[i].u--;
            edge[i].v--;
            if(edge[i].u != edge[i].v) edge[i].w = dis(p[edge[i].u], p[edge[i].v]);
            else edge[i].w = INF; //去除自环
        }
        type ans = Directed_MST(0, n, m);
        if(ans == -1) printf("poor snoopy\n");
        else printf("%.2f\n", ans);
    }
    return 0;
}
*/
