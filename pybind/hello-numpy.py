import numpy as np
 
arr = np.array([1, 2, 3])
print("Array with Rank 1: \n",arr)
 
arr = np.array([[1, 2, 3],
                [4, 5, 6]])
print("Array with Rank 2: \n", arr)
 
arr = np.array((1, 3, 2))
print("\nArray created using "
      "passed tuple:\n", arr)