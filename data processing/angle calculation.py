
import math
import os
import h5py
import numpy as np
from lmfit.models import SkewedGaussianModel
unit_vector = {}
data_dir = "/Users/chenyiyu/Downloads/csv/"

for root, dirs, files in os.walk(data_dir, topdown=True):
    for name in files:
        if (name[7:].isnumeric()):
            if(int(name[7:])==0):
                Dip = os.path.join(root, name)
                Dop = os.path.join(root, pname)
                linesip = open(Dip, "r").readlines()
                linesop = open(Dop, "r").readlines()

                theta = 0
                phi = 0
                inc = 2 * math.pi / 20
                while (theta != 2 * math.pi):
                    while (phi != 2 * math.pi):
                        x = math.cos(theta) * math.sin(phi)
                        y = math.sin(theta) * math.sin(phi)
                        z = math.cos(phi)
                        unit_vector[(x, y, z)] = []
                        phi += inc
                    theta += inc

                x_c = 0  # implement
                y_c = 0
                z_c = 0


                for i in range(2,len(linesop)):
                    val_i = list(map(float, linesip[:-1].split(" ")))
                    val_o = list(map(float, linesop[:-1].split(" ")))
                    xo, yo, zo, v1o, v2o, v3o = val_o[:6]
                    xi, yi, zi, v1i, v2i, v3i, m = val_i[:7]
                    xo -= x_c
                    yo -= y_c
                    zo -= z_c
                    cur = math.sqrt(xo ** 2 + yo ** 2 + zo ** 2)
                    xo /= cur
                    yo /= cur
                    zo /= cur

                    mind = 1000000000000000
                    for i in unit_vector:
                        tp = math.sqrt((i[0] - xo) ** 2 + (i[1] - yo) ** 2 + (i[2] - yo) ** 2)
                        if (tp < mind):
                            mind = tp
                            ar = i
                    unit_vector[ar].append((v1i, v2i, v3i, m, cur, v1o, v2o, v3o))

                theta = 0
                phi = 0
                inc = 2 * math.pi / 20
                while (theta != 2 * math.pi):
                    while (phi != 2 * math.pi):
                        x = math.cos(theta) * math.sin(phi)
                        y = math.sin(theta) * math.sin(phi)
                        z = math.cos(phi)
                        dmax = 0
                        dists = np.array([])
                        for j in unit_vector[(x, y, z)]:
                            if (j[4] > dmax):
                                dmax = j[4]
                            dists = np.append(dists, [j[4]])

                        y, x = np.histogram(dists, bins=25)
                        model = SkewedGaussianModel()
                        params = model.make_params(amplitude=10, center=0, sigma=1, gamma=0)
                        result = model.fit(y, params, x=x)
                        p1,p2 = result.params
                        if (x == 0 and y == 0 and z == 1):
                            ip = np.array([[phi, theta, ]])  # pos_x,y,z,v_x,y,z,angle_1,2
                            op = np.array([[dmax]])  # dis, dense_a,b,c
                        else:
                            ip = np.append(ip, [[]], axis=0)
                            op = np.append(op, [[]], axis=0)

                        phi += inc
                    theta += inc

                # implement normal distribution part

                # output via h5py file.


        else:
                pname = name


