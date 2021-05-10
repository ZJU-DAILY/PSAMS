#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#include <fstream>
#include <sys/time.h> 
#include "../dis.h"
#include <iostream>
#define rand() ((rand()%10000)*10000+rand()%10000)
using namespace std;
double dist[NUUM];
double* tdist[1000];


int fgg[NUUM];
int stack[NUUM],top=0;
double alpha;
struct timeval start, end1;
double sm(double a,double b){ 
	if(a>b) return b;
	return a;
}
void work(){
	top=1;
	stack[0]=rand()%num;
	fgg[stack[0]]=1;
	for(int j=0;j<num;j++) dist[j]=dis(j,stack[0]);
	for(int i=1;i<pnum*30;i++){
		double max=0;
		int k=-1;
		for(int j=0;j<num;j++)if(fgg[j]==0){
			if(dist[j]>max){
				max=dist[j];
				k=j;
			}
		}
//		cout<<i<<" "<<max<<endl;
		stack[top++]=k;	
		fgg[k]=1;
		for(int j=0;j<num;j++)
		{
			//if(i>=19) cout<<dis(j,k)<<" ";
			dist[j]=sm(dist[j],dis(j,k));
		}

	}

}

void mat(){	
	ofstream out1;
	out1.open("matrix.txt");
	out1<<top<<endl;
	for(int i=0;i<top;i++){
		cout<<"dist "<<i<<endl;
		tdist[i]=new double[num+10];	
		double sum=0;
		for(int k=0;k<num;k++){
			tdist[i][k]=dis(stack[i],k);	
			sum+=tdist[i][k]=dis(stack[i],k);
		}
		sum/=num;
		for(int k=0;k<num;k++)tdist[i][k]-=sum;			
	}		
	for(int i=0;i<top;i++){		
		cout<<"finish "<<i<<endl;
		for(int j=0;j<top;j++){
			double sum=0;	
			
			for(int k=0;k<num;k++)sum+=tdist[i][k]*tdist[j][k];
			out1<<to_string(sum/num);
			if(j==top-1) out1<<endl;
			else out1<<" ";
		}		
	}
	out1.close();
	out1.open("cand.txt");
	gettimeofday(&end1, NULL);//记录下系统当前时间给end，此时程序结束。
	out1<< (end1.tv_sec - start.tv_sec)+ (end1.tv_usec - start.tv_usec)*0.000001<<endl;
	out1<<top<<endl;
	for(int i=0;i<top;i++){		
		out1<<stack[i];
		if(i==top-1) out1<<endl;
		else out1<<" ";				
	}
	out1.close();	
}
int main(){
	
	readm();
	for(int i=0;i<num;i++)fgg[i]=0;
	gettimeofday(&start, NULL);
	work();
	mat();	
	system("1.bat");
	//op();
}
