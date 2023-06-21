import matplotlib.pyplot as plt
import numpy as np


data = np.fromfile('./matrix_17.06.2023.bin', dtype='uint8')
print(data.shape)
n_rows = 474
line_len = 2000
a = data.reshape((n_rows, line_len))

plt.matshow(a, cmap='gray')

plt.show()