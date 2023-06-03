import matplotlib.pyplot as plt
import numpy as np

data = np.fromfile('./debug_strip_data.bin', dtype='uint8')

line_len = int(2000)
n_rows = int(474)
data = data.reshape((n_rows, line_len))

plt.matshow(data, cmap='gray')

plt.show()