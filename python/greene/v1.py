#!/usr/bin/python

''' 
Quantile normalization, base on:
https://en.wikipedia.org/wiki/Quantile_normalization
'''

#def quantitle_normalize(arr):
 
input_matrix = [ [ 5, 4, 3 ], [ 2, 1, 4 ], [ 3, 4, 6 ], [ 4, 2, 8 ] ]

row = len(input_matrix)
col = len(input_matrix[0])
#rank_matrix = [[0] * row] * col
rank_matrix = [ ]
sorted_matrix = [ ]
for c in range(0, col):
    #print "column: ", c
    current_col = []
    for r in range(0, row):
        current_col.append(input_matrix[r][c])
    current_col.sort()
    sorted_matrix.append(current_col)
    col_rank = []
    for r in range(0, row):
        col_rank.append(current_col.index(input_matrix[r][c]))
    rank_matrix.append(col_rank)


#print input_matrix
#print rank_matrix
#print sorted_matrix

row_average = [ ]

for r in range(0, row):
    sum = 0
    for c in range(0, col):
        sum += sorted_matrix[c][r]
    row_average.append(sum / float(col))

#index2average = { }

output_matrix = [ ]
for r in range(0, row):
    new_row = [ ]
    for c in range(0, col):
        rank_index = rank_matrix[c][r]
        new_row.append(row_average[rank_index])
    output_matrix.append(new_row)

#print output_matrix


