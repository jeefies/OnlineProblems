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
    Edge(int to,int f,int next):to(to),f(f),next(next){}//û���˷������·����ע��ǰ���ͺ��䶼���������ڵ���qaq
} ; vector <int> q, H, Extra, Set[MAXN], cnt ; List Gap[MAXN] ;//list�����ǿ죨
//q:���У�H:�߶ȣ�Extra��ÿ����ĳ�������Set:�������Ǹ������HLPP��Ķѣ��߶�����һά
int Ans, N, M, S, T, max_H, now_H ; vector <Edge> E[MAXN] ; /*vector��ߣ���˵��죩*/vector<List::iterator> Era_pos ; //������λ+ɾ��

inline void eggs() { ;}//for free~
inline int my_min(int a, int b){return a & ((a - b) >> 31) | b & ( ~ (a - b) >> 31) ;}//�ڿƼ�
inline void Add(int f, int v, int u){ E[u].push_back(Edge(v, f, E[v].size())), E[v].push_back(Edge(u, 0, E[u].size() - 1)) ; }
inline int qr(){ rr int k = 0 ; char c = gc() ; while (!isdigit(c)) c = gc() ;while (isdigit(c)) k = (k << 1) + (k << 3) + c - 48, c = gc() ; return k ; }

inline void Init_label(){//�ȼ���һ��ʼ���Ǹ�BFS��ִֻ��һ��
    rr int i, h = 0, t = 0 ;q.clear(), q.resize(N) ; 
    H.assign(N + 1, N + 1) ; H[T] = 0 ; q[t ++] = T ;//��T���߶�С�ģ���ǰ���
    while (h < t){//���С���BFS��������Ϥ�������á���
        rr int now = q[h] ; ++ h ;
        for (vector <Edge> :: Iter k = E[now].begin() ; k != E[now].end() ; ++ k)
            if (H[k->to] == N + 1 && E[k->to][k->next].f) H[k->to] = H[now] + 1, ++ cnt[H[k->to]], q[t ++] = k->to ;
    }
    rep(i, 0, N + 1) Set[i].clear(), Gap[i].clear() ;//�������һ�±ȽϺð�
    rep(i, 0, N) 
        if (H[i]  <N + 1)  
            Era_pos[i] = Gap[H[i]].insert(Gap[H[i]].BG, i), //����insert�����ķ���ֵ��һ��ָ��qaq
            (Extra[i]>0) ? Set[H[i]].push_back(i) : eggs() ;//����ʵ���eggs������Ϊ����Ŀ�����":"����������Ҫ��ͬ��
    max_H = now_H = H[q[-- t]] ; //���£�BFS�����ʣ����һ��Ԫ��һ���߶���󣨳���Դ�㣩
}
inline void Push(int x, Edge &e){//����д������push����������ܷ��㣿
    rr int now_flow = min(Extra[x], e.f) ;
    Extra[x] -= now_flow, e.f -= now_flow, Extra[e.to] += now_flow, E[e.to][e.next].f += now_flow ;
    if (Extra[e.to] > 0 && Extra[e.to] <= now_flow) Set[H[e.to]].push_back(e.to) ;  // push it into "heap"
}
inline void _Push(int x){
    rr int i, x_h = N, t = H[x] ; 
    for (vector <Edge> :: Iter k = E[x].BG ; k != E[x].end() ; ++ k)
        if (k->f > 0)//���������
            if (H[k->to] == H[x] - 1) { Push(x, *k) ; if (!Extra[x]) return ;} else x_h = min(x_h, H[k->to] + 1) ;
    if (cnt[H[x]] <= 1){//������ֶϲ���
        for(i = t ; i <= max_H ; Gap[i].clear(), ++ i)//���gap��for�϶���O(n)����
            for(List::Iter k = Gap[i].BG ; k != Gap[i].end() ; ++ k) cnt[H[*k]] --, H[*k] = N ; 
        max_H = t - 1 ; /*�ϲ����ϵĸ߶ȶ�û����*/return ;
    }
    -- cnt[t], Era_pos[x] = Gap[t].erase(Era_pos[x]) ; H[x] = x_h ; if (x_h == N) return ; //������ǩ������Ϊ��ǰ��ɾ��ԭ���ĸ߶�
    ++ cnt[x_h], Era_pos[x] = Gap[x_h].insert(Gap[x_h].begin(), x), max_H = max(now_H = x_h, max_H), Set[x_h].push_back(x) ;//�����µĸ߶�
}
inline int HLPP(){
    rr int i, now ; H.assign(N, 0) ; H[S] = N ; Era_pos.resize(N)  ;
    rep(i, 0, N - 1) if (i != S) Era_pos[i] = Gap[H[i]].insert(Gap[H[i]].BG, i) ; 
    cnt.assign(N, 0), cnt[0] = N - 1 ; Extra.assign(N, 0), Extra[S] = INF, Extra[T] =- INF ;
    rep(i, 0, E[S].size() - 1) Push(S, E[S][i]) ;  //����Դ��Ҫ�����ó������ͣ���ΪԴ������ʱ�߶Ȳ��Ҫ=1.
    Init_label() ; //��ʼ����BFS��
    while (now_H >= 0) //��ʽ��ʼHLPP����Ŀ��
        if (Set[now_H].empty()) now_H -- ; //�߶ȵݼ���ʵ��һ���ѵ�Ч��
        else now = Set[now_H].back(), Set[now_H].pop_back(), _Push(now) ;
    return Extra[T] + INF ;
}
int main(){
    N = qr(); rr int i ;//�����++N��Ϊ���պ�ò���qaq
    rep(i, 1, M) Add(qr(), qr(), qr()) ; ++ N, Ans = HLPP() ; cout << Ans << endl ; return 0 ; 
}
