
#include "objstring.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <vector>
#include <algorithm>


int ** table1;

Objstring::Objstring(const Objstring & obj)
{
	value = obj.value;
}

Objstring::Objstring(string v)
{
	value = v;
	//dim = d;
}

Objstring & Objstring::operator=(const Objstring & obj)
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

string & Objstring::getValue()
{
	return value;
}

//int Objstring::getDim()
//{
//	return dim;
//}

void Objstring::setValue(string v)
{
	value = v;
}


typedef struct sPalDB
   { char *pals;  /* words all together */
     char **ptrs;  /* pointers to each word */
     int npals;	  /* number of words (there is space for 1 more) */
     int csize;   /* allocated c size */
     int *c;
   } PalDB;

static int never = 1;
static PalDB DB;

#define db(p) (DB.ptrs[(int)p])

	/* edit distance */

double editDist(const char * s1, const char * s2)
{
	double dist = 0.0;
	if (table1 == NULL) {	// init. table if NULL
		table1 = new int*[34 + 1];
		for (int i = 0; i<34 + 1; i++)
			table1[i] = new int[34 + 1];
	}
	int n = strlen(s1), m = strlen(s2);
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
double distanceInter (Obj obj1, Obj obj2)
   { 
	   return editDist(db(obj1), db(obj2));
   }

double qdistanceInter(const char* obj1, Obj obj2)
{
	return editDist(obj1, DB.ptrs[(int)obj2]);
}

Obj parseobj (char *s)

   { 
     char *str = db(NewObj);
     if (str != NULL) free(str);
     str = (char *)malloc (strlen(s)+1);
     strcpy (str,s);
     db(NewObj) = str;
     return NewObj; 
   }

void printobj (Obj obj)

   { printf ("%s\n",db(obj));
   }

int openDB(char *name)
{
	char *ptr, *top;
	FILE *f;
	struct stat sdata;
	unsigned long dn;

	closeDB();

	f = fopen(name, "r");
	stat(name, &sdata);
	DB.pals = (char *)malloc(sdata.st_size);
	fread(DB.pals, sdata.st_size, 1, f);
	fclose(f);
	ptr = DB.pals; top = ptr + sdata.st_size;
	dn = 0;
	int fff = 0, ffg = 0, dnn = 0;
	while (fff == 0 && ptr < top)
	{
		if (*ptr != '\n') {
			ptr++;
			ffg = 1;
		}
		else {
			if (ffg == 0) fff = 1;	else ffg = 0;
			dn++;
			dnn++;
			*ptr++ = 0;
		}
	}
	DB.ptrs = (char **)malloc((dn + 1)*sizeof(char*));
	dn = 0; ptr = DB.pals;
	DB.ptrs[0] = NULL;
	while (ptr < top&&dn<dnn)
	{
		//DB.ptrs[++dn] = ptr;
		// Henry test
		DB.ptrs[dn++] = ptr;
		while (*ptr++);
	}
	DB.npals = dn;
	DB.c = NULL;	//新加的一行，因为在freeIndex时将DB.c释放，loadIndex后进行的knn查询时又对DB.c进行了realloc
					//若DB.c不置为null，则使用了已释放的内存地址，造成错误
	return DB.npals;
}

void closeDB(void)
{
	if (never) { never = 0; DB.pals = NULL; }
	if (DB.pals == NULL) return;
	free(DB.pals);
	free(DB.ptrs);
	free(DB.c); DB.csize = -1;
	DB.pals = NULL;
}
