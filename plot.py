import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('test.dat')
time = data[:,0]
fig, ax = plt.subplots(2, 1, sharex=True)

ax[0].plot(time, data[:,1], time, data[:,2])
ax[0].plot(time, data[:,3], time, data[:,4])
ax[0].set_title('Wave functions')
ax[0].set_ylim([-1, 1])

ax[1].plot(time, data[:,1]**2 + data[:,2]**2)
ax[1].plot(time, data[:,3]**2 + data[:,4]**2)
ax[1].set_title('Populations')
ax[1].set_xlabel('Time (a.u.)')
ax[1].set_ylim([0, 1])

plt.show()
