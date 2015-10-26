
# The try statement also supports an else clause, which must follow the last except clause.
# This code is executed if the code in the try block doesn’t raise an exception. 

try:
   f = open('foo', 'r')
except IOError as e:
   error_log.write('Unable to open foo : %s\n' % e)
else:
   data = f.read()
   f.close()

# "finally" statement defines a cleanup action for code contained in a try block:

f = open('foo','r')
try:
   # Do some stuff
finally:
   f.close()
   # File closed regardless of what happened

# "finally" clause isn’t used to catch errors. Rather, it’s used to provide code that must
# always be executed, regardless of whether an error occurs.
# If no exception is raised, the code in "finally" clause is executed immediately after
# the code in the try block.
# If an exception occurs, control is first passed to the first statement of "finally" clause.
# After this code has executed, the exception is re-raised to be caught by another exception handler.
