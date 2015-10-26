#!/usr/bin/python

# Dictionary: { }
google = {   
    "name"  : "GOOG",
    "shares": 100,
    "price" : 490.13
}

google.keys()   # All keys
google.values() # All values
google.items()  # All keys and values
 
# Empty dictionary
empty_dict = {} # or: empty_dict = dict()

# Get list of keys in dict:
keys = list(google) # ["name", "shares", "price"]

# Number of pairs in dict:
len(google)  # return 3

# Remove an element from dict
del google["price"]
