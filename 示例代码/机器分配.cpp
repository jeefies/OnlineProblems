#include<bits/stdc++.h>
using namespace std;
const int maxN=205;
int n,m,f[maxN][maxN],value[maxN][maxN],maxl;
void print(int i,int j){ 
    if(i==0)return;
    for(int k=0;k<=j;k++)
       if(maxl==f[i-1][k]+value[i][j-k]){
           maxl=f[i-1][k];
           print(i-1,k);
           printf("%d %d\n",i,j-k);//倒序输出 
           break;
       }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
       for(int j=1;j<=m;j++)
          scanf("%d",&value[i][j]);
    for(int i=1;i<=n;i++)
       for(int j=1;j<=m;j++){
           maxl=0;
           for(int k=0;k<=j;k++)
              if(f[i-1][k]+value[i][j-k]>maxl)
                  maxl=f[i-1][k]+value[i][j-k];
           f[i][j]=maxl;
       }
    printf("%d\n",f[n][m]);
    print(n,m);//输出分配方案 
    return 0;
}
/*
3 3
30 40 50
20 30 50
20 25 30
*/
