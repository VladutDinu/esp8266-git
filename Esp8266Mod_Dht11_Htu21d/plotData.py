import matplotlib as mpl
import csv
import matplotlib.pyplot as plt
temp=[]
humd=[]
f=open("data.txt","r+")
f1=f.read()
rezultate=f1.split('\n')
for x in rezultate:
    r1=x.split(',')
    if r1[0]:
        temp.append(r1[0])
        humd.append(r1[1])
print(temp)
print(humd)
plt.plot(temp,humd)
plt.show()