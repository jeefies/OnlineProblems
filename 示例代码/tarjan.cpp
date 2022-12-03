#include<bits/stdc++.h>
using namespace std;
#define maxN 100005
#define maxM 200005
struct Edge{
  int to,next;
};
int head[maxN],n,m,tot;
struct Edge edge[maxM];
bool vis[maxN];
void add(int x,int y){
   tot++;
   edge[tot].to=y;
   edge[tot].next=head[x];
   head[x]=tot;
}
int dfn[maxN],low[maxN],s[maxN],top=0,index=0,scc=0;
bool ins[maxN];
vector <int> vec[maxN];
void tarjan(int i){    
    dfn[i]=low[i]=++index;//ʱ��� 
	s[++top]=i;   //ѹջ 
	ins[i]=true;  //���ջ��Ԫ�� 
    for(int u=head[i];u;u=edge[u].next){
    	 int j=edge[u].to;
    	 if(!dfn[j]){
    	 	tarjan(j);
    	 	low[i]=min(low[i],low[j]);//ǰ��� 
         }
         else if(ins[j]&&low[i]>dfn[j])
                  low[i]=dfn[j]; //����� 
    }
	if(dfn[i]==low[i]){  //����ǿ��ͨ�����Ķ�Ӧ�����ջ 
		++scc;
		int v;
		do{
			v=s[top--];
			ins[v]=false;
			vec[scc].push_back(v);
		}while(i!=v);
	}       
} 
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++){
       int x,y;
       scanf("%d%d",&x,&y);
       add(x,y);
    } 
    memset(ins,0,sizeof(ins));
    tarjan(1);
    for(int i=1;i<=scc;i++){
    	for(int j = 0;j <vec[i].size();j++)
		    printf("%d ",vec[i][j]);
		printf("\n");
    }         
    return 0;
}
/*
6 8
1 3
3 5
5 6
1 2
3 4
4 1
2 4
4 6
*/
