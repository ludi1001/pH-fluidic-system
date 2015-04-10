import numpy as np
import scipy as sp
import scipy.optimize
import matplotlib as mpl
import matplotlib.pyplot as plt

water = (573.9795918367347, 726.8571428571429, 759.08) #714.625, 734.5694444444445)
measurements = ((6.0,  (576.4102564102565, 511.57575757575756, 287.125)),
                (6.5,  (584.25,            548.7,              310.7368421052632)),
                (6.5,  (587.25,            541.2333333333333,  288.59375)),
                (6.5,  (584.7647058823529, 393.5416666666667,  137.21428571428572)),
                (7.0,  (567.6037735849056, 402.30645161290323, 295.92105263157896)),
                (7.18, (573.5217391304348, 437.95,             297.8536585365854)),
                (7.78, (566.6224489795918, 397.16129032258067, 237.3409090909091)))
 
for m in measurements:
    pH = m[0]
    vals = m[1]
    ratio = (water[1] - vals[1])/(water[2] - vals[2])
    tgb = vals[1]/vals[2]
    print("pH: {0}, AbsG: {absG}, AbsB: {absB}, AbsG/AbsB: {1}, Tg/Tb: {2}".format(pH, ratio, tgb, absG=water[1]-vals[1], absB=water[2]-vals[2]))
   