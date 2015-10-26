#!/usr/bin/python

# Lambda is like a function object:
a = lambda x,y : x+y
r = a(2,3)  # r is 5

# Another example:
input_list = range(1, 100)
output_list = filter(lambda x: x % 2 == 0, input_list)
print output_list

# Example #3:
names = ["xyz", "ABC", "abd", "weR" ]
names.sort(key=lambda n: n.lower()) # sort strings by lowercase
