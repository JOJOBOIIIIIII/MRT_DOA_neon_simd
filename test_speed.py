
import subprocess
import numpy as np

# Define the path to the C binary you want to execute
binary_paths = ["./sample_cov_base","./sample_cov_ftree","./sample_cov_autovectorize_ftree","./sample_cov_autovectorize_no_ftree"]  # Replace with the actual path to your C binary

test_range= 10

average_times=[]

try:
    for bf in binary_paths:
        arr=np.zeros(test_range)
        for i in range(test_range)
            return_code = subprocess.call(bf)
            arr[i]=return_code

        average_times.append( np.mean(arr)  )



except subprocess.CalledProcessError as e:
    print(f"C binary execution failed: {e}")

for i in range(len(binary_paths)):
    print(binary_paths[i] + ":\t" + str(average_times[i]))

