
class exampleClass:
	def __init__(self):
		self.eyes = "brown"
		self.age = 28
	
	def my_method(self):
		return "eyes = " + str(self.eyes) + " + age = " + str(self.age)
		
		
def foo():
	return 1, 2, 3

def fibo_rec(num):
	if num == 0 or num == 1:
		return 1
	else:
		return fibo_rec(num - 2) + fibo_rec(num - 1)

def fibo_iter(num):
	if num == 1 or num == 0:
		return 1
	res = 1
	prev = 0
	for i in range(1, num + 1):
		temp = prev + res
		prev = res
		res = temp
	return res

def find_mails(line):
	import re
	words = re.findall(r'^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,4})$', line)

	return words

def page_parcer(url):
	import urllib2
	data = urllib2.urlopen(url)
	listen = []
	
	html = data.read()
	print html

	return find_mails(html)

def calc(a, b, c):
	def percent(x, total = a + b + c):
		return (x*100.0) / total 
	print "Percentages ate", percent(a), percent(b), percent(c)
	
def calc2(a, b, c):
	def percent(x):
		return (x*100.0) / (a + b + c)
	print "Percentages ate", percent(a), percent(b), percent(c)

if __name__ == "__main__":
	Or = exampleClass()
	print Or.my_method()
	print fibo_rec(1)
	print fibo_rec(2)
	print fibo_rec(3)
	print fibo_rec(4)
	print fibo_rec(5)
	print fibo_rec(6)
	print
	print fibo_iter(1)
	print fibo_iter(2)
	print fibo_iter(3)
	print fibo_iter(4)
	print fibo_iter(5)
	print fibo_iter(6)
	l = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
	f = map(fibo_rec, l)
	print f
	#print page_parcer("https://docs.python.org/2/glossary.html")
	
	calc(2, 4, 5)
	calc2(2, 4, 5)
	for i in dir(tuple):
		print i
		a = 5
		
	print a
	print tuple.__sizeof__(tuple)
