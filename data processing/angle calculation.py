
import math
import os
import h5py
import numpy as np
from lmfit.models import SkewedGaussianModel
unit_vector = {}
data_dir = "/Users/chenyiyu/Downloads/csv/"
cnt = 1

for root, dirs, files in os.walk(data_dir, topdown=True):
    for name in files:
        if (name[7:].isnumeric()):
            if (int(name[7:]) == 0):
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

                for i in range(2, len(linesop)):
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
                        p1, p2 = result.params
                        if (x == 0 and y == 0 and z == 1):  # pos_x,y,z,v_x,y,z,angle_1,2
                            op = np.array([[dmax, p1, p2]])
                            ip = np.array([theta, phi, M1, M2, collision_angle, collision_velocity])# dis, dense_a,b,c
                        else:
                            op = np.append(op, [[dmax, p1, p2]], axis=0)
                            ip = np.append(ip, [[theta, phi, M1, M2, collision_angle, collision_velocity]], axis=0)

                        phi += inc
                    theta += inc
                f.create_dataset("input",ip)
                f.create_dataset("output",op)
                f.close()
            else:
                pname = name
        elif(name=="setup.txt"):
            f = h5py.File(f"dataset{cnt}","w")
            D = os.path.join(root, name)
            lines = open(D, "r").readlines()
            for line in lines:
                if 'vel_vesc_touching_ball' in line:
                    collision_velocity = int(line[line.find(":")+1:])
                elif "impact_angle_touching_ball" in line:
                    collision_angle = int(line[line.find(":")+1:])
                elif "M_targ" in line:
                    M1 = int(line[line.find(":")+1:])
                elif "M_proj" in line:
                    M2 = int(line[line.find(":")+1:])
                else:
                    continue

