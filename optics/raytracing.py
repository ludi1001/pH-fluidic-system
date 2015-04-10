import numpy as np
import scipy as sp
import scipy.optimize
import matplotlib as mpl
import matplotlib.pyplot as plt

R = 1#1.3/2
n = 1.35
shift = 0#-.75 - R
last_x = 5
old = False

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
    
    if old:
        theta_i = np.arccos(np.dot(ray_inc, normal))
        if theta_i > np.pi/2:
            theta_i = np.pi - theta_i
        print("theta_i {0}".format(theta_i/np.pi*180))
        theta_t = np.arcsin(ni * np.sin(theta_i) / nt)
        print("theta_t {0}".format(theta_t/np.pi*180))
        print("alpha {0}".format(alpha/np.pi*180))
        vec0 = ni * np.cross(ray_inc, normal)
        print("ray_inc x normal {0}".format(vec0))
        alpha_new1 = theta_t - theta_i + alpha
        vec1a = nt * np.cross([1, np.tan(alpha_new1)]/(1 + np.tan(alpha_new1)**2), normal)
        alpha_new2 = alpha - (theta_t - theta_i)
        vec1b = nt * np.cross([1, np.tan(alpha_new2)]/(1 + np.tan(alpha_new2)**2), normal)
        print("ray_trans x normal {0}, {1}".format(vec1a, vec1b))
        if np.abs(vec1a - vec0) < np.abs(vec1b - vec0):
            alpha_new = alpha_new1
        else:
            alpha_new = alpha_new2
        if np.amin([np.abs(vec1a - vec0),  np.abs(vec1b - vec0)]) > .01:
            print("warning raytracing")
        
    else: 
        ray_inc_3 = np.array([ray_inc[0], ray_inc[1], 0])
        normal_3 = np.array([normal[0], normal[1], 0])
        if np.dot(ray_inc, normal) > 0:
            normal_3 = -normal_3
        kt = ni/nt*np.cross(normal_3, np.cross(-1*normal_3, ray_inc_3)) - normal_3 * np.sqrt(1 - (ni/nt)**2 * np.linalg.norm(np.cross(normal_3, ray_inc_3))**2)
        print("{0} {1} {2}".format(kt, np.arctan2(kt[1], kt[0]), nt*np.cross([kt[0], kt[1]], normal)))
        alpha_new = np.arctan2(kt[1], kt[0])
        print("ni * ki x normal {0}".format(ni * np.cross(ray_inc, normal)))
        print("nt * kt x normal {0}".format(nt*np.cross([kt[0], kt[1]], normal)))
    return (alpha_new, x0, y0)
    
def plot_segment(x0, y0, x1, y2, alpha, color='b-'):
    beta = np.linspace(0, 1)
    x = beta * x0 + (1 - beta) * x1
    y = np.tan(alpha) * (x - x0) + y0
    plt.plot(x - shift, y, color)

def raytrace(alpha, x0, y0, color='b-'):
    #plot ray 1
    x1 = np.amin(intersect_circle(alpha, x0, y0, R))
    if x1 is None:
        x1 = last_x
        y1 = np.tan(alpha) * (x1 - x0) + y0
        plot_segment(x0, y0, x1, y1, alpha, color)
        return
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
    x3 = last_x
    y3 = np.tan(alpha2) * (x3 - x2) + y2
    plot_segment(x2, y2, x3, y3, alpha2, color)

def raytrace_angles(angles, x0, y0, color='b-'):
    for angle in angles:
        raytrace(angle/180*np.pi, x0, y0, color)
        
x0 = -2 - R
y0 = 0  

"""
# Chromatic Aberration
n = 1.33141
raytrace_angles(range(-18, 19, 4), x0, y0, 'r-')
n = 1.34235
raytrace_angles(range(-18, 19, 4), x0, y0, 'b-')
"""

"""Spherical Aberration
raytrace_angles(range(-18, 19, 2), x0, y0, 'b-')
"""

raytrace_angles(range(-4,17,2), x0, y0, 'b-')
#raytrace_angles(range(-10,11,2), x0, y0, 'r-')

"""
old = True
raytrace(3/180*np.pi, x0, y0, 'r-')
raytrace(5/180*np.pi, x0, y0, 'r-')
raytrace(10/180*np.pi, x0, y0, 'r-')
raytrace(18/180*np.pi, x0, y0, 'r-')
"""

y0 = .2
"""
raytrace(-.05, x0, y0, 'g-')
raytrace(-.01, x0, y0, 'g-')
raytrace(-.1, x0, y0, 'g-')
raytrace(-.03, x0, y0, 'g-')
raytrace(.1, x0, y0, 'g-')
raytrace(.05, x0, y0, 'g-')
raytrace(.01, x0, y0, 'g-')
raytrace(.03, x0, y0, 'g-')
raytrace(0, x0, y0, 'g-')
"""

"""
alpha = .03
raytrace(alpha, x0, 0, 'k-')
raytrace(alpha, x0, .1, 'k-')
raytrace(alpha, x0, .2, 'k-')
raytrace(alpha, x0, .3, 'k-')
raytrace(alpha, x0, .4, 'k-')
"""

"""
alpha = 0
raytrace(alpha, x0, 0, 'r-')
raytrace(alpha, x0, .1, 'r-')
raytrace(alpha, x0, .2, 'r-')
raytrace(alpha, x0, .3, 'r-')
raytrace(alpha, x0, .4, 'r-')
raytrace(alpha, x0, -.1, 'r-')
raytrace(alpha, x0, -.2, 'r-')
raytrace(alpha, x0, -.3, 'r-')
raytrace(alpha, x0, -.4, 'r-')
"""

plt.axis([-3,5,-1,1])
#plot lens
phi = np.linspace(0, 2 * np.pi)
plt.plot(R*np.cos(phi) - shift, R*np.sin(phi), 'r-')
  
plt.grid(b=True, which='major', color='k', linestyle='--')
plt.show()
