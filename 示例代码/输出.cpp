int n,m,t;
void print(int i,int j){
	if(i==0)return;
	for(int k=0;k<=j;k++)
	   if(t==f[i-1][k]+value[i][j-k]){
	   	   t=f[i-1][k];
	   	   print(i-1,k);
	   	   cout<<i<<" "<<j-k<<endl;
	   	   break;
	   }
} 
int main(){
	t=f[n][m];
	print(n,m);
}
