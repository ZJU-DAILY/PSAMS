import numpy as np
import time
import os
start = time.time()


f = open("matrix.txt","r")
n =int( f.readline())
#print n
data = np.zeros((n,n))
line = f.readline()
i = 0
while line:
    num = np.array([float(x) for x in line.split()])
    data[i,:] = num
    line = f.readline()
    i = i+1
f.close()
np.set_printoptions(suppress=True)
a,b=np.linalg.eig(data)
#print a,b
a_s = np.sort(a)
b_s = b[:,a.argsort()]
c=np.c_[a_s,b_s.T]
end = time.time()
#print end-start
np.savetxt('dim.txt',[n,end-start],fmt = ['%s'],newline = '\n')
np.savetxt('vec.txt',c,fmt = ['%.6f']*c.shape[1],newline = '\n')
os.system("pca.exe ")
