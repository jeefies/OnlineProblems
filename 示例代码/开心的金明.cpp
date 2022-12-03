#include<bits/stdc++.h>
using namespace std;
int f[30005],n,m;
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		for(int j=n;j>=x;j--)
		  f[j]=max(f[j],f[j-x]+x*y);
	}
	cout<<f[n];
	return 0;
} 
