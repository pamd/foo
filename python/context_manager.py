# Thanks to context manager, we do not need to call f.close() at the end any more:
with open("out.txt", "w") as f:
    f.write("output line blah blah")

