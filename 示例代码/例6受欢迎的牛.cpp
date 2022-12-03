#include<bits/stdc++.h>
#define maxN 10005
using namespace std;
struct NODE{
    int next,to;
}edge[5*maxN];
int head[maxN],dfn[maxN],low[maxN];
int du[maxN],id[maxN],all[maxN];//du����������ȣ�id��¼����������ĳ���б�ŵ���ͨ������all��¼������ͨ�����Ķ������� 
bool ins[maxN];
int cnt=0,tot=0,scc=0,n,m;
stack<int>s;
void add(int x,int y){
    cnt++;
    edge[cnt].to=y;
    edge[cnt].next=head[x];
    head[x]=cnt;
}
void read(int &xx){
    int x=0,f=1;char ch;
    for(ch=getchar();(ch<'0'||ch>'9')&&ch!='-';ch=getchar());
    if(ch=='-'){f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    xx=x*f;
}
void tarjan(int u){
    dfn[u]=low[u]=++tot;
    s.push(u);ins[u]=true;
    for(int i=head[u];i;i=edge[i].next){
        int v=edge[i].to;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(ins[v])low[u]=min(low[u],dfn[v]);
    }
    int k;
    if(low[u]==dfn[u]){
        ++scc;
        do{
            k=s.top();s.pop();
            ins[k]=false;
            id[k]=scc;all[scc]++;//��ǿ��ͨ������ţ���ͳ��ĳ��ǿ��ͨ�����Ķ������ 
        }while(u!=k);
    }
}
int main(){
    read(n);read(m);
    for(int i=1;i<=m;i++){
    	int u,v;
        read(u);read(v);
        add(u,v);
    }
    memset(all,0,sizeof(all)); 
    for(int i=1;i<=n;i++)
        if(!dfn[i])tarjan(i);
    for(int u=1;u<=n;u++){
        for(int i=head[u];i;i=edge[i].next){
            int v=edge[i].to;
            if(id[u]!=id[v])
                du[id[u]]++;//ͳ�Ƹ���ǿ��ͨ�����ĳ���           
        }
    }
    int b=0;//��� 
    for(int i=1;i<=scc;i++)
        if(!du[i]){
            if(b){cout<<"0";return 0;}//���γ��ֳ���Ϊ0��ʾ�޽� 
            b=i;//��¼����Ϊ���ǿ��ͨ���������
        }
    printf("%d\n",all[b]);
    return 0;
}
/*
3 3
1 2
2 1
2 3
*/
