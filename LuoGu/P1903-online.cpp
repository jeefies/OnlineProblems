#include<bits/stdc++.h>
using namespace std;
#define N 233333
#define M 1111111

int sum, cnt[M], col[N], ans[N], qc = 0, mc = 0, n, m, sz;

struct ques
{
	int l, r, t, id;
} qs[N], ms[N];//两个数组分解记录每一个询问以及修改的状态

inline void add(int x)
{
	sum += !cnt[x]++;
}

inline void del(int x)
{
	sum -= !--cnt[x];
}

//add与del是普通莫队原有操作

inline void fix(int l, int r, int t)//fix是对于时间上的变化所造成变化的维护
{
	int x = ms[t].l, &c = ms[t].r;
	if (l <= x && x <= r)
	{
		del(col[x]), add(c);
	} //如果这个修改的值在[l,r]区间内，则其变化将对答案造成影响
	swap(col[x], c);//因为修改后的下一次操作一定相反(即修改该位置->还原该位置->修改该位置...如此循环)，所以只需交换即可，而不需要写两个函数
}

bool cmp (const ques &a, const ques &b)
{
	return a.l / sz == b.l / sz ? a.r / sz == b.r / sz ? a.t < b.t : a.r < b.r : a.l < b.l;
}//魔改版cmp，需要判断t的大小

int main()
{
	cin >> n >> m; sz = pow(n, 0.666);//设置块的大小
	for (int i = 1; i <= n; i++) scanf("%d", col + i);
	for (int i = 1; i <= m; i++)
	{
		char op[5];
		int l, r;
		scanf("%s%d%d", op, &l, &r);
		if (op[0] == 'Q') 
			// ++qc, qs[qc].id = qc, qs[qc].l = l, qs[qc].r = r, qs[qc].t = mc;//询问的时间即为该询问以前已经执行了多少次修改操作
			++qc, qs[qc] = {l, r, mc, qc};
		else 
			// ms[++mc].l = l, ms[mc].r = r;
			ms[++mc] = {l, r, 0, 0};
	}
	sort(qs + 1, qs + qc + 1, cmp);
	int l = 1, r = 0, t = 0;
	for (int i = 1; i <= qc; i++)
	{
		while (l > qs[i].l) add(col[--l]);
		while (l < qs[i].l) del(col[l++]);
		while (r > qs[i].r) del(col[r--]);
		while (r < qs[i].r) add(col[++r]);
		while (t < qs[i].t) fix(l, r, ++t);
		while (t > qs[i].t) fix(l, r, t--);//增加t轴上的移动
		ans[qs[i].id] = sum;//得到最终答案
	}
	for (int i = 1; i <= qc; i++) printf("%d\n", ans[i]);
	return 0;//结束&AC!
}
