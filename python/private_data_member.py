class A(object):
    def __init__(self):
        self.__X = 3        # Mangled to self._A__X, thus __X is like a private data member  
    def __spam(self):       # Mangled to _A__spam()
        pass
    def bar(self):
        self.__spam()       # Only calls A.__spam()

class B(A):
    def __init__(self):
        A.__init__(self)
        self.__X = 37       # Mangled to self._B__X, which is distinct from __X in class A.
    def __spam(self):       # Mangled to _B__spam()
        pass

