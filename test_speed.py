
import subprocess
import numpy as np

# Define the path to the C binary you want to execute
binary_paths = ["./sample_cov_base","./sample_cov_ftree","./sample_cov_autovectorize_ftree","./sample_cov_autovectorize_no_ftree"]  # Replace with the actual path to your C binary

test_range= 1000

average_times=[]

i = 0
try:
    for bf in binary_paths:
        print("Computing " + "binary_paths[i]" + f" for {test_range} samples" + f"({i+1} out of {len(binary_paths)})")
        arr=np.zeros(test_range)
        for i in range(test_range):
            return_code = subprocess.call(bf)
            arr[i]=return_code
        
        av=np.mean(arr)
        average_times.append( av )
        i+=1


except subprocess.CalledProcessError as e:
    print(f"C binary execution failed: {e}")

for i in range(len(binary_paths)):
    print(binary_paths[i] + ":\t" + str(average_times[i]))

