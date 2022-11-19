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

int prim()        //����ķ����
{
    static int dis[N]; memset(dis, INF, sizeof(dis));  //��ʼ��dis����Ϊ�����
    static int inc[N]; memset(inc, 0, sizeof(inc));  //��ʼ��inc���飬0��ʾ�˵�δ������
    
    int sum = 0;    //��С������Ȩֵ��
    /*�������ѡȡ��1�ŵ�Ϊ��ʼʱ������Ķ���*/
    for(int i = 1; i <= n; i++)
        dis[i] = mp[1][i];     //��1�ŵ����������Ȩֵ����dis����
    dis[1] = 0, inc[1] = 1;

    for(int i = 1; i < n; i++){         //��ȥ��ʼʱ�������ĵ㻹��n-1����Ӧ������
    	int mpo, min;
        mpo = min = INF;            //��ʼΪ������ʾ�������ͨ·
        for(int j = 1; j <= n; j++){    //����
            if(inc[j] == 0 && dis[j] < min){
                mpo = j, min = dis[j];
            }
        }
        if(mpo == INF) return -1;
        
        sum += min;     //���ҵ��ĵ����벢���
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
                scanf("%d", &mp[i][j]);  //����i��j֮��ľ���
        if((k = prim()) != -1) //����prim����
            printf("%d\n", k);
        else
            printf("����������������������������������������\n");
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


