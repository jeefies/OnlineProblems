#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
int a[100005];
struct node{
    int b,next,v;
}st[1000005],nd[1000005];
int minl[100005],maxl[100005];
int n,m;
int head1[100005],head2[100005];
int now1,now2;
int vis1[100005],vis2[100005];
void add(int x,int y,int z){
    now1++;
    st[now1].b=y;
    st[now1].v=z;
    st[now1].next=head1[x];
    head1[x]=now1;
}
void add2(int x,int y,int z){
    now2++;
    nd[now2].b=y;
    nd[now2].v=z;
    nd[now2].next=head2[x];
    head2[x]=now2;
}
queue<int>q1;
queue<int>q2;
void spfa1(){
    for(int i=1;i<=n;i++)
      minl[i]=7777;                                 
    q1.push(1);              //初始化借鉴题解
    vis1[1]=1;
    while(!q1.empty()){
        int t=q1.front();
        q1.pop();
        vis1[t]=0;
        for(int i=head1[t];i!=0;i=st[i].next){
            int b=st[i].b;    
            if(minl[b]>min(minl[t],st[i].v)){//是在三者中找最小值，一定要把判断打在外面不然形成环spfa会卡住 
               minl[b]=min(minl[t],st[i].v);    
               if(vis1[b]==0){
                   q1.push(b); 
                   vis1[b]=1;
               }                
            }
        }
    }
}
void spfa2(){
    for(int i=1;i<=n;i++)
       maxl[i]=0;
    q2.push(n);
    vis2[n]=1;
    while(!q2.empty()){
        int t=q2.front();
        q2.pop();
        vis2[t]=0;
        for(int i=head2[t];i!=0;i=nd[i].next){
            int b=nd[i].b;
            if(maxl[b]<max(maxl[t],nd[i].v)){
                maxl[b]=max(maxl[t],nd[i].v);
                if(vis2[b]==0){
                    q2.push(b);
                    vis2[b]=1; 
                }
            }
        }
    } 
}
int main(){
    scanf("%d%d",&n,&m);
    
    for(int i=1;i<=n;i++)
      scanf("%d",&a[i]);
    for(int i=1;i<=m;i++){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        if(z==2){
            add(x,y,a[y]);
            add(y,x,a[x]);
            add2(x,y,a[y]);
            add2(y,x,a[x]);            
        }
        else{
            add2(y,x,a[x]);
            add(x,y,a[y]);
        }
    }
    spfa1();
    spfa2();
	for (int i = 1; i <= n; i++) printf("%d ", maxl[i]); putchar('\n');
    for (int i = 1; i <= n; i++) printf("%d ", minl[i]); putchar('\n');
    int ans=0;
    for(int i=1;i<=n;i++){
        ans=max(ans,maxl[i]-minl[i]);
    }
    printf("%d",ans);
    return 0;
}

