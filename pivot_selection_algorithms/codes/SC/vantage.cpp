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
int od[NUUM],ot=0; 
int nd[NUUM],nt=0;
double ssg[NUUM];
double sig[NUUM];
double svg[NUUM];
double ecorr=0.83,esp=34000000;
double miu=0;
double alpha;
double sigma(int i,int k){
	return pow(dis(stack[i],nd[k])-dis(stack[i],nd[k-1])-svg[i]/nt,2);
}
void update(int i){
	double p=dis(stack[i],nd[nt-1]);
	svg[i]+=p;
	ssg[i]+=p*p;
	sig[i]=sig[i]*(nt-1)+pow(dis(stack[i],nd[nt-1])-dis(stack[i],nd[nt-2])-svg[i]/nt,2);
	sig[i]/=nt;
}

void clear_a(int i){
	double sum=0;
	ssg[i]=0;
	svg[i]=0;
	for(int k=0;k<nt;k++) {
		double q=dis(stack[i],nd[k]);
		svg[i]+=q;
		ssg[i]+=q*q;
	}
	sum=0;
	for(int k=1;k<nt;k++) sum+=sigma(i,k);
	sig[i]=sum/nt;
}
double cor(int i,int j){
	double sum=0;
	for(int k=0;k<nt;k++) 
	{sum+=dis(stack[i],nd[k])*dis(stack[j],nd[k]);
	}
	sum*=nt;
	sum-=svg[i]*svg[j];
	sum/=pow((nt*ssg[i]-svg[i]*svg[i])*(nt*ssg[j]-svg[j]*svg[j]),0.5);
	sum=abs(sum);
	return sum;
}

void op(){
	ofstream out1;
	out1.open("../pivotsc.txt");
	out1<<pnum<<endl;
	for(int i=0;i<pnum;i++){
		out1<<stack[i]<<" ";	
	}
	out1<<endl;
	gettimeofday(&end1, NULL);//记录下系统当前时间给end，此时程序结束。
	out1<<"time "<<(end1.tv_sec - start.tv_sec)+ (end1.tv_usec - start.tv_usec)*0.000001 <<" s"<<endl;
	out1.close();	
	
}
void ini() {
	for(int k=0;k<pnum;k++){
		int p=rand()%ot;
		stack[k]=od[p];
		od[p]=od[ot-1];
		od[ot-1]=stack[k];
		ot--;
		svg[k]=0;
		sig[k]=0;
		ssg[k]=0;
	}
}
void res(int i){
	int p=rand()%num;
	stack[i]=od[p];
	clear_a(i);
}
void work(){
	ot=num;
	int q;
	cout<<"num"<<num<<endl;
	//for(int i=0;i<num;i++){
	for(int i=0;i<num;i++){
		if (i%100==0) cout<<"ittr "<<i<<" q= "<<q<<endl;
		int boo[1000];
		for (int j=0;j<pnum;j++)boo[j]=0;
		int p=rand()%ot;

		int flg=0;
		nd[nt++]=od[p];
		od[p]=od[--ot];
		od[ot+1]=nd[nt-1];
		for(int j=0;j<pnum;j++){
			update(j);
			if(i==0) continue;
			if(sig[j]>esp) {
				flg=1;
				if(i%100==0)cout<<"rechoose sigma "<<sig[j]<<" "<<esp<<endl;
				res(j);
				boo[j]=1;
			}
		}
		if(i<3) continue;
		for(int j=0;j<pnum;j++)
			for(int k=0;k<pnum;k++)
			if(j!=k&&cor(j,k)>ecorr){
				flg=1;
				if(i%100==0)cout<<"rechoose corr "<<cor(j,k)<<" "<<ecorr<<endl;
				if(sig[j]>sig[k]) res(j);
				else res(k);
			}
		if(i%50==0)cout<<"==========="<<endl;
		if(flg==0) q++;
		else q=0;
		if(i>pow(num,0.6)&&q>400) break;
		
	}
cout<<num<<" "<<pow(num,0.5)<<endl;
}
int main(){
	readm();
	ot=num;
	for(int i=0;i<num;i++)od[i]=i;
	gettimeofday(&start, NULL);
	ini();
	work();
	op();
}
