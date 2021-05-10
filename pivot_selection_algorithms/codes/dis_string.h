#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <sys/time.h> 
#define NUUM 1500000

#define CandA 300
#define FILENAME "../sample.txt" 
using namespace std;

string loc[NUUM];
int dim;
int pnum=5,num,PairA=0;
int ptype=0;
double mm=0;
int ** table1;
double dis(int ii,int jj){
	string s1=loc[ii] ;
	string s2=loc[jj];
	double dist = 0.0;
	if (table1 == NULL) {	// init. table if NULL
		table1 = new int*[34 + 1];
		for (int i = 0; i<34 + 1; i++)
			table1[i] = new int[34 + 1];
	}


	int n = s1.length(), m = s2.length();
	if (n == 0) return m;
	if (m == 0) return n;
	//printf("%d %d\n",m,n);
	for (int i = 0; i <= n; i++) table1[i][0] = i;
	for (int j = 0; j <= m; j++) table1[0][j] = j;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;	// ith character of s, jth character of t
			table1[i][j] = 1 + min(table1[i - 1][j], table1[i][j - 1]);
			table1[i][j] = min(table1[i - 1][j - 1] + cost, table1[i][j]);
		}
	}
	return (double)(table1[n][m]);
}
void readm(){ //re-read the file
	ifstream ain1;
	cout<<"Pnum : 5";
	//cin>>pnum;
	ain1.open(FILENAME, ifstream::in);	
	num=0;
	string str;
	while(getline(ain1, str)){
		loc[num]=str;
		num++;
	}
	cout<<"num "<<num<<endl;
	PairA=num/100;
	ain1.close();	
	mm=0;
	for(int i=0;i<num;i++) if(loc[i].length()>mm) mm=loc[i].length();
	cout<<"maxdis "<<mm<<endl;
}
