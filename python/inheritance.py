# Base class of bank account
class Base(object):
    def __init__(self, name, balance):
        self.name = name
        self.balance = balance

    def deposit(self, amount):
        self.balance += amount

class Deriv(Base):
    def __init__(self, name, balance, interest):
        Base.__init__(self, name, balance) # Call ctor in base class
        self.interest = interest           # Set data member in derived class

    def deposit(self, amount):
        self.balance -= 1   # $1.00 transaction fee
        Base.deposit(self, amount)
        # or call super(), note that "self" is not a parameter of deposit() any more:
        # super(Base, self).deposit(amount) 

