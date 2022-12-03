#include <bits/stdc++.h>
using namespace std;
const int maxN=1e5+5;
const int maxM=5e5+5;
vector<int>g1[maxN],g2[maxN],d;//g1存原图，g2存反图，d记录对原图的节点访问退出时的顺序 
bool vis[maxN];
int t=0,a[maxM],b[maxM],cmp[maxN],cnt=0,rd[maxN];//a存边的起点，b存边的终点，cmp存结点的连通分量编号 
int n,m;
void dfs(int x){
	vis[x]=true;
	for(int i=0;i<g1[x].size();i++){
		int k=g1[x][i];
		if(!vis[k])dfs(k);		
	}
	d.push_back(x);
}
void dfs2(int x,int j){
	cmp[x]=j;vis[x]=true;
	for(int i=0;i<g2[x].size();i++){
		int k=g2[x][i];
		if(!vis[k])dfs2(k,j);
	}
}
void kosaraju(){
	memset(vis,false,sizeof(vis));
	for(int i=1;i<=n;i++)
		if(!vis[i]) dfs(i);
    memset(vis,false,sizeof(vis));
	for(int i=d.size()-1;i>=0;i--)
		if(!vis[d[i]]){
			t++;
			dfs2(d[i],t);
		}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		if(u==v)continue;
		a[++cnt]=u;b[cnt]=v;
		g1[u].push_back(v);
		g2[v].push_back(u);
	}
	kosaraju();
	for(int i=1;i<=cnt;i++){//缩点并计算各个强连通分量的入度 
		int p=a[i],q=b[i];
		if(cmp[p]!=cmp[q])rd[cmp[q]]++;
	}
	int ans=0;
	for(int i=1;i<=t;i++){//统计缩点后的DAG图中入度为0的点
		if(!rd[i]) ans++;
	}
	printf("%d\n",ans);
	return 0;
}
/*
5 4
1 2
2 1
2 3
5 1
*/
