#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

int read() {
	static LL x;
	scanf("%lld", &x);
	return x;
}

LL c[2002][2002];

inline void build()//记得加入main函数，数组范围要开够，我就是在此RE。
{
  c[0][0]=1;
  c[1][0]=c[1][1]=1;//如上初始化，绝对绝对不能忘记或错，结合常识。
  for(int i=2;i<=2000;i++)
  {
    c[i][0]=1;
    for(int j=1;j<=2000;j++)//这不是此方法能承受的最大范围，打出题目要求的即可。
      c[i][j]=c[i-1][j-1]+c[i-1][j];//递推公式。
  }
}
int t, k, n, m;
inline void solve()
{
  build();
  t=read(),k=read();
  while(t--)
  {
    LL ans=0;
    n=read(),m=read();
    for(int i=0;i<=n;i++)
      for(int j=0;j<=min(i,m);j++)
        if(c[i][j]%k==0) {
        	printf("C(%d, %d) is ok\n", i, j);
        	ans++;
		}
    printf("%lld\n",ans);
  }
}

int main() {
	solve();
}
