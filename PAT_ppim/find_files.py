directory="/lustre/nyx/hades/dst/sep08_BT/gen2/" #oryginal data directory
fname="zepsute.list" #file with list of missing files
newfile="zepsute_out.list"

import subprocess
import time
import shlex
import os

print("Find files from list:")
print(fname)
print("in directory:")
print(directory)

f2=open(newfile,"w")

with open(fname) as f:
    content = f.readlines()
content = [x.strip() for x in content]

for k in content:   #take every name from vector content
    bashCommand = "find "+directory+" -name "+k
    print(bashCommand)
    args=shlex.split(bashCommand)
    print(args)
    #break
    subprocess.call(args,stdout=f2)
    #os.system(bashCommand)>>f2
    #break
