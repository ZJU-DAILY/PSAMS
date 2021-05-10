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
int ppa[NUUM][2];
double MaxD[NUUM];
double contribution[NUUM];
int stack[NUUM],top=0,ptop=0; 
double alpha=0.06;
double rat=0;
ifstream ain1;

double ddis(int i,int j){
	return abs(dis(ppa[i][0],stack[j])-dis(ppa[i][1],stack[j]));
}
int check(int k){
	for(int i=0;i<top;i++){
		if(dis(k,stack[i])<mm*alpha) return 1;
	}
	return 0;
}

void work(){	
	top=1;
	stack[0]=0;
	for(int i=1;i<num;i++){
		if (check(i)==0){
			stack[top++]=i;
		}		
	}
}

void slim(){
	for(int i=0;i<ptop;i++){
		int p=rand()%num;
		ppa[i][0]=p;
		p=rand()%num;
		ppa[i][1]=p;
		if(ppa[i][0]==ppa[i][1]) i--;			
	}
	for(int k=pnum;k<top;k++){
		int temp;
		for(int j=0;j<pnum;j++) contribution[j]=0;
		for(int j=0;j<ptop;j++)MaxD[j]=0;
		for(int i=0;i<ptop;i++){
			int i1=0,i2=0;
			double max1=ddis(i,0),max2=ddis(i,0),tt=0;
			for(int j=1;j<pnum;j++){
				tt=ddis(i,j);
				if (tt>max1){
					max2=max1;
					i2=i1;
					max1=tt;
					i1=i;					
				}
				else if(tt>max2){
					max2=tt;
					i2=i;
				}
			}
			contribution[i1]+=max1-max2;
			tt=ddis(i,k);
			if(tt>max1) contribution[pnum]+=tt-max1;
		}
		temp=pnum;
		for(int j=0;j<pnum;j++)if(contribution[j]<contribution[temp]) temp=j;
		if (temp<pnum){
			stack[temp]=stack[k];
		}			
	}
	top=pnum;
}

void op(){
	ofstream out1;
	out1.open("../pivotdsss.txt");
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
	ptop=PairA;
	gettimeofday(&start, NULL);
	work();	
	cout<<top<<endl;
	slim();
	op();
}

