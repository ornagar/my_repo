#ex 1
def hello_world():
	print '"Hello World"'

#ex 2
def hello_hex():
	print "2248656c6c6f20576f726c6422".decode("hex")

#ex 3
def mult_by_eight(num):
	return num << 3

#ex 4
def print_even():
	for i in range(100):
		if i % 2 == 0:
			print i

#ex 5
def list_even():
	new_list = []
	for i in range(100):
		if i % 2 == 0:
			new_list.append(i)
	return new_list
	
#ex 6
def list_even2():
	new_list = [i for i in range(100) if i % 2 == 0]
	return new_list
	
#ex 7
def print_a_f():
	str = "I never think of the future - it comes soon enough"
	pattern = "abcdef"
	new_str = ""
	for char in str:
		if char in pattern:
			new_str += char
	print new_str

#ex 8
def str_to_dict(string):
	my_dict = {}
	for char in string:
		if char in my_dict:
			my_dict[char] += 1
		else:
			my_dict[char] = 1
	print my_dict

#ex 9
def flip_num(num):
	temp = 0
	while num != 0:
		temp *= 10
		temp += num % 10
		num /= 10
	print temp
		
if __name__ == "__main__":
	hello_world()
	hello_hex()
	print mult_by_eight(3)
	print_even()
	print list_even()
	print list_even2()
	print_a_f()
	str_to_dict("hello world")
	flip_num(123)
