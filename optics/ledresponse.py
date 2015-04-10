import numpy as np
import scipy as sp
import scipy.optimize
import matplotlib as mpl
import matplotlib.pyplot as plt

green_current = np.array([19, 26, 34])
green_vals = np.array([305, 355, 410]) - 60

blue_current = np.array([12, 17, 24, 31])
blue_vals = np.array([155, 182, 217, 256]) - 50

plt.figure(1)
p = np.polyfit(blue_current,blue_vals,1)
print(p)
xrange = np.linspace(blue_current[0], blue_current[-1])
plt.plot(xrange,np.polyval(p,xrange),'k--')
plt.plot(blue_current, blue_vals, 'b-o')
plt.xlabel("Current (mA)")
plt.ylabel("Measurement")
plt.title("Blue LED Response")

plt.figure(2)
xrange = np.linspace(green_current[0], green_current[-1])
p = np.polyfit(green_current,green_vals,1)
print(p)
plt.plot(xrange,np.polyval(p,xrange),'k--')
plt.plot(green_current, green_vals, 'b-o')
plt.xlabel("Current (mA)")
plt.ylabel("Measurement")
plt.title("Green LED Response")
plt.show()