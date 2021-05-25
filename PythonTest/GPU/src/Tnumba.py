from numba import cuda
import numpy as np

@cuda.jit
def my_kernal(io_array):
    ''' 
    kernal code
    '''
    pos=cuda.grid(1)
    if pos<io_array.size:
        io_array[pos]*=2

data=np.linspace(0,10,256)
thread_per_block=256
block_per_grid=int(data.shape[0]/thread_per_block)
print(data)
my_kernal[block_per_grid,thread_per_block](data)
print(data)