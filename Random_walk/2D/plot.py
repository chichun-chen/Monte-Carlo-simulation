import numpy as np
import matplotlib.pyplot as plt

if __name__ == "__main__":
    data = np.genfromtxt("mean_distance.txt", delimiter="")
    x = data[:,0]
    y = data[:,1]
    plt.plot(x, y)
    plt.xlabel('Steps')
    plt.ylabel('Expectation value of distance')
    plt.savefig('2D_random_walk.png', dpi=500)
 

