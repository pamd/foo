#!/usr.bin/python
f = open("out.txt", "w") # open file for writing
year = 2000
principle = 1000
rate = 0.03
while year <= 2015:
    principle = principle * (1 + rate)
    print >>f, "%3d %0.2f" % (year, principle) # python 2
    #print("%3d %0.2f" % (year, principle), file=f) # python 3
    #f.write("%3d %0.2f\n" % (year, principle)) # another alternative
    year += 1
f.close() # Don't forget to close the file
