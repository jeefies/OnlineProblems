#include <cstdio>

int main(){
    for (int i=192;i<=329;i++){//枚举A最多329
        int p=i,j=i<<1,k=i*3,t=0;
        while (p) t|=1<<p%10-1,p/=10;//分解，第p%10位为1
        while (j) t|=1<<j%10-1,j/=10;//以此类推
        while (k) t|=1<<k%10-1,k/=10;
        if ((t&511)==511) printf("%d %d %d\n",i,i<<1,i*3);//也就是都匹配到了
    }
    return 0;
}
