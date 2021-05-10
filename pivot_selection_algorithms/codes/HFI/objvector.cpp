
#include "objvector.h"

#include <math.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>  
using namespace std;

Objvector::Objvector(const Objvector & obj)
{
	value = obj.value;
}

Objvector::Objvector(vector<double> v)
{
	value = v;
	//dim = d;
}

Objvector & Objvector::operator=(const Objvector & obj)
{
	// TODO: insert return statement here
	if (this == &obj) {
		return *this;
	}
	else {
		value = obj.value;
		//dim = obj.dim;
	}
}

vector<double> & Objvector::getValue()
{
	return value;
}

//int Objvector::getDim()
//{
//	return dim;
//}

void Objvector::setValue(vector<double> v)
{
	value = v;
}


typedef struct sEuclDB
{
	double *nums;  /* coords all together */
	int nnums;	  /* number of vectors (with space for one more) */
	int coords;  /* coordinates */
	double(*df) (double *p1, double *p2, int k); /* distance to use */
	double *nobj;
} EuclDB;

static int never = 1;
static EuclDB DB;

#define db(p) (DB.nums + DB.coords*(int)p)

/* L2 distance */

static double L2D(double *p1, double *p2, int k)
{
	register int i;
	double tot = 0, dif;
	for (i = 0; i < k; i++)
	{
		dif = (p1[i] - p2[i]);
		tot += dif*dif;
	}
	return sqrt(tot);
}

static double L5D(double *p1, double *p2, int k)
{
	register int i;
	double tot = 0, dif;
	for (i = 0; i < k; i++)
	{
		dif = fabs(p1[i] - p2[i]);
		tot += pow(dif, 5);
	}
	return pow(tot, 0.2);
}

static double L1D(double *p1, double *p2, int k)
{
	register int i;
	double tot = 0, dif;
	for (i = 0; i < k; i++)
	{
		dif = (p1[i] - p2[i]);
		if (dif < 0) dif = -dif;
		tot += dif;
	}
	return tot;
}

static double LiD(double *p1, double *p2, int k)
{
	register int i;
	double max = 0, dif;
	for (i = 0; i < k; i++)
	{
		dif = (p1[i] - p2[i]);
		if (dif < 0) dif = -dif;
		if (dif > max) max = dif;
	}
	return max;
}

double distanceInter(Obj o1, Obj o2)

{
	return DB.df(db(o1), db(o2), DB.coords);
}
void showo(int o1)

{
	for (int j = 0; j < DB.coords; ++j)
	{
		cout<<DB.nums[o1*DB.coords + j]<<" ";
	}
	cout << endl;	
}

double qdistanceInter(Objvector o1, Obj o2)

{
	for (int d = 0; d < DB.coords; ++d) {
		DB.nobj[d] = o1.getValue()[d];
	}
	return DB.df(DB.nobj, db(o2), DB.coords);
}

Obj parseobj(char *p)

{
	double *d = db(NewObj);
	int i, step;
	for (i = 0;i<DB.coords - 1;i++)
	{
		sscanf(p, "%lf,%n", d + i, &step);
		p += step;
	}
	sscanf(p, "%lf", d + i);
	return NewObj;
}

void printobj(Obj obj)

{
	int i;
	double *p = db(obj);
	for (i = 0;i<DB.coords - 1;i++) printf("%f,", p[i]);
	printf("%f\n", p[i]);
}

int openDB(char *name)
{
	FILE *f = fopen(name, "r");
	cout << name << endl;
	int dim, num, func;
	fscanf(f, "%d%d%d", &dim, &num, &func);
	if (func == 1) DB.df = L1D;
	else if (func == 2) DB.df = L2D;
	else if (func == 5) DB.df = L5D;
	else DB.df = LiD;
	DB.coords = dim;
	DB.nnums = num;
	DB.nums = (double *)malloc((DB.nnums + 1) * sizeof(double)* DB.coords);
	DB.nobj = (double *)malloc(DB.coords * sizeof(double));

	for (int i = 0; i < DB.nnums; ++i)
	{
		for (int j = 0; j < DB.coords; ++j)
		{
			fscanf(f, "%lf", &DB.nums[i*DB.coords + j]);
		}
//		fscanf(f, "\n");

	}
	fclose(f);
	
	return DB.nnums;
}

void closeDB(void)

{
	if (never) { DB.nums = NULL; never = 0; }
	if (DB.nums == NULL) return;
	free(DB.nums);
	DB.nums = NULL;
}

