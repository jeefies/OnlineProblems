#include<bits/stdc++.h>
using namespace std;
int c[27],w[27],f[30002]; 
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>c[i]<<w[i];
	memset(f,0,sizeof(f));
	for(int i=1;i<=m;i++)
	for(int j=0;j<=n;j++)
		if(j>=c[i])f[i][j]=max(f[i-1][j],f[i-1][j-c[i]]+c[i]*w[i]);
		else f[i][j]=f[i-1][j];
	cout<<f[m][n];
	return 0;
}

