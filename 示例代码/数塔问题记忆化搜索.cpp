#include<bits/stdc++.h>
using namespace std;
int A[202][202],triangle[202][202],n;
int dfs(int i,int j){//�ӵ�ǰλ�ÿ�ʼ�Ŀɵõ�����ֵ
   int s1,s2 ;              
   if (A[i][j]!=-1) return A[i][j];  //��֦
   if (i>n||j>i) return 0;   
   s1=dfs(i+1,j)+triangle[i][j];     
   s2=dfs(i+1,j+1)+triangle[i][j];    
   if (s1>s2) A[i][j] =s1;  //������ֵ����¼       
   else A[i][j]=s2;               
   return A[i][j];  
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=i;j++)
	    scanf("%d",&triangle[i][j]); 
	memset(A,-1,sizeof(A));
	dfs(1,1);
	printf("%d\n",A[1][1]);
	return 0;
}
