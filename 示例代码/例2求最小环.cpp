#include<bits/stdc++.h>
using namespace std;
#define maxN 105
#define INF 0x7ffffff
int mp[maxN][maxN],dist[maxN][maxN],n,m,minc;
void floyd(){
    minc=INF;
    for(int k=1; k<=n; k++){   
        for(int i=1; i<=k; i++)//KΪ�������㡢����ͼ����ɻ�(��k��������ص�k��)
            for(int j=i+1; j<=k; j++)
                minc=min(minc,dist[i][j]+mp[i][k]+mp[k][j]);
        for(int i=1; i<=n; i++) //floyd�㷨��������������·
            for(int j=1; j<=n; j++)
                if(dist[i][j]>dist[i][k]+dist[k][j])
                    dist[i][j]=dist[i][k]+dist[k][j];
    }
}
void init(){ //��ʼ��������ͼ�����ܳɻ� 
    for(int i=0; i<maxN; i++)
        for(int j=0; j<maxN; j++){
            mp[i][j]=INF;
            dist[i][j]=INF;
        }
}
int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        for(int i=1; i<=m; i++){
        	int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            if(w<mp[u][v]){
                mp[u][v]=mp[v][u]=w;
                dist[u][v]=dist[v][u]=w;
            }
        }
        floyd();
        if(minc<INF)
            printf("%d\n",minc);
        else
            printf("It's impossible.\n");
    }
    return 0;
}
/*
3 3
1 2 1
2 3 1
1 3 1
3 3
1 2 1
1 2 3
2 3 1
*/
