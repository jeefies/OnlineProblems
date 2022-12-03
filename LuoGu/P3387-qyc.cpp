#include<cstdio>
#include<algorithm>
using namespace std;
int v[105],w[105],z[105],top,n,m,ti=0,dfn[105],low[105],head[105];
struct sd{
	int next,to;
}edge[10005];
int a,b,qlt[105][105],num[105];
void tarjan(int x)
{
	printf("Tarjan in %d\n", x);
	dfn[x]=low[x]=++ti;
	z[++top]=x,v[x]=1;
	for(int i=head[x];i;i=edge[i].next)
	{
		int y = edge[i].to;
		if(!dfn[y])
		{
			tarjan(y);
			low[x]=min(low[x],low[y]);
		} else if(v[y]&&dfn[y]<low[x]) {
			low[x]=dfn[y];
		}
	}
	if(low[x]==dfn[x])
	{
		printf("Add a at %d\n", x);
		a++;
		do {
			qlt[a][++num[a]] = z[top], v[z[top]] = 0;
			printf("\tGroup %d add %d in (at %d)\n", a, z[top], num[a]);
		} while (x != z[top--]);
	}
	printf("Tarjan out %d\n", x);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		edge[i].to=b,edge[i].next=head[a],head[a]=i;
	}
	a=0;
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i);
	for(int i=1;i<=a;i++)
	{
		printf("Group %d (tot %d): ", i, num[i]);
		for(int j=1;j<=num[i];j++)
		{
			printf("%d ",qlt[i][j]);
		}
		printf("\n");
	}
	return 0;
}
/*
5 5
1 2 3 4 5
1 3
3 2
2 1
1 4
5 4
*/