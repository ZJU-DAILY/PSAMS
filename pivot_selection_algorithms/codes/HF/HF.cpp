#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#include "../dis.h"
#include <sys/time.h> 
#include <iostream>
#define rand() ((rand()%10000)*10000+rand()%10000)
using namespace std;
struct timeval start, end1;
int fgg[NUUM];
double dist[NUUM] ;
int stack[NUUM],top=0;
double sm(double a,double b){ 
	if(a>b) return b;
	return a;
}
void work(){
	top=1;
	int q=rand()%num;
	int k=0;
	double max=-1;
	for(int j=0;j<num;j++) dist[j]=dis(j,q);
	for(int j=0;j<num;j++){
		if(dist[j]>max){
			max=dist[j];
			k=j;
		}
	}
	stack[0]=k;
	fgg[k]=1;
	max=-1;
	for(int j=0;j<num;j++) dist[j]=dis(j,k);
	k=0;
	for(int j=0;j<num;j++){
		if(dist[j]>max){
			max=dist[j];
			k=j;
		}
	}
	stack[top++]=k;
	fgg[k]=1;
	double mmm=dis(stack[0],stack[1]);
	for(int j=0;j<num;j++){
		dist[j]=abs(mmm-dis(j,stack[1]));
	}
	for(int i=2;i<pnum;i++){
		max=dist[0];
		int k=0;
		for(int j=1;j<num;j++)if(fgg[j]==0){
			if(dist[j]<max){
				max=dist[j];
				k=j;
			}
		}
		stack[top++]=k;	
		fgg[k]=1;
		for(int j=0;j<num;j++)dist[j]+=abs(dis(j,k)-mmm);
	}

}
void op(){
	ofstream out1;
	out1.open("../pivothf.txt");
	out1<<top<<endl;
	for(int i=0;i<pnum;i++){
		out1<<stack[i]<<" ";	
	}
	out1<<endl;
	gettimeofday(&end1, NULL);//记录下系统当前时间给end，此时程序结束。
	out1<<"time "<<(end1.tv_sec - start.tv_sec)+ (end1.tv_usec - start.tv_usec)*0.000001 <<" s"<<endl;
	out1.close();	
	
}
int main(){
	readm();
	for(int i=0;i<num;i++)dist[i]=0;	
	gettimeofday(&start, NULL);
	work();				
	op();
}
