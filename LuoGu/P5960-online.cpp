#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int INF = 0x3f;
const int MAX = 1e4 + 5;
const int N = MAX;

int n, m;
int cnt, head[MAX], dis[MAX], vis[MAX], inq[MAX];

struct edge
{
	int to, dis, next;
}edge[MAX];

void add(int u, int v, int w)
{
	++cnt;
	edge[cnt] = {v, w, head[u]};
	head[u] = cnt;
}

bool spfa()
{
	queue <int> q;
	q.push(0);
	dis[0] = 0;
	++inq[0];
	while (!q.empty())
	{
		int cu = q.front();
		q.pop();
		vis[cu] = 0;
		for (int i = head[cu]; i; i = edge[i].next)
		{
			int cv = edge[i].to, cdis = edge[i].dis;
			if (dis[cv] > dis[cu] + cdis)
			{
				dis[cv] = dis[cu] + cdis;
				if (!vis[cv])
				{
					q.push(cv);
					vis[cv] = 1;
					++inq[cv];
					if (inq[cv] > n) //ע��:���ӳ���Դ�����(n+1)����,�жϸ�����������Ϊĳ���㱻�ɳڳ��� n��; 
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

// cprt: comparative
bool spfa(int s, int * cprt) {
	static int in[N]; memset(in, 0, sizeof(in));
	static int it[N]; memset(it, 0, sizeof(it));
	
	queue<int> que;
	cprt[s] = 0; que.push(s);
	
	while (que.size()) {
		int top = que.front(); que.pop();
		in[top] = 0;
		
		if (++it[top] > n) return false;
		
		for (int i = head[top]; i; i = edge[i].next) {
			int to = edge[i].to, w = edge[i].dis;
			if (cprt[to] > w + cprt[top]) {
				cprt[to] = w + cprt[top];
				if (!in[to]) que.push(to), in[to] = true;
			}
		}
	}
	
	return true;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
	{
		add(0, i, 0); //0�ŵ�Ϊ����Դ�㣬��ÿ���������Ҿ����Ϊ 0����ֹ��ͼ����ͨ�����; 
	}
	for (int i = 1; i <= m; ++i)
	{
		int u, v, w;
		scanf("%d%d%d", &v, &u, &w); //Xi - Xj = y -> Xi = Xj + y, j <=> u, i <=> v, ��������v������u; 
		add(u, v, w); //���� 
	}
	memset(dis, INF, sizeof(dis));
	if (!spfa(0, dis))
	{
		printf("NO\n");
	}
	else
	{
		for (int i = 1; i <= n; ++i)
		{
			printf("%d ", dis[i]);
		}	
	}
	return 0;
}
/**************************************************************
    Language: C++
    Result: Accepted
    Time:52 ms
    Memory:896 kb
****************************************************************/
