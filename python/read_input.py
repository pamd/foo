#!/usr/bin/python

#x = raw_input("input: ") # x is string here
#print int(x) + 10 # Convert x into integer explicitly

f = open("foo.txt")
line = f.readline()
while line:
    print line, # Trailing ',' omits newline character
    line = f.readline()
f.close()

# More compact version:
for line in open("foo.txt"):
    print line, # Don't forget the trailing ','


