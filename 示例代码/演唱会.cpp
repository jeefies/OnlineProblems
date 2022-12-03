#include<bits/stdc++.h>
using namespace std;
int f[205],t[205],r[205],n;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>t[i];
	for(int i=1;i<=n-1;i++)cin>>r[i];
	f[1]=t[1];f[2]=r[1];	
	for(int i=3;i<=n;i++)
	  f[i]=min(f[i-1]+t[i],f[i-2]+r[i-1]);
	cout<<f[n];
	return 0;
}
/*
5
2 3 5 4 6
4 6 7 8
*/ 
