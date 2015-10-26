# Static mathod
class Foo(object):
     @staticmethod
     def add(x,y):
         return x + y

# Call static method:
x = Foo.add(3,4)  # x  = 7


# Class method
class Times(object):
    factor = 1 # static data member
    @classmethod
    def mul(cls,x): # NOte that the parameter "cls" is not available in static method 
        return cls.factor*x

class TwoTimes(Times): # TwoTimes is derived from Times
    factor = 2

# Call class method from derived class
x = TwoTimes.mul(4)      # x = 2 * 4 = 8
