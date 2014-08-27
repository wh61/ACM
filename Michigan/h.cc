#include <iostream>
#include <cstring>
#include <cstdio>
#include <stack>
#include <vector>
#include <map>

using namespace std;

int A[6666], B[6666], C[6666];
int pool[35550000];

const size_t bit = 32;

int N;

inline void zip(int *a, int *num, int sz) {
    for (int i = 0; i < N; ++i) a[i] = 0;
    for (int i = 0; i < sz; ++i) {
        int ind = num[i] / bit;
        int bt = num[i] % bit;
        a[ind] |= 1 << bt;
    }
}

inline void OP(int *ans, int *a, int *b, char op) {
    if (op == '*') {

        for (int i = 0; i < N; ++i) ans[i] = a[i] & b[i];
    } else if (op == '+') {
        for (int i = 0; i < N; ++i) ans[i] = a[i] | b[i];
    } else if (op == '-') {
        for (int i = 0; i < N; ++i) ans[i] = ~b[i];
    }
}



int num[222222];
char s[22222];



int main() {


    freopen("in.txt", "r", stdin);

    int ca = 0;
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {



        int *pt_pool = pool;
        if (n == 0 && m == 0) break;

        N = n / bit + 2;
        int K;
        scanf("%d", &K);
        for (int i = 0; i < K; ++i) {
            scanf("%d", num + i);
            num[i]--;
        }
        zip(A, num, K);

        scanf("%d", &K);
        for (int i = 0; i < K; ++i) {
            scanf("%d", num + i);
            num[i]--;
        }
        zip(B, num, K);

        scanf("%s", s);

        map<char, int> mp;
        mp[')'] = 1;
        mp['+'] = 2;
        mp['*'] = 3;
        mp['-'] = 4;
        mp['('] = 0;

        stack<int*> val;
        stack<char> op;
        s[m] = ')';
        for (int i = 0; i <= m; ++i) {
            if (s[i] == 'A' || s[i] == 'B') {
                if (s[i] == 'A') val.push(A); else val.push(B);
            } else if (s[i] == '(') {
                op.push(s[i]);
            } else {
                int opVal = mp[s[i]];
                while (!op.empty() &&  mp[op.top()] >= opVal) {
                    char o = op.top();
                    op.pop();
                    int *lhs, *rhs;
                    rhs = val.top();
                    val.pop();
                    if (o != '-') {
                        lhs = val.top();
                        val.pop();
                    }
                    int *ans = pt_pool;
                    pt_pool += N + 2;
                    OP(ans, lhs, rhs, o);
                    val.push(ans);
                }
                if (i == m) break;
                if (s[i] == ')') op.pop(); else op.push(s[i]);
            }
        }

        int* rs = val.top();

        vector<int> v;
        for (int i = 0; i < n; ++i) {
            int ind = i / bit;
            int bt = i % bit;
            if (rs[ind] & (1 << bt)) v.push_back(i + 1);
        }
        int tot = v.size();

        printf("Case %d: %d", ++ca, tot);
        for (int i = 0; i < tot; ++i) {
            printf(" %d", v[i]);
        }
        puts("");

    }
    return 0;
}
