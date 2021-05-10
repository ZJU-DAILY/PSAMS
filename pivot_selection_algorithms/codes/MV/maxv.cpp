#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#include <fstream>
#include "../dis.h"
#include <iostream>
#define NUUM 2000000
#define MUUM 4000000
using namespace std;
struct timeval start, end1;
int stack[NUUM],top=0;
int can[NUUM],ctop=0;
double svg[MUUM];
double avg[MUUM];
int ind[MUUM];
int N=PairA,m;

void op(){
	ofstream out1;
	out1.open("../pivotmv.txt");
	out1<<top<<endl;
	for(int i=0;i<top;i++){
		
		out1<<stack[i]<<" ";	
	}	
	out1<<endl;
	gettimeofday(&end1, NULL);//记录下系统当前时间给end，此时程序结束。
	out1<<"time "<<(end1.tv_sec - start.tv_sec)+ (end1.tv_usec - start.tv_usec)*0.000001 <<" s"<<endl;	
	for(int i=0;i<top;i++){
		for (int j=0;j<dim-1;j++) 
			out1<<loc[stack[i]][j]<<" ";
		out1<<loc[stack[i]][dim-1]<<endl;	
	}	
	out1.close();
}
void candi(){
	for(int i=0;i<N;i++){
		int p=rand()%num;
		can[i]=p;
	} 
}

void dfs(int k){
	double sum=0;
	for(int i=0;i<N;i++){
		double q= dis(k,can[i]);
		if(q>mm) mm=q;
		sum+= dis(k,can[i]);
	} 	
	sum/=N;
	avg[k+1]=sum;
	double nn=0;
	for(int i=0;i<N;i++)nn+=pow(dis(k,can[i])-sum,2);
	svg[k+1]=nn;
}
void up(int i){
	int q=ind[i];
	double p=svg[i];
	int k=i/2;	
	while(k>0&&svg[k]>p){
		svg[i]=svg[k];
		ind[i]=ind[k];
		i=k;
		k=i/2;		
	}
	svg[i]=p;
	ind[i]=q;
}
void down(int i){
	int q=ind[i];
	double p=svg[i];
	int k=i*2;
	if (k<m&&svg[k]>svg[k+1]) k++;
	while(k<m&&svg[k]<p){
		svg[i]=svg[k];
		ind[i]=ind[k];
		i=k;
		k=i*2;
		if (k<m&&svg[k]>svg[k+1]) k++;
	}
	svg[i]=p;
	ind[i]=q;
}
void sort(int n){	
	for(int i=1;i<=n;i++) up(i);
	m=n;
	for(int i=n;i>=1;i--) {
		int q=ind[i];
		ind[i]=ind[1];
		ind[1]=q;
		double p=svg[i];
		svg[i]=svg[1];
		svg[1]=p;
		m--;
		down(1);
	}
}
int check(int k){
	for(int i=0;i<top;i++){
		double q=dis(ind[stack[i]],ind[k]);
		double p=avg[stack[i]];
		if(q<p-mm||q>p+mm) return 0;		
	}
	return 1;
}
void work(){
	double max=0;
	int k=0;
	candi();
	for(int i=0;i<num/100;i++){
		if(i%((int)(pow(num,0.5)))==0){
			cout<<i <<endl;
		} 
		max=0;
		ind[i+1]=i;
		dfs(i);
	}
	mm=mm*0.15;
	sort(num/100);
	top=0;
	k=0;	
	while (top<pnum&&k<num/100){		
		k++;
		while(k<num&&check(k)==0) k++;
		if(k>=num/100) break;
		stack[top]=k;		
		top++;
	}
	cout<<"Get pivots: "<<top<<endl;
	for(int i=0;i<top;i++){
		stack[i]=ind[stack[i]];
	}
}
int main(){
	readm();

	gettimeofday(&start, NULL);
	work();
	op();
	fclose(stdout);
}
