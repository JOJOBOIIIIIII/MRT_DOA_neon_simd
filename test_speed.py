
import subprocess
import numpy as np
import sys

#Erase file content
with open("times.txt","w") as file:
    file.write("")

# Define the path to the C binary you want to execute
binary_paths = ["./sample_cov_base","./sample_cov_ftree","./sample_cov_autovectorize_ftree","./sample_cov_autovectorize_no_ftree"]  # Replace with the actual path to your C binary

if (len(sys.argv) != 1+1):
    print("Need to pass argument")
    exit()
test_range=int(sys.argv[1])


average_times=[]
index = 0
try:
    for bf in binary_paths:
        print("Computing " + f"{binary_paths[index]}" + f" for {test_range} samples... " + f"({index+1} out of {len(binary_paths)})")
        arr=np.zeros(test_range)
        for i in range(test_range):
            subprocess.run([bf,"some_arg"])
            with open("times.txt", "r") as file:
                for line in file:
                    arr[i]=float(line.strip())

        av=np.mean(arr)
        average_times.append( av )
        index+=1
        with open("times.txt","w") as file:
            file.write("")




except subprocess.CalledProcessError as e:
    print(f"C binary execution failed: {e}")

for i in range(len(binary_paths)):
    print(binary_paths[i] + ":\t" + str(average_times[i]))

min_time=100
min_index=None
for i,av_time in enumerate(average_times):
    if (av_time < min_time and (i != 0) ):
        min_time=av_time
        min_index=i
base_time = average_times[0]

print(f"Fastest is {binary_paths[min_index]}, {base_time-min_time} s faster than base, or {100 - (100 * min_time/base_time)} % faster")
