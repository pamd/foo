#!/bin/bash

# Compare output of DijkstraSP and BellmanFordSP based on same input file

for i in 0 1 2 3 4 5 6 7; do
    echo "source vertex: $i";
    java BellmanFordSP tinyEWDn.txt $i > bell$i.txt
    java DijkstraSP    tinyEWDn.txt $i > dijk$i.txt
    diff dijk$i.txt bell$i.txt
    echo
done

# dhu conclusion: The outputs from the two algorithms are exactly same.