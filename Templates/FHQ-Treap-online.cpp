#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int s = 0,w = 1;char ch = getchar();
    while(ch<'0'||ch>'9'){if(ch == '-')w=-1;ch = getchar();}
    while(ch>='0'&&ch<='9'){s = (s << 1) + (s << 3) + ch - '0';ch = getchar();}
    return s * w;
}
int rt,cnt;
struct Tree
{
    int l,r,val,key,siz;
}t[110000];
inline int MakeNew(int val)
{
    t[++cnt].val = val,t[cnt].key = rand() * rand(),t[cnt].siz = 1;
    return cnt;
}
inline void Split(int now,int w,int &u,int &v)
{
    if(!now) u = v = 0;
    else
    {
        if(t[now].val <= w) u = now,Split(t[now].r,w,t[now].r,v);
        else v = now,Split(t[now].l,w,u,t[now].l);
        t[now].siz = t[t[now].r].siz + t[t[now].l].siz + 1;
    }
}
inline int Merge(int u,int v)
{
    if(!u||!v) return u + v;
    if(t[u].key < t[v].key)
    {
        t[u].r = Merge(t[u].r,v);
        t[u].siz = t[t[u].r].siz + t[t[u].l].siz + 1;
        return u;
    }
    else 
    {
        t[v].l = Merge(u,t[v].l);
        t[v].siz = t[t[v].r].siz + t[t[v].l].siz + 1;
        return v;
    }
}
inline int Kth(int now,int sum)
{
    while(1)
        if(sum <= t[t[now].l].siz) now = t[now].l;
        else if(sum == t[t[now].l].siz + 1) return now;
        else sum-=t[t[now].l].siz + 1,now = t[now].r;
}
int main()
{
	freopen("P3369_7.in", "r", stdin);
	freopen("P3369.ans", "w", stdout);
    int n = read(),x,y,z,opt,a;
    srand(20040328);
    while(n--)
    {
        opt = read();a = read();
        if(opt == 1)
        {
            Split(rt,a,x,y);
            rt = Merge(Merge(x,MakeNew(a)),y);
        }
        else if(opt == 2)
        {
            Split(rt,a,x,z);
            Split(x,a-1,x,y);
            y = Merge(t[y].l,t[y].r);
            rt = Merge(Merge(x,y),z);
        }
        else if(opt == 3)
        {
            Split(rt,a-1,x,y);
            printf("%d\n",t[x].siz + 1);
            rt = Merge(x,y);
        }
        else if(opt == 4) printf("%d\n",t[Kth(rt,a)].val);
        else if(opt == 5)
        {
            Split(rt,a-1,x,y);
            printf("%d\n",t[Kth(x,t[x].siz)].val);
            rt = Merge(x,y);
        }
        else if(opt == 6)
        {
            Split(rt,a,x,y);
            printf("%d\n",t[Kth(y,1)].val);
            rt = Merge(x,y);
        }
    }
    return 0;
}