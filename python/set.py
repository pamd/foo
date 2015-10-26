#!/usr/bin/python

# Set: each element must be unique.
s = set([1, 2, 2, 3, 4]) # s only includes 1, 2, 3, 4

a = s1 | s2 # union
b = s1 & s2 # intersection
c = s1 - s2 # set difference (items in s1, but not in s2)
d = s1 ^ s2 # Symmetric difference (items in s1 or s2, but not both)

