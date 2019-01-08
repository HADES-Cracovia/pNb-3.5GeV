import subprocess
import time
import os


print("Copy and hadd files from shorter lists")

max_value=15

for k in range (13,max_value+1):
    input_name="x{:02d}".format(k)#+"hadron"
    output_name="hadron{:02d}.root".format(k)
    print("file name: {}".format(input_name))
    argument_list=""

    with open(input_name) as f:
        content = f.readlines()
        content = [x.strip() for x in content]

    argument_list=argument_list+" ".join(content)
    bashCommand="hadd -f "+output_name+" "+argument_list
    #print(bashCommand)

    os.system(bashCommand)
