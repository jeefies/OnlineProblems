#include <bits/stdc++.h>
using namespace std;  
const int maxN=205;
int n,mp[maxN][maxN],f[maxN],ans=0;//mp[i][j]��ʾiԸ���j������f[i]��ʾi�ĸ���
int main(){  
    cin >> n;
    memset(mp,0,sizeof(mp));
    int x;
    for(int i=1;i<=n;i++)  
        while(scanf("%d",&x)&&x)
            mp[i][x]=1; 
    for(int k=1;k<=n;k++) //Floyed�ж�i��j�Ƿ���·�� 
        for(int i=1;i<=n;i++)  
            for(int j=1;j<=n;j++)  
                if(mp[i][k]&&mp[k][j])  
                    mp[i][j]=1;//���iԸ���k����k��Ը���j�����൱�ڵ�i����Ը�����j����
    for(int i=1;i<=n;i++)  f[i]=i;//���鼯����ʼ��ÿ���˵ĸ��׽ڵ�����Լ�
    for(int i=1;i<=n;i++)  
        for(int j=1;j<=n;j++)  
            if(mp[i][j]) f[j]=f[i];//�ϲ������iԸ���j����ôi�ĸ��׾���j�ĸ���
    for(int i=1;i<=n;i++)  
        if(f[i]==i) ans++;  //���i�ĸ��׽ڵ�����Լ������1
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
