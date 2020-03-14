import matplotlib as mpl
import csv
from datetime import *
import matplotlib.pyplot as plt
temp=[]
humd=[]
timeS=[]
f=open("data.txt","r+")
f1=f.read()
rezultate=f1.split('\n')
for x in rezultate:
    r1=x.split(',')
    if r1[0]:
        timeS.append(datetime.fromtimestamp(int(r1[0]) / 1000).strftime("%H:%M:%S")) # add the time stamp to a vector
        temp.append(r1[1])
        humd.append(r1[2])
print(temp)
print(humd)
print(timeS)
plt.plot(timeS,humd)
plt.plot(timeS,temp)
plt.show()