#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#include <fstream>
#include "../dis.h"
#include <sys/time.h> 
#include <iostream>
#define rand() ((rand()%10000)*10000+rand()%10000)
using namespace std;
struct timeval start, end1;
double dist[NUUM] ;
int fgg[NUUM];
int stack[NUUM],top=0;
double alpha;

double sm(double a,double b){ 
	if(a>b) return b;
	return a;
}
void work(){
	top=1;
	stack[0]=rand()%num;
	fgg[stack[0]]=1;
	for(int j=0;j<num;j++) dist[j]=dis(j,stack[0]);
	for(int i=1;i<pnum;i++){
		double max=0;
		int k=-1;
		for(int j=0;j<num;j++)if(fgg[j]==0){
			if(dist[j]>max){
				max=dist[j];
				k=j;
			}
		}
		stack[top++]=k;	
		fgg[k]=1;
		for(int j=0;j<num;j++)dist[j]=sm(dist[j],dis(j,k));
	}

}

void op(){	
	ofstream out1;
	out1.open("../pivotfft.txt");
	out1<<top<<endl;
	for(int i=0;i<top;i++){
		out1<<stack[i]<<" ";		
	}	
	out1<<endl;	
	gettimeofday(&end1, NULL);//记录下系统当前时间给end，此时程序结束。
	out1<<"time "<<(end1.tv_sec - start.tv_sec)+ (end1.tv_usec - start.tv_usec)*0.000001 <<" s"<<endl;	
	out1.close(); 
}
int main(){
	readm();
	for(int i=0;i<=num;i++)fgg[i]=0;
	gettimeofday(&start, NULL);
	work();				
	op();
}
