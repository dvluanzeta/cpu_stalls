import matplotlib.pyplot as plt
import numpy as np
import subprocess

def exec(nsize, nsteps):
    s = subprocess.check_output(["x64\\Release\\TestMemAccess.exe", str(nsize), str(nsteps)]).decode('utf-8')
    return float(s)

nsize_1 = np.arange(100, 1000, 100)
nsize_2 = np.arange(1000, 3000, 200)
nsize_3 = np.arange(3000, 8000, 500)
nsize_4 = np.arange(8000, 16000, 1000)
nsteps_1 = np.zeros_like(nsize_1) + 1000
nsteps_2 = np.zeros_like(nsize_2) + 200
nsteps_3 = np.zeros_like(nsize_3) + 150
nsteps_4 = np.zeros_like(nsize_4) + 100

matrix_size = np.concatenate([nsize_1, nsize_2, nsize_3, nsize_4])
repeats = np.concatenate([nsteps_1, nsteps_2, nsteps_3, nsteps_4])
ratios = np.zeros_like(matrix_size, dtype=np.float64)

for i in range(len(matrix_size)):
    print("- nsize: {}, nsteps: {} ->".format(matrix_size[i], repeats[i]), end =" ")
    ratios[i] = exec(matrix_size[i], repeats[i])
    print("ratio: {}".format(ratios[i]))

plt.plot(matrix_size, ratios)
plt.show()