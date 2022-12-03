#include<bits/stdc++.h>
using namespace std;
int mp[102][102],f[102],n,m;
int main(){
	cin>>n>>m;
	memset(mp,0,sizeof(mp));//邻接矩阵存图，先初始化为0 
	for(int i=1;i<=m;i++){
		int u,v,x;
		cin>>u>>v>>x;
		mp[u][v]=x;
	}
	f[n]=0;//表示从终点到n点的最短路值 
	for(int i=n-1;i>=1;i--){
		f[i]=0x3f3f3f3f;
		for(int j=i+1;j<=n;j++)
		  if(mp[i][j]!=0&&f[i]>f[j]+mp[i][j])
		  	f[i]=f[j]+mp[i][j];  	   
	}
	cout<<f[1];
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
