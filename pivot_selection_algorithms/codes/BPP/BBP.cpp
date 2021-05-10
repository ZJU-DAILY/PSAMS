#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#include <fstream>
#include "../dis.h"
#include <sys/time.h> 
#include <iostream>
#define NUUM 2000000
#define rand() ((rand()%10000)*10000+rand()%10000)
using namespace std;
struct timeval start, end1;
//double loc[NUUM][30];
//int dim;
//int ptype;
double dist[15000][400] ;
int rnk[15000][400] ;
int flg[500];
double rec[500][400];
int apn[400],acn[15000];

int stack[NUUM],top=0;
double alpha;
int pn=CandA,cn=PairA;

double cnt(int p){ 
	for(int i=0;i<pn;i++) 
	for(int k=0;k<=p;k++)
		rec[i][k]=0;
	for(int k=0;k<cn;k++){
		int j=0;
		for(int i=0;i<pn;i++) if(flg[rnk[k][i]]==1){
			j++;
			rec[rnk[k][i]][j]++;
			if(j==p) break;
		}		
	}
		
	for(int i=0;i<pn;i++)if(flg[i]){
		for(int k=1;k<=p;k++)
			rec[i][0]+=rec[i][k];	
		rec[i][0]/=1.0*p;		
	} 

	double s=0;
	for(int i=0;i<pn;i++) if(flg[i])
	for(int k=1;k<=p;k++)
		s+=(rec[i][k]-rec[i][0])*(rec[i][k]-rec[i][0])*1.0/p;
	s=s*1.0/pn;
	return s;
}
int tot(){
	int s=0;
	for(int i=0;i<pn;i++) s+=flg[i];
	return s;
}
void work(){
	int p=tot();
	while(tot()>pnum){	
		
		if(p>100) p=100;
		double t1=100000000;
		int min=-1;
		for(int i=0;i<pn;i++) if(flg[i]==1){
			flg[i]=0;
			double q=cnt(p);
			flg[i]=1;
			if(q<t1){
				t1=q;
				min=i;
			}
		}
		flg[min]=0;		
		
		p=tot();
		if(p%10==0)cout<<"here "<<p<<" "<<t1<<endl;	
	}
}

void op(){	
	ofstream out1;
	out1.open("../pivotbpp.txt");
	out1<<pnum<<endl;
	for(int i=0;i<pn;i++){
		if(flg[i])out1<<apn[i]<<" ";		
	}	
	out1<<endl;	
	gettimeofday(&end1, NULL);//记录下系统当前时间给end，此时程序结束。
	out1<<"time "<<(end1.tv_sec - start.tv_sec)+ (end1.tv_usec - start.tv_usec)*0.000001 <<" s"<<endl;	
	out1.close(); 
}
void swp(int k,int i,int j){
	double q=dist[k][i];
	dist[k][i]=dist[k][j];
	dist[k][j]=q;
	int p=rnk[k][i];
	rnk[k][i]=rnk[k][j];
	rnk[k][j]=p;
}
int main(){
	readm();
	cn=num/100 ;
	gettimeofday(&start, NULL);
	for(int i=0;i<pn;i++){
		apn[i]=rand()%num;	
		flg[i]=1;
	}
	
	for(int i=0;i<cn;i++)acn[i]=rand()%num;
	for(int i=0;i<cn;i++)
		for(int j=0;j<pn;j++){
			dist[i][j]=dis(acn[i],apn[j]);
			rnk[i][j]=j;
		}
	for(int k=0;k<cn;k++)
		for(int i=0;i<pn;i++)
		for(int j=i+1;j<pn;j++)
			if(dist[k][i]>dist[k][j]){
				swp(k,i,j);
			}

	work();				
	op();
}
