#include<bits/stdc++.h>
using namespace std;
const int maxN=102;
int n,a[maxN][maxN];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
	 for(int j=1;j<=i;j++)
	  	scanf("%d",&a[i][j]);
	for(int i=n-1;i>=1;i--)
	 for(int j=1;j<=i;j++)
	    a[i][j]=max(a[i+1][j],a[i+1][j+1])+a[i][j];
   	cout<<a[1][1];
	return 0;
	      
}
/*
5
7
3 8
8 1 0 
2 7 4 4
4 5 2 6 5
*/
