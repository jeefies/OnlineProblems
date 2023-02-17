//copy from:Orchidany(pks)
// !!!! I just wanna test its time!
#include <bits/stdc++.h>

#define MAXN 10030
#define min my_min
#define BG begin()
#define gc getchar
#define rr register 
#define Iter iterator
#define INF 2147483647
#define rep(i, a, x) for(i = a ; i <= x ; ++ i)

using namespace std ;
typedef list<int> List ; int step;

struct Edge{
    int to, f, next ;
    Edge(int to,int f,int next):to(to),f(f),next(next){}//没有人发现正下方这句注释前半句和后半句都是三个音节的吗qaq
} ; vector <int> q, H, Extra, Set[MAXN], cnt ; List Gap[MAXN] ;//list，就是快（
//q:队列，H:高度，Extra：每个点的超额流，Set:…就是那个经典版HLPP里的堆，高度做第一维
int Ans, N, M, S, T, max_H, now_H ; vector <Edge> E[MAXN] ; /*vector存边（据说会快）*/vector<List::iterator> Era_pos ; //辅助定位+删除

inline void eggs() { ;}//for free~
inline int my_min(int a, int b){return a & ((a - b) >> 31) | b & ( ~ (a - b) >> 31) ;}//黑科技
inline void Add(int f, int v, int u){ E[u].push_back(Edge(v, f, E[v].size())), E[v].push_back(Edge(u, 0, E[u].size() - 1)) ; }
inline int qr(){ rr int k = 0 ; char c = gc() ; while (!isdigit(c)) c = gc() ;while (isdigit(c)) k = (k << 1) + (k << 3) + c - 48, c = gc() ; return k ; }

inline void Init_label(){//等价于一开始的那个BFS，只执行一次
    rr int i, h = 0, t = 0 ;q.clear(), q.resize(N) ; 
    H.assign(N + 1, N + 1) ; H[T] = 0 ; q[t ++] = T ;//从T（高度小的）向前标号
    while (h < t){//队列……BFS……真熟悉啊……嗝……
        rr int now = q[h] ; ++ h ;
        for (vector <Edge> :: Iter k = E[now].begin() ; k != E[now].end() ; ++ k)
            if (H[k->to] == N + 1 && E[k->to][k->next].f) H[k->to] = H[now] + 1, ++ cnt[H[k->to]], q[t ++] = k->to ;
    }
    rep(i, 0, N + 1) Set[i].clear(), Gap[i].clear() ;//还是清空一下比较好吧
    rep(i, 0, N) 
        if (H[i]  <N + 1)  
            Era_pos[i] = Gap[H[i]].insert(Gap[H[i]].BG, i), //疑似insert函数的返回值是一个指针qaq
            (Extra[i]>0) ? Set[H[i]].push_back(i) : eggs() ;//这个彩蛋（eggs）是因为，三目运算符":"两边类型需要形同…
    max_H = now_H = H[q[-- t]] ; //更新，BFS的性质，最后一个元素一定高度最大（除了源点）
}
inline void Push(int x, Edge &e){//单独写出来的push函数，好像很方便？
    rr int now_flow = min(Extra[x], e.f) ;
    Extra[x] -= now_flow, e.f -= now_flow, Extra[e.to] += now_flow, E[e.to][e.next].f += now_flow ;
    if (Extra[e.to] > 0 && Extra[e.to] <= now_flow) Set[H[e.to]].push_back(e.to) ;  // push it into "heap"
}
inline void _Push(int x){
    rr int i, x_h = N, t = H[x] ; 
    for (vector <Edge> :: Iter k = E[x].BG ; k != E[x].end() ; ++ k)
        if (k->f > 0)//如果可以流
            if (H[k->to] == H[x] - 1) { Push(x, *k) ; if (!Extra[x]) return ;} else x_h = min(x_h, H[k->to] + 1) ;
    if (cnt[H[x]] <= 1){//如果出现断层了
        for(i = t ; i <= max_H ; Gap[i].clear(), ++ i)//这个gap的for肯定比O(n)优秀
            for(List::Iter k = Gap[i].BG ; k != Gap[i].end() ; ++ k) cnt[H[*k]] --, H[*k] = N ; 
        max_H = t - 1 ; /*断层以上的高度都没用了*/return ;
    }
    -- cnt[t], Era_pos[x] = Gap[t].erase(Era_pos[x]) ; H[x] = x_h ; if (x_h == N) return ; //重贴标签操作，为当前点删除原来的高度
    ++ cnt[x_h], Era_pos[x] = Gap[x_h].insert(Gap[x_h].begin(), x), max_H = max(now_H = x_h, max_H), Set[x_h].push_back(x) ;//增添新的高度
}
inline int HLPP(){
    rr int i, now ; H.assign(N, 0) ; H[S] = N ; Era_pos.resize(N)  ;
    rep(i, 0, N - 1) if (i != S) Era_pos[i] = Gap[H[i]].insert(Gap[H[i]].BG, i) ; 
    cnt.assign(N, 0), cnt[0] = N - 1 ; Extra.assign(N, 0), Extra[S] = INF, Extra[T] =- INF ;
    rep(i, 0, E[S].size() - 1) Push(S, E[S][i]) ;  //下面源点要单独拿出来推送，因为源点推送时高度差不需要=1.
    Init_label() ; //初始化（BFS）
    while (now_H >= 0) //正式开始HLPP（泪目）
        if (Set[now_H].empty()) now_H -- ; //高度递减，实现一个堆的效果
        else now = Set[now_H].back(), Set[now_H].pop_back(), _Push(now) ;
    return Extra[T] + INF ;
}
int main(){
    N = qr(); rr int i ;//下面的++N是为了日后好操作qaq
    rep(i, 1, M) Add(qr(), qr(), qr()) ; ++ N, Ans = HLPP() ; cout << Ans << endl ; return 0 ; 
}
