
## Introduction

This repo holds the source code and scripts for pivot selection algorithms in metric apaces.
Details can be refferred to  https://github.com/ZJU-DBL/PSAMS

## Usage

1. Datasets and Pivots 

The used datasets has the following files:
	*.txt
	*_qid.txt
	*_query.txt
The first file contains all the data, and the first line for datasets except 'words' denotes the size, the dimention and the distance metric (taking 1 as an example, it means L-1 Norm Distance).
The second and the third file contains the ids and the values for the quries.

2. Index

After asking the authors for the codes of all the three indexes, we only get the execute file.
The file 'indexes' contains the execute files for LAESA (LAESA_Float.exe, LAESA_String.exe), MVP tree (MVP_Tree_Float.exe, MVP_Tree_String.exe) and SPB (SPB_Tree_Float.exe, SPB_Tree_String.exe) tree. In the sub folder, 'input.txt' is the input file for all the exe files. The sample input is as follow:

```
sample.txt
sample_qid.txt
sample_query.txt
pivot/pivotsample.txt 5  
cost_sample.txt
1 5 10 20 50 100
2 3 4 5 6 8 10
5
```

The first three lines denotes the path of datasets and queries as explained before. The 4th line contains path of the tested pivot and
the corresponding pivot number. The 5th line indicates the output file. The 6th and 7th line are 6 and 7 numbers seperately, which denotes the k for k-nearest neighbour query and r for range query. The last line denotes th size of the query.

After filling 'fil.in', simply runs the exe file and the output file will be generated to the given path.

## Compared algorithms

| __Algorithm__ | __Paper__ | __Year__ |
|-------------|------------|------------|
SSS | Spatial Selection of Sparse Pivots for Similarity Search in Metric Spaces | 2007
FFT | A Best Possible Heuristic for the k-Center Problem | 1985
BPP | A comparison of pivot selection techniques for permutation-based indexing | 2015
BPS | A new version of the nearestneighbour approximating and eliminating search algorithm (AESA) with linear preprocessing time and memory requirements | 1994
HF | The Omni-family of all-purpose access methods: a simple and effective way to make similarity search more efficient | 2007
MV | Reference-based indexing for metric spaces with costly distance measures | 2008
SC | Selecting vantage objects for similarity indexing | 2006
PCA | Pivot selection: Dimension reduction for distance-based indexing | 2012
IS | Pivot selection techniques for proximity searching in metric spaces | 2003
DSSS | A Dynamic Pivot Selection Technique for Similarity Search | 2008
HFI| Efficient metric indexing for similarity search | 2015



## Datasets

Each dataset can be obtained from the following links. 

| __Dataset__ | __link__ | __Dimension__ |
|-------------|------------|------------|
| LA          | http://www.dbs.informatik.uni-muenchen.de/ | 2 |
| Words       | http://icon.shef.ac.uk/Moby/ | 1~34 |
| Color 	  |http://cophir.isti.cnr.it/ |282|
| INT         | |20|

The dataset INT and examples for each dataset are included in the folder dataset.

The specific k for k-nearest neighbour query and r for range query are as belows:
| Dataset | Range for 1%, 2%, 4%, 8%, 16%, 32%, 64% |
| LA	| 473, 692, 989, 1409, 1875, 2314, 3096 | 
| Integer |	2321,2733, 3229,3843, 4614, 5613, 7090 |
| Color	|	3838, 4092, 4399, 4773, 5241, 5904, 7104 |
| Words |		2, 3, 4, 5, 6, 8, 10 |
 
## Citation
If you use our code for research work, please cite our paper as below:
```
@article{,
  title={Pivot Selection Algorithms in Metric Spaces: An Experimental Evaluation},
  author={Yifan Zhu, Lu Chen, Yunjun Gao, Christian S. Jensen},
  year={2021},
}
```
