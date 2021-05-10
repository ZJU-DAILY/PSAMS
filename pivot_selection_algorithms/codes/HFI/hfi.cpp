
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <iostream>
#include "objvector.cpp"
//#include "objstring.cpp"
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#define MAX(x, y) ((x>y)? (x): (y))

using namespace std;
string filname;
#define MAXREAL 1e20
#define num_cand 300
int * cand;

using namespace std;

double **DISTANCIAS;

int * sequence;
int * pivotSeq;

// provide non-repeated pivot selecting
void getNonRepeatedRandomNum(int * &rs, int nums, int totalnum)
{
	int end = totalnum;
	int num;
	for (int i = 0; i < nums; i++) {
		num = rand() % end;
		rs[i] = sequence[num];
		sequence[num] = sequence[end - 1]; // move the last value to the selected position
		end--; // decrease random range by one
	}
	sort(rs, rs + nums);
}

double dame_distancia(int x, int y)
{
	return DISTANCIAS[x][y];
}

//find num_cand pivots in O using maxpruning strategy
double** MaxPrunning(int num)
{
	cand = new int[num_cand];
	bool * indicator = new bool[num];
	for (int i = 0; i < num; i++)
		indicator[i] = true;
	int * idset = new int[num_cand];

	double d = 0.0;
	double t;
	int choose = 0;
	//存储所有对象到pivot距离
	double** distmatrix = new double*[num];
	for (int i = 0; i < num; i++)
	{
		distmatrix[i] = new double[num_cand];
		for (int j = 0; j < num_cand; j++)
			distmatrix[i][j] = 0;
	}

	//选取第一个pivot
	if (num_cand > 0)
	{

		for (int i = 1; i < num; i++)
		{
			t = mydistance(i, 0);
			if (t > d)
			{
				d = t;
				choose = i;
			}
		}

		idset[0] = choose;
		cand[0] = choose;
		indicator[choose] = false;
		//distmatrix[choose][0]=0;
	}

	//选取第二个pivot
	if (num_cand > 1)
	{
		d = 0;
		for (int i = 0; i < num; i++)
		{
			if (indicator[i])
			{
				distmatrix[i][0] = mydistance(cand[0], i);
				if (distmatrix[i][0] > d)
				{
					d = distmatrix[i][0];
					choose = i;
				}
			}
		}

		idset[1] = choose;
		cand[1] = choose;
		indicator[choose] = false;
		//distmatrix[choose][1]=0;
	}

	//选取剩余所有pivots
	double edge = d;
	d = MAXREAL;
	for (int i = 2; i < num_cand; i++)
	{
		d = MAXREAL;
		for (int j = 0; j < num; j++)
		{
			if (indicator[j])
			{
				t = 0;
				for (int k = 0; k < i - 1; k++)
				{
					t += fabs(edge - distmatrix[j][k]);
				}
				distmatrix[j][i - 1] = mydistance(j, cand[i - 1]);
				t += fabs(edge - distmatrix[j][i - 1]);
				if (t < d)
				{
					d = t;
					choose = j;
				}
			}
		}

		idset[i] = choose;
		//distmatrix[choose][i]= 0;
		indicator[choose] = false;
		cand[i] = choose;
	}


	//print distance matrix

	for (int i = 0; i < num; i++)
	{
		if (indicator[i])
		{
			distmatrix[i][num_cand - 1] = mydistance(i, cand[num_cand - 1]);
		}
	}

	for (int i = 0; i < num_cand; i++)
		for (int j = i + 1; j < num_cand; j++)
			distmatrix[idset[i]][j] = mydistance(idset[i], cand[j]);

	delete[] indicator;
	delete[] idset;

	return distmatrix;
}

int PivotSelect(int o_num, int q_num, int pivotNum)
{
	clock_t begin, buildEnd, queryEnd;
	begin = clock();
	double ** O_P_matrix = MaxPrunning(o_num);
	double ** Q_O_matrix = new double *[q_num];
	double ** Q_P_matrix = new double*[q_num];
	double ** esti = new double*[q_num];
	for (int i = 0; i < q_num; i++)
	{
		Q_O_matrix[i] = new double[o_num];
		Q_P_matrix[i] = new double[num_cand];
		esti[i] = new double[o_num];
	}
	bool* indicator = new bool[num_cand];
	for (int i = 0; i < num_cand; i++)
		indicator[i] = true;


	for (int i = 0; i < q_num; i++)
	{
		for (int j = 0; j < o_num; j++)
		{
			Q_O_matrix[i][j] = mydistance(i, j);
			esti[i][j] = 0;
		}
		for (int j = 0; j < num_cand; j++)
		{
			Q_P_matrix[i][j] = mydistance(i, cand[j]);
		}
	}


	double d = 0;
	double t = 0;
	int choose;
	pivotSeq = new int[pivotNum];
	int i;
	ofstream out1;
	out1.open("../pivothfi.txt");
	out1 << pivotNum << endl;
	for (i = 0; i < pivotNum; i++)
	{
		choose = -1;
		for (int j = 0; j < num_cand; j++)
		{
			if (indicator[j])
			{
				t = 0;
				for (int m = 0; m < q_num; m++)
				{
					for (int n = 0; n < o_num; n++)
					{
						if (Q_O_matrix[m][n] != 0)
						{
							t += (MAX(fabs(Q_P_matrix[m][j] - O_P_matrix[n][j]), esti[m][n])) / Q_O_matrix[m][n];
						}
					}
				}
				t = t / (q_num*o_num);
				if (t > d)
				{
					choose = j;
					d = t;
				}
			}
		}

		out1 << cand[choose] << endl;
		if (choose == -1)
			break;
		indicator[choose] = false;
		pivotSeq[i] = cand[choose];
		for (int m = 0; m < q_num; m++)
			for (int n = 0; n < o_num; n++)
				esti[m][n] = MAX(fabs(Q_P_matrix[m][choose] - O_P_matrix[n][choose]), esti[m][n]);
	}
	out1 << "time " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
	out1.close();
	cout << "pivot finish" << endl;

	return pivotNum;
}


int main(){

	int n, np;
	struct stat sdata;
	//struct tms t1,t2;
	char* fname;



	string filnn;
	char * finame = "../../LA.txt";
	
	int pn = 5;	
	cout << "input pnum : 5" << endl;
	//cin >> pn;

	n = openDB(finame);
	PivotSelect(n/100, num_cand,pn);
	return 0;
}

