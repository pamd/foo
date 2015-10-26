
# In Python, numeric types and strings are all immutable:
#
# http://stackoverflow.com/questions/2797114/python-references
# http://python.net/~goodger/projects/pycon/2007/idiomatic/handout.html#other-languages-have-variables
# 
# So when we write:
foo_int = 1
# foo_int is actually a "label" that is attached to a numeric object whose value is 1.
# If we then write: 
foo_int += 1
# Then the relationship beteen foo_int and the object whose value is 1 is removed, and
# foo_int is now attached to another object whose value is 2.
# This is why 
id(foo_int)
# is different before and after "foo_int += 1" statement, because
# the object that foo_int is attached to has been changed.
