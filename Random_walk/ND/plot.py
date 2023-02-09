import sys
import numpy as np
import matplotlib.pyplot as plt

if __name__ == "__main__":
    try:
        Dim = str(sys.argv[-1])
    except:
        Dim = '?'
    data = np.genfromtxt("mean_distance.txt", delimiter="")
    x = data[:,0]
    y = data[:,1]
    plt.plot(x, y)
    plt.xlabel('Steps')
    plt.ylabel('Expectation value of distance')
    plt.savefig('{}D_random_walk.png'.format(Dim), dpi=500)
 

