#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<queue>
#include<vector>
#include<map>
using namespace std;
#define llg long long
#define maxn 1000100
#define V1 (llg)(999999751)
#define V2 (llg)(299999827)
#define V3 (llg)(100000007)
#define md (llg)(89999794200117649)
#define mdd (llg)(999999786000011449)
#define yyj(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout);

inline llg getint()
{
    llg w=0,q=0; char c=getchar();
    while((c<'0' || c>'9') && c!='-') c=getchar();
    if (c=='-')  q=1, c=getchar(); while (c>='0' && c<='9') w=w*10+c-'0', c=getchar();
    return q ? -w : w;
}

unsigned long long hal[maxn],har[maxn],Har[maxn],Hal[maxn];
llg val[maxn],n,ans,he[maxn],lson[maxn],rson[maxn];

void dfs(llg x,llg fa)
{
	if (lson[x]) dfs(lson[x],x);
	if (rson[x]) dfs(rson[x],x);
	he[x]=he[lson[x]]+he[rson[x]]+1;
	if (he[lson[x]]==he[rson[x]] && hal[lson[x]]==har[rson[x]] &&  Hal[lson[x]]==Har[rson[x]])
		{
			ans=max(ans,he[x]);
		}
	hal[x]=hal[lson[x]]*V1+val[x]*V2+hal[rson[x]]*V3;
	Hal[x]=Hal[lson[x]]*V1+val[x]*V2+Hal[rson[x]]*V3;
	hal[x]%=md;
	Hal[x]%=mdd;
	har[x]=har[rson[x]]*V1+val[x]*V2+har[lson[x]]*V3;
	Har[x]=Har[rson[x]]*V1+val[x]*V2+Har[lson[x]]*V3;
	har[x]%=md;
	Har[x]%=mdd;
}

int main()
{
    freopen("P5018_test.in", "r", stdin);

	// yyj("D");
	cin>>n;
	for (llg i=1;i<=n;i++) val[i]=getint();
	for (llg i=1;i<=n;i++)
		{
			llg x=getint(),y=getint();
			if (x!=-1) lson[i]=x;
			if (y!=-1) rson[i]=y;
		}
	dfs(1,-1);
	cout<<ans<<endl;
	return 0;
}
