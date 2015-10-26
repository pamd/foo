#!/usr/bin/python

''' 
Calculate quantile normalization, base on:
https://en.wikipedia.org/wiki/Quantile_normalization
'''

def quantile_normalize(input_matrx):
    """"This function is a wrapper that calls all the other functions to calculate
    an input matrix's quantile normalization.
    """
    row = len(input_matrix)
    col = len(input_matrix[0])
    rank_matrix, sorted_matrix = get_rank_and_sorted_matrices(input_matrix, row, col)
    row_average = get_row_average(sorted_matrix, row, col)
    return get_output_matrix(rank_matrix, row_average, row, col)

def get_rank_and_sorted_matrices(input_matrix, row , col):
    "This function calculates rank matrix and another matrix whose columns are sorted."
    rank_matrix = { }    # Implementation detail: instead of 2D list, a dictionary object is used.
    sorted_matrix = { }  # Implementation detail: instead of 2D list, a dictionary object is used.
    for c in range(0, col):
        current_col = [ ] # Save the current column into this variable.
        for r in range(0, row): 
            current_col.append(input_matrix[r][c])
        current_col.sort()
        for r in range(0, row): # Put all elements in sorted column into sorted_matrix
            sorted_matrix[r, c] = current_col[r]
        for r in range(0, row): # Set values in rank_matrix
            rank_matrix[r, c] = current_col.index(input_matrix[r][c])
    return rank_matrix, sorted_matrix

def get_row_average(sorted_matrix, row, col):
    "This function returns a list of average values in each row."
    row_average = [ ]
    for r in range(0, row):
        sum = 0
        for c in range(0, col):
            sum += sorted_matrix[r, c]
        row_average.append(sum / float(col))
    return row_average

def get_output_matrix(rank_matrix, row_average, row, col):
    "This function calculates quantile normalization based on rank matrix and row average."
    output_matrix = [ ]
    for r in range(0, row):
        new_row = [ ]
        for c in range(0, col):
            rank_index = rank_matrix[r, c]
            new_row.append(row_average[rank_index])
        output_matrix.append(new_row)
    return output_matrix

# Test cases in wikipedia:
input_matrix = [ [ 5, 4, 3 ], [ 2, 1, 4 ], [ 3, 4, 6 ], [ 4, 2, 8 ] ]
ret = quantile_normalize(input_matrix)
print ret
