from abc import ABCMeta, abstractmethod

class Shape(object):
	__metaclass__ = ABCMeta
	
	@abstractmethod
	def area(self):
		pass
		
	@abstractmethod
	def display(self):
		pass
		
	@abstractmethod
	def __str__(self):
		pass
		
	@abstractmethod
	def __cmp__(self, other):
		pass
		
		
class Circle(Shape):
	
	def __init__(self, radius):
		self.__radius = radius
		self.__area = 3.14 * (radius ** 2)
		
	def area(self):
		return self.__area
		
	def display(self):
		print "Circle area = " + str(self.__area)
		
	def __str__(self):
		return "Circle area = " + str(self.__area)
		
	def __cmp__(self, other):
		if self.area() > other.area():
			return 1
		elif self.area() < other.area():
			return -1
		else:
			return 0
		

class Triangle(Shape):
	
	def __init__(self, height, width):
		self.__height = height
		self.__width = width
		self.__area = (height * width) / 2
	
	def area(self):
		return self.__area
	
	def display(self):
		print "Triangle area = " + str(self.__area)
		
	def __str__(self):
		return "Triangle area = " + str(self.__area)
		
	def __cmp__(self, other):
		if self.area() > other.area():
			return 1
		elif self.area() < other.area():
			return -1
		else:
			return 0
		
		
	
class Rectangle(Shape):
	
	def __init__(self, height, width):
		self.__height = height
		self.__width = width
		self.__area = height * width
	
	def area(self):
		return self.__area
	
	def display(self):
		print "Rectangle area = " + str(self.__area)
		
	def __str__(self):
		return "Rectangle area = " + str(self.__area)
		
	def __cmp__(self, other):
		if self.area() > other.area():
			return 1
		elif self.area() < other.area():
			return -1
		else:
			return 0
		

if __name__ == '__main__':

	shapes = [Rectangle(5, 10), Circle(5), Triangle(5, 10)]
	sorted_shapes = sorted(shapes)
	
	for i in sorted_shapes:
		print i
		
	
