#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;


#define maxn 55000

const int inf = 1000000000;

struct Node{
	//int val;
	int add; //延迟标记
	int mi, mx, dx, dy;
	//
	int l,r;
	Node *ls,*rs; //左右儿子
	void init(int _l,int _r){
		l=_l,r=_r; ls=rs=NULL; add=0;//延迟信息必须清0!!!
		mi = inf, mx = -inf, dx = dy = 0;
	}
	int mid(){ return (l+r)>>1; }
	void push_down(){ //保证有儿子
		ls->add+=add;
		rs->add+=add;
		mi += add;
		mx += add;
		add=0;
		//if( ls->l==ls->r ) { ls->mi += ls->add; ls->mx += ls->add; ls->add=0; }
		//if( rs->l==rs->r ) { rs->mi += rs->add; rs->mx += rs->add; rs->add=0; }
	}
	void update(){ //保证有儿子
		mi = min(ls->mi + ls->add, rs->mi + rs->add);
		mx = max(ls->mx + ls->add, rs->mx + rs->add);
		dx = max(ls->dx, rs->dx);
		dy = max(ls->dy, rs->dy);
		dx = max(dx, (rs->mx + rs->add) - (ls->mi + ls->add));
		dy = max(dy, (ls->mx + ls->add) - (rs->mi + rs->add));
	}
	void modify(int a,int b,int val){
		if( l==a && r==b ){
			add+=val;
			//this->mi += add;
			//this->mx += add;
			//if( a==b ) { this->val+=add; add=0; }
			return;
		}
		push_down(); //要进入子树,先要把树根的延迟信息push下去
		if( b<=mid() ) ls->modify(a,b,val);
		else if( a>mid() ) rs->modify(a,b,val);
		else {
			ls->modify(a,mid(),val);
			rs->modify(mid()+1,b,val);
		}
		update();
	}
	/*int query(int id){
		if( l==r ) return val;
		push_down();
		if( id<=mid() ) return ls->query(id);
		else return rs->query(id);
	}*/

	void query1(int a,int b,int &MI, int &DY){
		if( l==a && r==b ){

			DY = max(DY, this->dy);
			DY = max(DY, this->mx + this->add - MI);
			MI = min(MI, this->mi + add);
			//this->mi += add;
			//this->mx += add;
			//if( a==b ) { this->val+=add; add=0; }
			return;
		}
		push_down(); //要进入子树,先要把树根的延迟信息push下去
		if( b<=mid() ) ls->query1(a,b, MI, DY);
		else if( a>mid() ) rs->query1(a,b, MI, DY);
		else {

			rs->query1(mid()+1,b,MI, DY);
			ls->query1(a,mid(),MI, DY);
		}
		update();
	}

	void query2(int a,int b,int &MX, int &DX){
		if( l==a && r==b ){

			DX = max(DX, this->dx);
			DX = max(DX, MX - (this->mi + this->add));
			MX = max(MX, this->mx + this->add);
			//this->mi += add;
			//this->mx += add;
			//if( a==b ) { this->val+=add; add=0; }
			return;
		}
		push_down(); //要进入子树,先要把树根的延迟信息push下去
		if( b<=mid() ) ls->query2(a,b, MX, DX);
		else if( a>mid() ) rs->query2(a,b, MX, DX);
		else {

			rs->query2(mid()+1,b,MX, DX);
			ls->query2(a,mid(),MX, DX);
		}
		update();
	}

}dd[maxn*5];
int e; // 初始化
Node* _alloc(int l,int r) { dd[e].init(l,r); return &dd[e++]; }
int d[maxn],ind;
Node* _make(int l,int r){ //构造一棵树,并返回树根
	Node* p=_alloc(l,r);
	if( l==r ) {//这里用到d数组,需要初始化
		p->mi = d[l];
		p->mx = d[l];
		p->dx = p->dy = 0;
		p->add = 0;
		return p;
	}
	p->rs=_make(p->mid()+1,r);
	p->ls=_make(l,p->mid());
	p->update();
	return p;
}//********************线段树模板结束******************

vector<int> adj[maxn]; //邻接表

struct Tree{
	Node *root;
	int dep,pa; //这段树链的深度,父亲点
}tree[maxn];
int tid,sz[maxn],vst[maxn];

struct Info{
	int tid,tind; //每个节点所在的 树编号,树上的id
}info[maxn];

int count(int u){ //计算子树大小
	sz[u]=vst[u]=1;
	for(int i=0;i<adj[u].size();i++){
		int v=adj[u][i];
		if( vst[v]==0 ){
			sz[u]+=count(v);
		}
	}
	return sz[u];
}
int v[maxn]; //初始值

queue<int> q; //son dep pa
void divide(int u,int dep,int pa){ //树链剖分 非递归写法
	q.push(u); q.push(dep); q.push(pa);
	while( !q.empty() ){
		u=q.front(); q.pop();
		dep=q.front(); q.pop();
		pa=q.front(); q.pop();
		ind=0;
		while( true ){
			vst[u]=1;
			info[u].tid=tid, info[u].tind=ind; d[ind++]=v[u];
			int ma=-1, ver=-1; // size,vertex
			for(int i=0;i<adj[u].size();i++){
				int v=adj[u][i];
				if( vst[v] ) continue;
				if( ma==-1 ){
					ma=sz[v]; ver=v;
				}else if( sz[v]>ma ){
					q.push(ver); q.push(dep+1); q.push(u);
					ma=sz[v], ver=v;
				}else{
					q.push(v);   q.push(dep+1); q.push(u);
				}
			}
			if( ma<0 ) break;
			u=ver;
		}
		tree[tid].dep=dep; tree[tid].pa=pa;
		tree[tid++].root=_make(0,ind - 1);/////////////////////////
	}
}
void paint(int a,int b,int val){ //a到b的树链上的前权值全部加val
	int ta=info[a].tid, tb=info[b].tid;
	int ida=info[a].tind, idb=info[b].tind;
	if( ta == tb ){
		if( ida>idb ) swap(ida,idb);
		tree[ta].root->modify(ida,idb,val);
		return;
	}
	if( tree[ta].dep > tree[tb].dep){
		tree[ta].root->modify(0,ida,val);
		paint(tree[ta].pa,b,val);
	}else {
		tree[tb].root->modify(0,idb,val);
		paint(a,tree[tb].pa,val);
	}
}

void paint1(int a,int b,int &MI, int& DY){ //a到b的树链上的前权值全部加val
	int ta=info[a].tid, tb=info[b].tid;
	int ida=info[a].tind, idb=info[b].tind;
	if( ta == tb ){
		if( ida>idb ) swap(ida,idb);
		tree[ta].root->query1(ida,idb, MI, DY);
		return;
	}
	if( tree[ta].dep > tree[tb].dep){
		tree[ta].root->query1(0,ida, MI, DY);
		paint1(tree[ta].pa,b,MI, DY);
	}else {
		tree[tb].root->query1(0,idb, MI, DY);
		paint1(a,tree[tb].pa,MI, DY);
	}
}



void paint2(int a,int b,int &MX, int& DX){ //a到b的树链上的前权值全部加val
	int ta=info[a].tid, tb=info[b].tid;
	int ida=info[a].tind, idb=info[b].tind;
	if( ta == tb ){
		if( ida>idb ) swap(ida,idb);
		tree[ta].root->query2(ida,idb, MX, DX);
		return;
	}
	if( tree[ta].dep > tree[tb].dep){
		tree[ta].root->query2(0,ida, MX, DX);
		paint2(tree[ta].pa,b,MX, DX);
	}else {
		tree[tb].root->query2(0,idb, MX, DX);
		paint2(a,tree[tb].pa,MX, DX);
	}
}


void paintfa(int a,int b,int &father){ //a到b的树链上的前权值全部加val
	int ta=info[a].tid, tb=info[b].tid;
	int ida=info[a].tind, idb=info[b].tind;
	if( ta == tb ){
		if( ida>idb ) father=b;else father=a;
		return;
	}
	if( tree[ta].dep > tree[tb].dep){
		paintfa(tree[ta].pa,b,father);
	}else {
		paintfa(a,tree[tb].pa,father);
	}
}


//*************以上必须***************************

int main(){


	freopen("in.txt", "r", stdin);

	int T, ca = 0;
	scanf("%d", &T);
	int n,m,Q;
	while(T--){
		scanf("%d", &n);
		e=0; //
		for(int i=1;i<=n;i++) adj[i].clear();
		for(int i=1;i<=n;i++) scanf("%d",v+i);
		for(int i=1;i<n;i++){
			int u,v; scanf("%d %d",&u,&v);
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		memset(vst,0,sizeof(vst));
		count(1);
		memset(vst,0,sizeof(vst));
		tid=0; divide(1,0,-1);

		scanf("%d", &Q);

		typedef long long LL;
		LL ansCnt = 0;

		while( Q-- ){
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			int MI=inf,MX=-inf,DX=-inf,DY=-inf;
			int father;
		//	if (x > y) swap(x, y);
			paintfa(x,y,father);
			paint1(x,father,MI,DY);
			paint2(father,y,MX,DX);
			int ans;
			ans=max(DX,DY);
			ans=max(MX-MI,ans);
			ans=max(0,ans);
			//ansCnt += ans;
			printf("%d\n", ans);
			paint(x, y, z);
		}
	}
}
