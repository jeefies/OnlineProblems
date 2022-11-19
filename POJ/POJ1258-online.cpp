#include <iostream>
#include <queue>
#include <stack>
#include <cstring>
#include <string>
#include <climits>
#include <utility>

const int N = 150, INF = 0x3F3F3F3F;

using namespace std;

int mp[N][N], size = 0;
int n;

int prim()        //普利姆函数
{
    static int dis[N]; memset(dis, INF, sizeof(dis));  //初始化dis数组为无穷大
    static int inc[N]; memset(inc, 0, sizeof(inc));  //初始化inc数组，0表示此点未被纳入
    
    int sum = 0;    //最小生成树权值和
    /*这里随机选取了1号点为初始时被纳入的顶点*/
    for(int i = 1; i <= n; i++)
        dis[i] = mp[1][i];     //与1号点与其他点的权值存入dis数组
    dis[1] = 0, inc[1] = 1;

    for(int i = 1; i < n; i++){         //除去初始时随机纳入的点还有n-1个点应被纳入
    	int mpo, min;
        mpo = min = INF;            //初始为无穷大表示两点间无通路
        for(int j = 1; j <= n; j++){    //遍历
            if(inc[j] == 0 && dis[j] < min){
                mpo = j, min = dis[j];
            }
        }
        if(mpo == INF) return -1;
        
        sum += min;     //将找到的点纳入并标记
        inc[mpo] = 1;
        
        for(int j = 1; j <= n; j++){
            if(!inc[j] && dis[j] > mp[mpo][j])
                dis[j] = mp[mpo][j];
        }
    }
    
	return sum;
}
int main(void)
{
	/*
    int i, j, k;
    while(scanf("%d", &n) != EOF){
        for(i = 1; i <= n; i++)
            for(j = 1; j <= n; j++)
                scanf("%d", &mp[i][j]);  //输入i和j之间的距离
        if((k = prim()) != -1) //调用prim函数
            printf("%d\n", k);
        else
            printf("烫烫烫烫烫烫烫烫烫烫烫烫烫烫烫烫烫烫烫烫\n");
    }
    */
    
    while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++)
				scanf("%d", mp[i] + j);
		}
		printf("%d\n", prim());
	}
    
	return 0;
}


