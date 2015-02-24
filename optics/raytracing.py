import numpy as np
import scipy as sp
import scipy.optimize
import matplotlib as mpl
import matplotlib.pyplot as plt

R = 5
n = 1.35

def intersect_circle(alpha, x0, y0, R):
    a = 1 + np.tan(alpha)**2
    b = 2*np.tan(alpha)*(y0 - x0*np.tan(alpha))
    c = x0**2 * np.tan(alpha)**2 - 2*x0*y0*np.tan(alpha) + y0**2 - R**2

    discr = b**2 - 4*a*c
    if discr >= 0:
        xa = (-b + np.sqrt(discr))/(2 * a)
        xb = (-b - np.sqrt(discr))/(2 * a)
        return [xa, xb]
    else: 
        return None
        
def refract(alpha, x0, y0, ni, nt):
    ray_inc = np.array([1, np.tan(alpha)])
    ray_inc /= np.linalg.norm(ray_inc)
    normal = np.array([x0, y0])
    normal /= np.linalg.norm(normal)
    print(ray_inc)
    print(normal)
    theta_i = np.arccos(np.dot(ray_inc, normal))
    if theta_i > np.pi/2:
        theta_i = np.pi - theta_i
    print("theta_i {0}".format(theta_i/np.pi*180))
    theta_t = np.arcsin(ni * np.sin(theta_i) / nt)
    print("theta_t {0}".format(theta_t/np.pi*180))
    print("alpha {0}".format(alpha/np.pi*180))
    alpha_new = theta_t - theta_i + alpha
    if alpha < 0:
        alpha_new = alpha - (theta_t - theta_i)
    return (alpha_new, x0, y0)
    
def plot_segment(x0, y0, x1, y2, alpha, color='b-'):
    beta = np.linspace(0, 1)
    x = beta * x0 + (1 - beta) * x1
    y = np.tan(alpha) * (x - x0) + y0
    plt.plot(x, y, color)

def raytrace(alpha, x0, y0, color='b-'):
    #plot ray 1
    x1 = np.amin(intersect_circle(alpha, x0, y0, R))
    y1 = np.tan(alpha) * (x1 - x0) + y0
    plot_segment(x0, y0, x1, y1, alpha, color)

    #plot ray 2
    alpha1, *c = refract(alpha, x1, y1, 1, n)
    print(alpha1)
    x2 = np.amax(intersect_circle(alpha1, x1, y1, R))
    y2 = np.tan(alpha1) * (x2 - x1) + y1
    plot_segment(x1, y1, x2, y2, alpha1, color)

    #plot ray 3
    alpha2, *c = refract(alpha1, x2, y2, n, 1)
    print(alpha2)
    x3 = 20
    y3 = np.tan(alpha2) * (x3 - x2) + y2
    plot_segment(x2, y2, x3, y3, alpha2, color)


x0 = -20
y0 = 0  

"""
#raytrace(.2, x0, y0)
raytrace(.05, x0, y0)
raytrace(.01, x0, y0)
raytrace(.1, x0, y0)
raytrace(.02, x0, y0)
raytrace(.03, x0, y0)
"""

y0 = .2
"""
raytrace(-.05, x0, y0, 'g-')
raytrace(-.01, x0, y0, 'g-')
#raytrace(-.1, x0, y0, 'g-')
raytrace(-.02, x0, y0, 'g-')
raytrace(-.03, x0, y0, 'g-')
raytrace(.05, x0, y0, 'g-')
raytrace(.01, x0, y0, 'g-')
#raytrace(.1, x0, y0, 'g-')
raytrace(.02, x0, y0, 'g-')
raytrace(.03, x0, y0, 'g-')
raytrace(0, x0, y0, 'g-')
"""

alpha = .03
raytrace(alpha, x0, 0, 'k-')
raytrace(alpha, x0, .1, 'k-')
raytrace(alpha, x0, .2, 'k-')
raytrace(alpha, x0, .3, 'k-')
raytrace(alpha, x0, .4, 'k-')

alpha = -.03
raytrace(alpha, x0, 0, 'k-')
raytrace(alpha, x0, .1, 'k-')
raytrace(alpha, x0, .2, 'k-')
raytrace(alpha, x0, .3, 'k-')
raytrace(alpha, x0, .4, 'k-')


#plot lens
phi = np.linspace(0, 2 * np.pi)
plt.plot(R*np.cos(phi), R*np.sin(phi), 'r-')
  
plt.grid(b=True, which='major', color='k', linestyle='--')
plt.show()
