# Disk Scheduling Algorithms
This project contains the implementations of the following disk scheduling algorithms.
1. FCFS   
2. SCAN 
3. C-SCAN

This program services a disk with 100 cylinders numbered 0 to 99. It reads a random series of 25 unique cylinder requests from a file called `input.txt` and services them according to each of the algorithms listed above. The program is passed the initial position of the disk head and writes the seek sequence and the total amount of head movement required by each algorithm in a file called `output.txt`. The two files provided in this repository serve as a sample input and the correct corresponding output.

## Compiling and Executing the Disk Scheduler
Clone this project and navigate to its working directory. In your terminal, execute the following command:
> `make disk_scheduler`

#### Assumptions and Hints
1. Assume that the *initial head position* is always 33. 
2. In SCAN algorithm, assume that the disk arm is moving toward 0 from the initial head position.
3. In C_SCAN algorithm, assume that the disk arm is moving toward 99 from the initial head position.
4. The program will produce the `output.txt` with the same format as the sample file provided here.

