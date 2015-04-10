import numpy as np
import scipy as sp
import scipy.optimize
import matplotlib as mpl
import matplotlib.pyplot as plt

#40 mL, 6.03 pH
measurements = ((9, (319.40277777777777, 754.7966101694915, 265.2045454545454)),
                (12, (316.02222222222224, 701.7931034482758, 130.61818181818182)),
                (15, (296.44615384615383, 573.7752808988764, 68.59615384615384)))

format = ['r-o', 'g-o', 'b-o']
for i in range(3):
    #plt.figure(i+1)
    pH = []
    val = []
    for m, vals in measurements:
        pH.append(m)
        val.append(vals[i])
    pH = np.array(pH)
    val = np.array(val)
    val /= np.max(val)
    plt.plot(pH, val, format[i])
plt.xlabel('Drops of phenol red')
plt.ylabel('Normalized readings')
plt.show()