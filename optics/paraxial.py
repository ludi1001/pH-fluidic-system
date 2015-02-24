import numpy as np
import scipy as sp
import scipy.optimize
import matplotlib as mpl
import matplotlib.pyplot as plt

n = 1.35
R1 = 5
R2 = -R1
d = 2*R1

f_inv = (n - 1) * (1.0/R1 - 1.0/R2 + 1.0 * (n - 1) * d/(n * R1 * R2))
f = 1/f_inv
print("Effective focal length: {0}".format(f))

h1 = -f * (n - 1) * d / (R2 * n)
h2 = -f * (n - 1) * d / (R1 * n)
print("Front principal plane: {0}".format(h1))
print("Back principal plane: {0}".format(h2))
d0 = np.linspace(14, 21)
s0 = d0 + h1
s1 = (f * s0) /  (s0 - f)
d1 = s1 + h2
plt.plot(d0, d1, 'r-o')
plt.show()