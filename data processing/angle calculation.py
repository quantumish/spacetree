
#iterate through the files.
lines = open("/Users/chenyiyu/Downloads/csv/r000029819750029/frames/impact.0000", "r").readlines()
import math
import os
import h5py
import numpy as np
unit_vector = {}
data_dir = "/Users/chenyiyu/Downloads/csv/"
D
for root, dirs, files in os.walk(data_dir, topdown=True):
    for name in files:
        if(int(name[7:])):
            print(name,root)
            D = os.path.join(root, name)
            print(D)
            lines = open(D, "r").readlines()



theta = 0
phi = 0
inc = 2*math.pi/20
ep = 0.9
while(theta!=2*math.pi):
    while(phi!=2*math.pi):
        x = math.cos(theta)*math.sin(phi)
        y = math.sin(theta)*math.sin(phi)
        z = math.cos(phi)
        unit_vector[(x,y,z)] = []
        phi+=inc
    theta+=inc


for l in lines[2:]:
    vals = list(map(float, l[:-1].split(" ")))
    x = vals[0]
    y = vals[1]
    z = vals[2]
    cur = math.sqrt(x**2+y**2+z**2)
    x = x/cur
    y = y/cur
    z = z/cur
    v1 = vals[3]
    v2 = vals[4]
    v3 = vals[5]
    temp = -1
    mind = 10
    ar =-1
    for i in unit_vector:
        tp = math.sqrt((i[0]-x)**2+(i[1]-y)**2+(i[2]-y)**2)
        if(tp<mind):
            mind = tp
            ar = i
    unit_vector[ar].append((cur,v1,v2,v3))

output = {}

for i in unit_vector:
    for j in unit_vector[i]:
        dmax = 0
        if(j[0]>dmax):
            dmax = j[0]
            dmax_cor = j
        #number of frequency
    output[i] = [dmax_cor]


#implement normal distribution part


#output via numpy file.



