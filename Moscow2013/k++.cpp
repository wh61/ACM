#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <set>
#include <new>
#include <map>
#define see(x) cerr<<#x<<" = " << (x) << endl
using namespace std;
const unsigned int MASK=0x7FFFFFFF;
const int N = 200010;
int n,k;
unsigned int A,B,C;
unsigned int heap[N];
int size, hs;
unsigned int tmp;
inline void ins(unsigned int t)
{
  if (size == k)
  {
    if(t<=heap[1])
      return;
    heap[1] = t;
    for(int i=1;i<=hs;)
    {
      int m = i;
      int l = i<<1;
      int r = l+1;
      if (heap[l]<heap[i])
        m = l;
      if (r<=size && heap[r]<heap[m])
        m = r;
      if (m==i)
        break;
		tmp = heap[i];
		heap[i] = heap[m];
		heap[m] = tmp;
      //swap(heap[i],heap[m]);
      i = m;
    }
  }
  else
  {
    heap[++size] = t;
    hs = size>>1;
    for(int i=size;i>1;i>>=1)
      if(heap[i]<heap[i>>1]) {
     //   swap(heap[i],heap[i>>1]);
        tmp = heap[i];
        heap[i] = heap[i >> 1];
        heap[i >> 1] = tmp;
	}
      else
        break;
  }
}
inline unsigned int pop()
{
  unsigned int ans = heap[1];
  heap[1] = heap[size--];
  int hs = size>>1;
  for(int i=1;i<=hs;)
  {
    int m = i;
    int l = i<<1;
    int r = l+1;
    if (heap[l]<heap[i])
      m = l;
    if (r<=size && heap[r]<heap[m])
      m = r;
    if (m==i)
      break;
  tmp = heap[i];
  heap[i] = heap[m];
  heap[m] = tmp;
    //swap(heap[i],heap[m]);
    i = m;
  }
  return ans;
}
unsigned int x_, y_, z_, ans[N];
int len;
int main()
{
#ifndef ONLINE_JUDGE
  freopen("in","r",stdin);
  freopen("out","w",stdout);
#endif
  scanf("%d%d",&n,&k);
  scanf("%u%u%u%u%u",&x_,&y_,&A,&B,&C);
  x_ &= MASK;
  y_ &= MASK;
  A &= MASK;
  B &= MASK;
  C &= MASK;
  int x = x_, y = y_;
  for(int i=1; i<=n; ++i)
  {
    z_ = (A*x_ + B*y_ + C)& MASK;
    if (i%21 == 0)
      ins(z_);
    x_ = y_;
    y_ = z_;
  }
  x_ = x;
  y_ = y;
  for(int i=1; i<=n; ++i)
  {
    z_ = (A*x_ + B*y_ + C)& MASK;
    if (i%21 != 0)
      ins(z_);
    x_ = y_;
    y_ = z_;
  }
  while(size) ans[++len]=pop();
  for(int i=len; i>=1; --i)
    printf("%u ", ans[i]);
  return 0;
}
