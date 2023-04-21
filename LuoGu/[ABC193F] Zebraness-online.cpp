#include<bits/stdc++.h>
#define p(x,y) (((x)-1)*n+(y))
using namespace std;
const int maxn=5e4,inf=0x3f3f3f3f;
int n,tot,N;
char s[103][103];
namespace Edge{
	int head[maxn+5],flag=1;
	struct star{int to,nxt,val;}edge[3000005];
	inline void add(int u,int v,int val){
		edge[++flag]=(star){v,head[u],val},head[u]=flag;
	}
	inline void exadd(int u,int v,int val){add(u,v,val),add(v,u,0);}
}using namespace Edge;
namespace min_cut{
	const int S=0,T=maxn+1;
	int depth[maxn+5],now[maxn+5];
	inline bool bfs(){
		memcpy(now,head,sizeof(now));
		memset(depth,0,sizeof(depth));
		queue<int>q;
		q.emplace(S),depth[S]=1;
		while(q.size()){
			int h=q.front();q.pop();
			for(int i=head[h];i;i=edge[i].nxt){
				int v=edge[i].to;
				if(depth[v]||!edge[i].val)continue;
				depth[v]=depth[h]+1,q.emplace(v);
				if(v==T)return 1;
			}
		}return 0;
	}
	int dfs(int id,int flow){
		if(id==T||!flow)return flow;
		int tot=0;
		for(int &i=now[id];i;i=edge[i].nxt){
			int v=edge[i].to;
			if(depth[v]!=depth[id]+1||!edge[i].val)continue;
			int res=dfs(v,min(flow,edge[i].val));
			edge[i].val-=res,edge[i^1].val+=res;
			tot+=res,flow-=res;
		}return tot;
	}
	inline int Dinic(){
		int res=0;
		while(bfs())res+=dfs(S,inf);
		return res;
	}
}using namespace min_cut;
int main(){
	scanf("%d",&n),N=p(n,n);
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++){
		if(s[i][j]=='B')((i+j)&1)?exadd(S,p(i,j),inf):exadd(p(i,j),T,inf);
		if(s[i][j]=='W')((i+j)&1)?exadd(p(i,j),T,inf):exadd(S,p(i,j),inf);
		if(i<n){
			++N,exadd(S,N,1);
			exadd(N,p(i,j),inf),exadd(N,p(i+1,j),inf);
			++N,exadd(N,T,1);
			exadd(p(i,j),N,inf),exadd(p(i+1,j),N,inf);
		}
		if(j<n){
			++N,exadd(S,N,1);
			exadd(N,p(i,j),inf),exadd(N,p(i,j+1),inf);
			++N,exadd(N,T,1);
			exadd(p(i,j),N,inf),exadd(p(i,j+1),N,inf);
		}
	}printf("%d",N-p(n,n)-Dinic());return 0;
}