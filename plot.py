# Source - https://stackoverflow.com/a/39401259
# Posted by kilojoules, modified by community. See post 'Timeline' for change history
# Retrieved 2026-04-08, License - CC BY-SA 4.0

import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import griddata

def heatmap2d(arr: np.ndarray):
    plt.imshow(arr, cmap='viridis')
    plt.colorbar()
    plt.show()

array = np.loadtxt(open('map.txt', "rb"), delimiter=",", skiprows=0)
heatmap2d(array)
