#!/usr/bin/python

# Suppose we have a "dhu.py" file that defines function foo()

import dhu
dhu.foo()

import dhu as dongbo # Give dhu an alis of "dongbo"
dongbo.foo()

# Import specific definitions into current namespace
from dhu import foo
foo() # Note that the prefix "dhu." is not needed

# Import everything in dhu into current namespace
from dhu import *
foo() # Prefix of "dhu." is not needed

