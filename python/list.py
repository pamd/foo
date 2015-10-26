#!/usr/bin/python

# List: [ ]

names = [ "Dave", "John", "Mary" ]
names.append("dhu") # Add "dhu" at the end
names.insert(2, "helen") # insert "helen" between "John" and "Mary"
names.sort() # sort list
names.remove("Dave") # Remove all occurrences of "Dave"

# names[1: ]
# names[2:4]

# Number of elements in list:
len(names)
# len() can be also used on string, set, tuple or dictionary

names2 = [ ] # empty list #1
names3 = list() #empty list #2

# Create a 2-D list (matrix) that has 3 rows and 4 columns, and set all cells to 0:
matrix1 = [ [ 0 for i in range(4) ] for i in range(3) ]
# DO NOT use:
# matrix2 = [ [0] * 4] ] * 3
# Because although matrix2 is:
# [ [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0] ]
# the 3 rows are references to the same object [ 0, 0, 0, 0 ].
# So when we set matrix[0][1] = 9, matrix2 becomes:
# [ [0, 9, 0, 0], [0, 9, 0, 0], [0, 9, 0, 0] ]
#
# Alternatively, we can use dictionary to simulate a 2-D matrix:
mat3 = { }
mat3[0, 1] = 99
# Here "0, 1" is actually the key in dictionary, and the corresponding value is 99,
# so we can NOT write: mat[0][1] = 99
