#!/usr/bin/python

#primes = [ ]
#for i in range(0, 100):
#    primes.append(True)

primes = [True] * 100 # Create an array of boolean and set all elements to "True" 

for i in range(2, 100):
    if primes[i]:
        for j in range(i * 2, 100, i):
            primes[j] = False

for i in range(2, 100):
    if primes[i]:
        print i

