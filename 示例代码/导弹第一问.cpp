#include<bits/stdc++.h>
using namespace std;
int a[3002],f[3002];
int main(){
	int n=0,ans=0;
	while(cin>>a[++n]);
	n--;
	for(int i=n;i>=1;i--){
		f[i]=1;
		for(int j=i+1;j<=n;j++)
		  if(a[i]>=a[j]&&f[i]<f[j]+1) f[i]=f[j]+1;
		ans=max(f[i],ans);
	}
	cout<<ans;
	return 0;
}
/*389 207 155 300 299 170 158 65*/
