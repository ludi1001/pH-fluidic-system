import numpy as np
import scipy as sp
import scipy.optimize
import matplotlib as mpl
import matplotlib.pyplot as plt

#40 mL, 12 drops
measurements = (#(6.03, (310.5405405405405, 618.5121951219512, 165.1)),
                #(6.03, (318.9142857142857, 628.1875, 174.88888888888889)),
                #(7.7, (320.6666666666667, 449.52941176470586, 122.15384615384616)),
                (6.03, (316.02222222222224, 701.7931034482758, 130.61818181818182)),
                (6.03, (310.35714285714283, 699.2333333333333, 123.86486486486487)),
                (6.03, (317.3225806451613, 697.7894736842105, 121.72222222222223)),
                (6.27, (316.4222222222222, 564.6530612244898, 105.28947368421052)),
                (6.27, (315.1, 570.0142857142857, 122.45454545454545)),
                (6.49, (301.1489361702128, 581.9152542372881, 112.37037037037037)),
                (6.49, (312.7111111111111, 612.9230769230769, 125.36363636363636)))

format = ['ro', 'go', 'bo']
maxval = [0,0,0]
for i in range(3):
    #plt.figure(i+1)
    pH = []
    val = []
    for m, vals in measurements:
        pH.append(m)
        val.append(vals[i])
    pH = np.array(pH)
    val = np.array(val)
    maxval[i] = np.max(val)
    val /= np.max(val)
    plt.plot(pH + i/20.0, val, format[i])
for m, vals in measurements:
    x = np.array([m, m + 1/20.0, m + 2/20.0])
    y = np.array(vals)
    for i in range(3):
        y[i] /= maxval[i]
    plt.plot(x, y, 'k-')
plt.show()