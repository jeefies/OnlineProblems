#include<bits/stdc++.h>  
using namespace std;  
const int maxN=32005,maxM=185;
int m,n,mw[maxM],mv[maxM],fw[maxM][3],fv[maxM][3],f[maxN],v,p,q;  
//mw������ֵ��mv�������ػ���fw������Ӧ�ĸ�����ֵ��fv�������ػ���n��Ǯ����m��Ʒ����   
int main(){  
    cin>>n>>m;  
	memset(fv,0,sizeof(fv));
    for(int i=1;i<=m;i++){  
       cin>>v>>p>>q;  
       if(!q){//���������   
          mv[i]=v;//������ֵ   
          mw[i]=v*p;//������ֵ����Ҫ�ȵĳ˻�   
       }  
       else{//����Ǹ���   
          fv[q][0]++;//��¼�����ĸ�������   
          fv[q][fv[q][0]]=v;//ȷ������һ�򸽼���   
          fw[q][fv[q][0]]=v*p;  
       }  
    }  
    for(int i=1;i<=m;i++)  
    for(int j=n;j>=mv[i];j--){   
        //ֻҪ���� 
        f[j]=max(f[j],f[j-mv[i]]+mw[i]);  
        //�����͸���1  
        if(j>=mv[i]+fv[i][1])f[j]=max(f[j],f[j-mv[i]-fv[i][1]]+mw[i]+fw[i][1]);  
        //�����͸���2 
        if(j>=mv[i]+fv[i][2])f[j]=max(f[j],f[j-mv[i]-fv[i][2]]+mw[i]+fw[i][2]);  
        //������������  
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
