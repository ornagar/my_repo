
"""
This is a test file"""

def divide(a, b):
	"""
	divide function raises 'ValueError("Invalid inputs")' if b = 0
	try:
		return a / b
	except ZeroDivisionError:
		If ZeroDivisionError is raised - raise ValueError('invalid inputs')
		raise ValueError('Invalid inputs') from e
		
	"""
	x = False
	def change():
		nonlocal x
		x = True
		
	change()
	return x
	
	
result = divide(2, 2)
if result is None:
	print('Invalid inputs')

print(divide(2, 2))
