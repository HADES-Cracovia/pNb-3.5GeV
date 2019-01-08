#directory="/lustre/nyx/hades/user/iciepal/Lambda1520_ic/" #oryginal data directory
#fname="list_allfiles" #file with list of expected files
import subprocess
print("run all jobs")
import time
import os

#with open(fname) as f:
 #   content = f.readlines()
#content = [x.strip() for x in content]

os.system("scancel -u knowakow")
print("scancel -u knowakow")

print("./sendScript_SL_a.sh")
os.system("./sendScript_SL_a.sh")

#for k in content:   #take every name from vector content
#   print('try to run files from list{}'.format(k))
while(1 != int(subprocess.check_output('squeue -u knowakow | wc -l',shell=True,))):
    #print('waiting to finish list: {}'.format(k))
    print('still {} jobs to the end'.format(subprocess.check_output('squeue -u knowakow | wc -l',shell=True,)))
    time.sleep(30)


print("./sendScript_SL_b.sh")
os.system("./sendScript_SL_b.sh")

#for k in content:   #take every name from vector content
#   print('try to run files from list{}'.format(k))
while(1 != int(subprocess.check_output('squeue -u knowakow | wc -l',shell=True,))):
    #print('waiting to finish list: {}'.format(k))
    print('still {} jobs to the end'.format(subprocess.check_output('squeue -u knowakow | wc -l',shell=True,)))
    time.sleep(30)


print("./sendScript_SL_c.sh")
os.system("./sendScript_SL_c.sh")

#for k in content:   #take every name from vector content
#   print('try to run files from list{}'.format(k))
while(1 != int(subprocess.check_output('squeue -u knowakow | wc -l',shell=True,))):
    #print('waiting to finish list: {}'.format(k))
    print('still {} jobs to the end'.format(subprocess.check_output('squeue -u knowakow | wc -l',shell=True,)))
    time.sleep(30)


print("./sendScript_SL_d.sh")
os.system("./sendScript_SL_d.sh")

#for k in content:   #take every name from vector content
#   print('try to run files from list{}'.format(k))
while(1 != int(subprocess.check_output('squeue -u knowakow | wc -l',shell=True,))):
    #print('waiting to finish list: {}'.format(k))
    print('still {} jobs to the end'.format(subprocess.check_output('squeue -u knowakow | wc -l',shell=True,)))
    time.sleep(30)

     
