#!/usr/bin/python

class Stack(object): # Stack is derived from object
    def __init__(self):  # ctor
        self.stack = [ ]

    def push(self, object):
        self.stack.append(object)

    def pop(self):
        return self.stack.pop()

    def length(self):
        return len(self.stack)

# Usage:
s = Stack() # create an object of Stack type
del s       # destroy the object
