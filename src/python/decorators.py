from functools import wraps

def tags(tag_name):
	def tags_decorator(func):
		@wraps(func)
		def func_wrapper(*args, **kwargs):
			return "<p>{0}</p>".format(func(*args, **kwargs))
		return func_wrapper
	return tags_decorator
	
class Person(object):
	def __init__(self):
		self.name = "John"
		self.family = "Doe"
		
	@tags("p")
	def get_fullname(self):
		return self.name + " " + self.family
		
		
@tags("p")
def get_text(name):
	"""returns some text"""
	return "Hello " + name

print get_text.__name__ 
print get_text.__doc__
print get_text.__module__

