class Circle(object):
     def __init__(self,radius):
         self.radius = radius

     # Some additional properties of Circles
     @property
     def area(self):
         return math.pi*self.radius**2
     @property
     def perimeter(self):
         return 2*math.pi*self.radius

c = Circle(4.0)
c.radius # 4.0
c.area   # 50.26548245743669
c.perimeter # 25.132741228718345

c.area = 2 # Syntax error, because area is a property in Circle
# Error message:
# Traceback (most recent call last):
#   File "<stdin>", line 1, in <module>
# AttributeError: can't set attribute
