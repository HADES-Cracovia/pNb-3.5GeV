import subprocess
print("Send all jobs")
import time
import os

bashCommand = "squeue -u knowakow|wc -l"
os.system(bashCommand)
os.system(export lines)
jobs=100
os.system(bashCommand)>>jobs
print("jobs: ",jobs)
if jobs==0:
    print("no jobs in queue")
