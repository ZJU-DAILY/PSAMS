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
int stack[NUUM],top=0;
double alpha=0.15;
int check(int k){
	double mm1=100000;
	for(int i=0;i<top;i++){
		if(dis(k,stack[i])<mm*alpha){			
			return 1;		
		} 
		if(dis(k,stack[i])<mm1) mm1=dis(k,stack[i]);	
	}
	cout<<"pick "<<mm1<<endl;
	return 0;
}
void work(){
	
	top=1;
	stack[0]=rand()%num;
	for(int i=0;i<num;i++){		
		if (check(i)==0){
			stack[top++]=i;
		}		
		if(top%1000==0) cout<<"top="<<top<<" i= "<<i<<endl;
	}

}
void op(){
	ofstream out1;
	out1.open("../pivotsss.txt");
	if(top>pnum)  top=pnum;
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
	gettimeofday(&start, NULL);	
	work();
	cout<<top<<endl;
	op();
}
