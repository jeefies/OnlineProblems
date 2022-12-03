#include<bits/stdc++.h>
using namespace std;
int mp[102][102],f[102],g[102];
int main(){
	int n,m,u,v,x;
	cin>>n>>m;
	memset(mp,0,sizeof(mp));
	for(int i=1;i<=m;i++){
		cin>>u>>v>>x;
		mp[u][v]=x;
	}
	f[n]=0;g[n]=0;
	for(int i=n-1;i>=1;i--){
		f[i]=0x3f3f3f3f;
		for(int j=i+1;j<=n;j++)
		  if(mp[i][j]!=0&&f[i]>f[j]+mp[i][j]){
		  	f[i]=f[j]+mp[i][j];//计算出的值小于当前保存的g[i]，则更新g[i]
		  	g[i]=j;//新的g[i]值是经过点j产生的, 因此点i的上一点是点j 
		  }		   
	}
	int i=1; 
	cout<<1;//输出最优解的路径
	i=g[i];
	while(i){
		cout<<"->"<<i;
		i=g[i];		
	}
	cout<<endl<<f[1];
	return 0;
} 
/* 
7 9
1 2 5
1 3 2
2 4 3
2 5 2
3 5 7
3 6 4
4 7 4
5 7 3
6 7 5
*/ 
