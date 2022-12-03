#include<bits/stdc++.h>
using namespace std;
const int maxN=10005;
int n,k,q=1;
int b[maxN],f[maxN];//设f[i]表示1到i个时间最大空闲值 
struct node{
   int p,t;
}a[maxN];
bool cmp(node a,node b){ 
    return a.p>b.p; //逆推，所以从大到小
}
int main(){
	cin>>n>>k;
	memset(b,0,sizeof(b));
	memset(f,0,sizeof(f));
	for(int i=1;i<=k;i++){
		scanf("%d%d",&a[i].p,&a[i].t);
		b[a[i].p]++;
	}
    sort(a+1,a+k+1,cmp);
    //f[n+1]=0;
	for(int i=n;i>=1;i--)
		if(b[i]==0)f[i]=f[i+1]+1;
		else{
			for(int j=1;j<=b[i];j++){
				f[i]=max(f[i],f[i+a[q].t]);
				q++;
			}
		}
	printf("%d",f[1]);
	return 0;
}
/*
15 6
1 2
1 6
4 11
8 5
8 1
11 5
*/
