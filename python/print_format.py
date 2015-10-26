#!/usr/bin/python

year = 2015
amount = 123.456

print "%3d %0.2f" % (year, amount)
#print ("%3d %0.2f" % (year, amount)) # Python 3

# or:
print format(year, "3d"), format(amount, "0.2f")



