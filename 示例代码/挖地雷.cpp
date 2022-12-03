#include<bits/stdc++.h>
using namespace std;
int f[205],w[205],m[205][205],father[205],n,mx=0,k;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>w[i];
	for(int i=1;i<=n-1;i++)
		for(int j=i+1;j<=n;j++)
			cin>>m[i][j];
	f[n]=w[n],father[n]=0;
	for(int i=n;i>=1;i--){
		f[i]=w[i];
		for(int j=i+1;j<=n;j++)
		   if(m[i][j]&&f[i]<f[j]+w[i]){
		   	   f[i]=f[j]+w[i];
		   	   father[i]=j;
		   }
	}
	for(int i=1;i<=n;i++)
	   if(f[i]>mx) {
	       mx=f[i];
	       k=i;
	   }
	cout<<k;
	k=father[k];
	while(k!=0){
		cout<<" "<<k;
		k=father[k];
	}
	cout<<endl<<mx;
	return 0;
} 
/*
5
10 8 4 7 6
1 1 1 0
0 0 0
1 1
1
*/ 
