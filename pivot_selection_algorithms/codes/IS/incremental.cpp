#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#include <fstream>
#include "../dis.h"
#include <sys/time.h> 
#include <iostream>
using namespace std;
struct timeval start, end1;
int ppa[NUUM][2];
int stack[NUUM],top=0;
int fgg[NUUM];
int can[NUUM],ctop=0;
double svg[NUUM];
int N=CandA;
void op(){
	ofstream out1;
	out1.open("../pivotis.txt");
	out1<<top<<endl;
	for(int i=0;i<pnum;i++){
		out1<<stack[i]<<" ";	
	}
	out1<<endl;	
	gettimeofday(&end1, NULL);//记录下系统当前时间给end，此时程序结束。
	out1<<"time "<<(end1.tv_sec - start.tv_sec)+ (end1.tv_usec - start.tv_usec)*0.000001 <<" s"<<endl;
	out1.close();
}
void candi(){
	for(int i=0;i<N;i++) fgg[can[i]]=0;
	for(int i=0;i<N;i++){
		int p=rand()%num;
		if(fgg[p]) i--;
		else{
			can[i]=p;
			fgg[p]=1;
		}
	} 
}
void ini() {
	for(int i=0;i<PairA;i++){	
		int p=rand()%num;
		ppa[i][0]=p;
		p=rand()%num;
		ppa[i][1]=p;
		if(ppa[i][0]==ppa[i][1]) i--;	
		svg[i]=0;
	}
}
double dfs(int k){
	double sum=0;
	for(int i=0;i<PairA;i++){	
		double q=abs(dis(k,ppa[i][1])-dis(k,ppa[i][0]));
		if(svg[i]>q) sum+=svg[i];
		else sum+=q;
	}
	return sum;
}
void work(){
	double max=0;
	int k=0;
	candi();
	for(int i=0;i<pnum;i++){		
		max=0;
		for(int j=0;j<N;j++){
			double tmp=dfs(can[j]);
			if(tmp>max){
				max=tmp;
				k=can[j];
			} 
		}
		cout <<i<<" "<<max<<" "<<k<<endl;
		stack[top++]=k;		
		for(int i=0;i<PairA;i++){
			double q=abs(dis(k,ppa[i][1])-dis(k,ppa[i][0]));
			if (svg[i]<q) svg[i]=q;
		}
	}

}
int main(){
	readm();
	gettimeofday(&start, NULL);
	ini();
	work();
	op();
}
