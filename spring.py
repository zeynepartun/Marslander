# uncomment the next line if running in a notebook
# %matplotlib inline
import numpy as np
import matplotlib.pyplot as plt
import math
import time

start = time.time()

# mass, spring constant, initial position and velocity
m = 1
k = 1
x = 0
v = 1
x_verlet = x

# simulation time, timestep and time
t_max = 100
dt = 0.001
t_array = np.arange(0, t_max, dt)
xmin1 = -v*dt + x

# initialise empty lists to record trajectories
x_list = []
v_list = []
x_true_list = []
x_verlet_list = []


# Euler integration
for t in t_array:

    # append current state to trajectories
    x_list.append(x)
    v_list.append(v)
    x_true_list.append(math.sin(t))
    x_verlet_list.append(x_verlet)


    # calculate new position and velocity
    a = -k * x / m
    x = x + dt * v
    v = v + dt * a
    x_verlet_old = x_verlet
    a_verlet = -k * x_verlet / m
    x_verlet = 2*(x_verlet) - xmin1 + (dt**2)* a_verlet
    xmin1 = x_verlet_old

# convert trajectory lists into arrays, so they can be sliced (useful for Assignment 2)
x_array = np.array(x_list)
v_array = np.array(v_list)
x_true_array = np.array(x_true_list)
x_verlet_array = np.array(x_verlet_list)


# #£ plot the position-time graph
# plt.figure(1)
# plt.clf()
# plt.xlabel('time (s)')
# plt.grid()
# #£ plt.plot(t_array, x_array, label='x (m)')
# #£ plt.plot(t_array, v_array, label='v (m/s)')
# plt.plot(t_array, x_true_array, label='x_true (m)')
# plt.plot(t_array, x_verlet_array, label='x_verlet (m)')
# plt.legend()
# plt.show()

# printing to a file
f = open('trajectories_python.txt', 'w')

txt = ''
for i in np.arange(0, len(t_array)):
    txt += "{} {} {}\n".format(t_array[i], x_array[i], v_array[i])
f.write(txt)
f.close()

end = time.time()
print(end - start)
