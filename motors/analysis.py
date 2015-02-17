import numpy as np
import scipy as sp
import scipy.optimize
import matplotlib as mpl
import matplotlib.pyplot as plt

x = np.arange(10,60,10)
y = np.asarray([8.72, 16.98, 24.52, 34.82, 44.16])
xrange = np.linspace(0,50)
p = np.polyfit(x,y,1)
print(p)
plt.plot(x,y,'bo-')
a = plt.plot(xrange,np.polyval(p,xrange),'r-')
plt.grid(b=True, which='major', color='k', linestyle='--')
plt.xlabel('Time (s)')
plt.ylabel('Volume (mL)')
plt.title('Motor 1')
plt.show()