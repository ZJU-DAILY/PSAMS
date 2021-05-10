#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/time.h> 
#define NUUM 1500000

#define CandA 300
#define FILENAME "../sample.txt" 
using namespace std;

float* loc[NUUM];
int dim;
int pnum=5,num,PairA=0;
int ptype=0;
double mm;
double dis(int i,int j){
	if(ptype==2){
		double sum=0;
		for(int k=0;k<dim;k++) {
			sum+=pow(loc[i][k]-loc[j][k],2);	
		//	cout<<loc[i][k]<<" "<<loc[j][k]<<endl;
		}
		return pow(sum,0.5);	
	}
	if(ptype==1){
		double sum=0;
		for(int k=0;k<dim;k++) sum+=abs(1000+loc[i][k]-loc[j][k]-1000);
		return sum;	
	}

	if(ptype==5){
		double sum=0;
		for(int k=0;k<dim;k++) sum+=pow(loc[i][k]-loc[j][k],5);
		return pow(sum,0.2);	
	}

	if(ptype==0){
		double max=0,p;
		for(int k=0;k<dim;k++) 
		{			
			p=abs(loc[i][k]-loc[j][k]);
			if(p>max) max=p;
		}
		return max;	
	}	
}
void readm(){ //re-read the file
	ifstream ain1;
//	cout<<"Input pnum : ";
//	cin>>pnum;
	ain1.open(FILENAME, ifstream::in);	
	ain1>>dim>>num>>ptype;
	cout<<dim<<" "<<num<<" "<<ptype<<endl;
	PairA=num/100;
	//num=100000;
	for(int i=0;i<num;i++)loc[i]=new float[dim+3];
	for(int i=0;i<num;i++){
		if(i%30000==0) cout<<"read finish "<<i<<endl;
		for(int j=0;j<dim;j++)
			ain1>>loc[i][j];
	}
	ain1.close();	
	int j=1;
	mm=0;
	double mm1=0;
	for(int i=1;i<num;i++) if(dis(0,i)>mm1){
		j=i;
		mm1=dis(0,i);
	}	
	for(int i=1;i<num;i++) if(dis(j,i)>mm) mm=dis(j,i);
	cout<<"maxdis "<<mm*0.05<<endl;
}
