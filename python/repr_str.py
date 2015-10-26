
# repr() is implemented by class_name.__repr__(self), which is used by eval() to change
# the representation string back to its original format.
a = [2,3,4,5]      # Create a list
s = repr(a)        # s = '[2, 3, 4, 5]'
b = eval(s)        # Turns s back into a list

# str() is implemented by class_name.__str__(self), which is used by:
print object_name
# or:
print str(object_name)
