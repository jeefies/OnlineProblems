#include <bits/stdc++.h>
using namespace std;  
const int maxN=205;
int n,mp[maxN][maxN],f[maxN],ans=0;//mp[i][j]表示i愿意给j拷贝，f[i]表示i的父亲
int main(){  
    cin >> n;
    memset(mp,0,sizeof(mp));
    int x;
    for(int i=1;i<=n;i++)  
        while(scanf("%d",&x)&&x)
            mp[i][x]=1; 
    for(int k=1;k<=n;k++) //Floyed判定i到j是否有路径 
        for(int i=1;i<=n;i++)  
            for(int j=1;j<=n;j++)  
                if(mp[i][k]&&mp[k][j])  
                    mp[i][j]=1;//如果i愿意给k，而k又愿意给j，就相当于第i个人愿意给第j个人
    for(int i=1;i<=n;i++)  f[i]=i;//并查集，初始化每个人的父亲节点就是自己
    for(int i=1;i<=n;i++)  
        for(int j=1;j<=n;j++)  
            if(mp[i][j]) f[j]=f[i];//合并，如果i愿意给j，那么i的父亲就是j的父亲
    for(int i=1;i<=n;i++)  
        if(f[i]==i) ans++;  //如果i的父亲节点就是自己，则加1
    cout<<ans;  
    return 0;  
} 
/*
6
2 4 3 0
4 5 0
0
0
1 0
0
output:2
*/ 
