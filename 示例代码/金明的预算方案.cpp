#include<bits/stdc++.h>  
using namespace std;  
const int maxN=32005,maxM=185;
int m,n,mw[maxM],mv[maxM],fw[maxM][3],fv[maxM][3],f[maxN],v,p,q;  
//mw主件价值，mv主件价重积，fw主件对应的附件价值，fv附件价重积，n总钱数，m物品总数   
int main(){  
    cin>>n>>m;  
	memset(fv,0,sizeof(fv));
    for(int i=1;i<=m;i++){  
       cin>>v>>p>>q;  
       if(!q){//如果是主件   
          mv[i]=v;//主件价值   
          mw[i]=v*p;//主件价值与重要度的乘积   
       }  
       else{//如果是附件   
          fv[q][0]++;//记录主件的附件个数   
          fv[q][fv[q][0]]=v;//确定附件一或附件二   
          fw[q][fv[q][0]]=v*p;  
       }  
    }  
    for(int i=1;i<=m;i++)  
    for(int j=n;j>=mv[i];j--){   
        //只要主件 
        f[j]=max(f[j],f[j-mv[i]]+mw[i]);  
        //主件和附件1  
        if(j>=mv[i]+fv[i][1])f[j]=max(f[j],f[j-mv[i]-fv[i][1]]+mw[i]+fw[i][1]);  
        //主件和附件2 
        if(j>=mv[i]+fv[i][2])f[j]=max(f[j],f[j-mv[i]-fv[i][2]]+mw[i]+fw[i][2]);  
        //主件和两附件  
        if(j>=mv[i]+fv[i][1]+fv[i][2])  
           f[j]=max(f[j],f[j-mv[i]-fv[i][1]-fv[i][2]]+mw[i]+fw[i][1]+fw[i][2]);  
    }  
    cout<<f[n]<<endl;  
    return 0;  
}
/*
1000 5
800 2 0
400 5 1
300 5 1
400 3 0
500 2 0
*/ 
