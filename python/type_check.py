#
# isinstanceof(object_name, class_names): is object_name (oneof the) classname(s) type?
# Note that classnames can be a tuple that includes more than one class.
s = [1, 2, 3]
isinstance(s, (list, tuple))

# issubclass(class1, class2): is class1 a subclass of class2?
# Note that class2 can be a tuple that includes more than one class.
# issubclass(A, A) returns True.

# type(obj): Returns type of the input object
type(3) # returns <type 'int'>, NOT 'int'.

str = "123"
my_int = int(str)  # convert into integer type
str2 = str(my_int) # convert back into string
str3 = bin(my_int) # convert to a string of binary representation

