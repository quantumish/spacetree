import csv

lines = open("/home/quantumish/Downloads/impact.0003", "r").readlines()

x,y,z=[],[],[]
for l in lines[2:]:
    vals = list(map(float, l[:-1].split(" ")))
    x.append(vals[0])
    y.append(vals[1])
    z.append(vals[2])

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import proj3d

fig = plt.figure(figsize=(8, 8))
ax = fig.add_subplot(111, projection='3d')

ax.scatter(x,y,z)
plt.axis("equal")
plt.show()

# import numpy as np


# from lmfit.models import SkewedGaussianModel
# import random
# # dists, vels = zip(*[ (10, 3), (25, 2), (26, 4), (26, 2), (28, 5), (28, 4), (78, 1)])
# dists = [np.random.normal(0, 1) for i in range(1000)]

# y, x = np.histogram(dists, bins=100)
# x = x[:-1]

# model = SkewedGaussianModel()
# params = model.make_params(amplitude=10, center=0, sigma=1, gamma=0)
# result = model.fit(y, params, x=x)

# print(result.fit_report)
# help(result)
# plt.hist(dists, bins=100)
# plt.plot(x, result.best_fit)
# plt.show()
