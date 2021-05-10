#include <string>
#include <cstring>
#include <cmath>
#include <fstream>
#include "../dis.h"
#include <ctime>
#include <iostream>
#include <sys/time.h> 
using namespace std;
struct timeval start, end1;
int pivot[NUUM],fa[NUUM];
double rec[NUUM],dist[NUUM];
int stack[NUUM],top;
int yiz=5,cstack[NUUM][2],ctop=0;
int best_p[3000],s_p[3000],stop;
double mxd=100000000;
double distsim[400][200000];
double distsim1[200000];
double best_min=10000000,s_min=10000000;
double beta=0.4;
double alpha=2;
double ttt=0;
void gen(){
	top=0; 
	for(int i=0;i<ctop;i++){
		cstack[i][0]=rand()%num;
		cstack[i][1]=rand()%num;
		if(cstack[i][0]==cstack[i][1]) i--;			
	}
	for(int i=0;i<CandA;i++) fa[i]=-1;
	while (CandA>top){
		int maxi=rand()%num;		
		stack[top++]=maxi;	
		if(fa[maxi]==1) top--;
		fa[maxi]=1;		
	}	
	
	for(int i=0;i<ctop;i++)		{	
//	cout<<"firtst "<<dis(41,184)<<endl;
		distsim1[i]=dis(cstack[i][0],cstack[i][1]); 
		for(int j=0;j<top;j++)	distsim[j][i]=abs(dis(stack[j],cstack[i][0])-dis(stack[j],cstack[i][1]));		
//		cout<<num<<" "<<cstack[i][0]<<" "<<cstack[i][1]<<"test " <<dis(cstack[i][0],cstack[i][1])<<endl;
	}
}
double objr(double alpha){
	double sum=0;
	for(int i=0;i<ctop;i++){
		double max=0,q,p;
		p=distsim1[i]; 
		for(int k=0;k<stop;k++){
			q=distsim[s_p[k]][i];
			if(q>max) max=q;				
		} 	
	//	cout<<"this is "<<p<<" "<<max<<endl;
	 	sum+=p*pow(1-max/p,alpha)/CandA;
	}
	return sum;
}

void op(int ii){
	ofstream out1;

	char tmpf1[20];
	sprintf(tmpf1, "../pivotwdr.txt");
	string tmpf(tmpf1);
	out1.open(tmpf);
	out1<<pnum<<endl;
	for(int i=0;i<pnum;i++)out1<<stack[s_p[i]]<<" ";	
	out1<<endl;	
	gettimeofday(&end1, NULL);//记录下系统当前时间给end，此时程序结束。
	double ttm=(end1.tv_sec - start.tv_sec)+ (end1.tv_usec - start.tv_usec)*0.000001;
	out1<<"time "<<ttm <<" s"<<endl;
	out1.close();		
}
void exp(){
	stop=1;
	double min=10000000;
	int pos=-1;	
	for(int j=0;j<top;j++)		
		{
			s_p[stop-1]=j;
			double tt=objr(alpha);
			if(tt<min-0.00000001){
				pos=j;
				min=tt;
			}
		}
	s_p[0]=pos;
	stop=1;
	int i=50,fgg;
	while(i--){
		cout<<"doing : "<<50-i<<" Cand: ";
		for(int j=0;j<stop;j++){
			cout<<stack[s_p[j]]<<" ";
		}
		cout<<endl;
		if(stop<pnum){				
			cout<<" ans= "<<objr(alpha)<<endl;
			stop++;
			min=10000000;
			pos=-1;
			for(int j=0;j<top;j++)		
				{
					s_p[stop-1]=j;
					double tt=objr(alpha);
					if(tt<min-0.00000001){
						pos=j;
						min=tt;
					}
				}
			s_p[stop-1]=pos;		
			if(pos==-1) break;
			continue;
		}		
		min=objr(alpha);
		int f=0;
		cout<<top<<" is top and stop "<< stop<<" min "<<min<<endl;
		for(int i=0;i<top;i++)		
		for(int j=0;j<stop;j++){
			int q=s_p[j];
			s_p[j]=i;
			double tt=objr(alpha);
			if(tt<min-0.00000001){
				f=1;
				q=i;
			}
			s_p[j]=q;
		} 
		if(f==0) break;		
	}
	stop=pnum;		
}
void sortp(){
	stop=1;
	double recc[100];
	for(int j=0;j<pnum;j++){
		s_p[pnum]=s_p[0];
		s_p[0]=s_p[j];
		recc[j]=objr(alpha);
		s_p[0]=s_p[pnum];
	}
	for(int i=0;i<pnum;i++)
		for(int j=i;j<pnum;j++)
			if(recc[i]>recc[j]){
				recc[pnum]=recc[i];
				recc[i]=recc[j];
				recc[j]=recc[pnum];
				s_p[pnum]=s_p[i];
				s_p[i]=s_p[j];
				s_p[j]=s_p[pnum];
			}
	stop=pnum;
	for(int i=0;i<pnum;i++)
		cout<<"rec pivot "<<i<<" rec "<<recc[i]<<endl;	
}
int main(){
	
	readm();
//	freopen("../wrr.log","w",stdout);
	ctop=num/100;
	gettimeofday(&start, NULL);	
	gen();		
	exp();
	sortp();
	op(-1);		
	fclose(stdout);
}
