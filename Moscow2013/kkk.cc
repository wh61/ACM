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
const int N = 201000;
int n,k;
unsigned int A,B,C;
unsigned int heap[N];
int size, hs;
inline void ins(unsigned int t)
{
  if (size == k)
  {
    if(t<heap[1])
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
      swap(heap[i],heap[m]);
      i = m;
    }
  }
  else
  {
    heap[++size] = t;
    hs = size>>1;
    for(int i=size;i>1;i>>=1)
      if(heap[i]<heap[i>>1])
        swap(heap[i],heap[i>>1]);
      else
        break;
  }
}
unsigned int x_, y_, z_;
int main()
{
#ifndef ONLINE_JUDGE
  freopen("in.txt","r",stdin);
 // freopen("out.txt","w",stdout);
#endif
  scanf("%d%d",&n,&k);
  scanf("%u%u%u%u%u",&x_,&y_,&A,&B,&C);
  unsigned int x_1 = x_, x_0 = y_;
  if (A + B != 1 || C > 20000 || n < 1000000) {


  for(int i=1; i<=n; ++i)
  {
    z_ = (A*x_ + B*y_ + C)&MASK;
    ins(z_);
    x_ = y_;
    y_ = z_;
  }
  sort(heap+1,heap+size+1);
  for(int i=size;i>=1;--i)
    printf("%u ", heap[i]);

   return 0;



   }


	if (B == 1) {
		int pos = -1;
		unsigned int mx = 0;
		unsigned x = x_, y = y_, z = z_;
		for(int i=1; i<=n; ++i)
		{
				z = (A*x + B*y + C)&MASK;
				if (z > mx) {
					mx = z, pos = i;
				}
				x = y;
				y = z;
		}

		int L = -1, R = pos;
		for (int i = pos; i > 0; --i) {
			ins(mx);
			mx -= C;
			if (size < k) {
				L = i;
			} else {
				break;
			}
		}
		x = x_, y = y_, z = z_;
		for(int i=1; i<=n; ++i)
		{
				z = (A*x + B*y + C)&MASK;
				if (!(L <= i && i <= R)) { ins(z); }
				x = y;
				y = z;
		}


	sort(heap+1,heap+size+1);
  for(int i=size;i>=1;--i)
    printf("%u ", heap[i]);



		return 0;
	}


	if (A == 1) {
		int pos = -1;
		unsigned int mx = 0;
		unsigned int x = x_, y = y_, z = z_;

		for(int i=1; i<=n; ++i)
		{
				z = (A*x + B*y + C)&MASK;
				if (z > mx) {
					mx = z, pos = i;
				}
				x = y;
				y = z;
		}

		int L = -1, R = pos;
		for (int i = pos; i > 0; i -= 2) {
			ins(mx);
			mx -= C;
			if (size < k) {
				L = i;
			} else {
				break;
			}
		}
		x = x_, y = y_, z = z_;



		for(int i=1; i<=n; ++i)
		{
				z = (A*x + B*y + C)&MASK;
				if (i >= L && i <= R && ((pos - i) & 1) == 0) continue;
				ins(z);
				x = y;
				y = z;
		}

	sort(heap+1,heap+size+1);
  for(int i=size;i>=1;--i)
    printf("%u ", heap[i]);



		return 0;

	}



  return 0;
}
