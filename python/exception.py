#!/usr/bin/python

try:
    f = open("file.txt", "r")
except IOError as e:
    print e

# Throw an exception
raise RuntimeError("Computer crashes!")
